#include <type_traits>
#include <intrin.h>
#include <algorithm>

// transform floating-point values to sortable integer values (or vice versa)
template <typename T>
constexpr void FltTransformIntrin(T* val, size_t count, bool to_float) {
    static_assert(std::is_floating_point_v<T>);
    size_t i = 0;

    // float intrinsic speedup using AVX2
    if constexpr (sizeof(T) == 4) {
        for (i; i < count - ((32 / sizeof(T)) - 1); i += (32 / sizeof(T))) {
            __m256i Value = *(__m256i*) & val[i];
            __m256i Data;
            Data = _mm256_and_si256(_mm256_set1_epi32(1ui64 << 31), Value);
            if (to_float) Data = _mm256_xor_si256(Data, _mm256_set1_epi32(1ui64 << 31));
            Data = _mm256_srai_epi32(Data, 31);
            Data = _mm256_or_si256(Data, _mm256_set1_epi32(1ui64 << 31));
            Data = _mm256_xor_si256(Value, Data);
            *(__m256i*)& val[i] = Data;
        }
    }

    for (i; i < count; i++) {
        if constexpr (sizeof(T) == 4) {
            unsigned int Value = *(unsigned int*)&val[i];
            if (!to_float) {
                *(unsigned int*)&val[i] ^= -int(Value >> 31) | 0x80000000;
            }
            else {
                *(unsigned int*)&val[i] ^= ((Value >> 31) - 1) | 0x80000000;
            }
        }
        else if constexpr (sizeof(T) == 8) {
            unsigned __int64 Value = *(unsigned __int64*)&val[i];
            if (!to_float) {
                *(unsigned __int64*)&val[i] ^= -__int64(Value >> 63) | 0x8000000000000000;
            }
            else {
                *(unsigned __int64*)&val[i] ^= ((Value >> 63) - 1) | 0x8000000000000000;
            }
        }
    }
}

// sort an array using custom algorithm
// IgnoreLowBitsCount = number of least significant bits to ignore (must be multiple of 4). Improves speed with every multiple of 8.
// IgnoreHighBitsCount = number of most significant bits to ignore (must be multiple of 4). Improves speed with every multiple of 8.
template <typename T>
void QuickRadix(T* Data, size_t Count, int IgnoreLowBitsCount, int IgnoreHighBitsCount) {
    // total number of bits in the value
    int BitCountCur = IgnoreLowBitsCount;
    const int BitCount = (sizeof(T) * 8) - IgnoreHighBitsCount;
    constexpr int DataSize = sizeof(T);
    IgnoreLowBitsCount &= ~3ui64;
    IgnoreHighBitsCount &= ~3ui64;

    // create temp arrays
    unsigned __int64 Allocation = (unsigned __int64)std::malloc((DataSize * Count) + (sizeof(unsigned int) * 0x100));
    if (!Allocation) return;
    T* SortOutput = (T*)(Allocation + (sizeof(unsigned int) * 0x100));
    {
        constexpr int RadixArraySize = sizeof(unsigned int) * 0x100;
        unsigned int* Radix = (unsigned int*)Allocation;
        constexpr int RadixBase = (RadixArraySize / sizeof(Radix[0])) - 1;

        // radix sort (8-bit aligned)
        while (BitCountCur < BitCount - 7) {
            // reset radix counts
            std::memset(Radix, 0, RadixArraySize);

            // count each occurrence of the current unsigned char value
            {
                __int64 i;

                if (BitCountCur % 8 == 0) {
                    // 8-bit to 32-bit aligned optimizations
                    T* Start = (T*)((unsigned __int64)&Data[0] + (BitCountCur / 8));
                    for (i = 0; i < Count - 7; i += 8) {
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                        Radix[*(unsigned char*)Start++]++;
                    }
                    for (i; i < Count; ++i) {
                        Radix[*(unsigned char*)Start++]++;
                    }
                }
                else if constexpr (DataSize == 8) {
                    // 64-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 3; i += 4) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi64x(RadixBase));
                        Radix[ModData.m256i_u64[0]]++;
                        Radix[ModData.m256i_u64[1]]++;
                        Radix[ModData.m256i_u64[2]]++;
                        Radix[ModData.m256i_u64[3]]++;
                    }
                }
                else if constexpr (DataSize == 4) {
                    // 32-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 7; i += 8) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi32(RadixBase));
                        Radix[ModData.m256i_u32[0]]++;
                        Radix[ModData.m256i_u32[1]]++;
                        Radix[ModData.m256i_u32[2]]++;
                        Radix[ModData.m256i_u32[3]]++;
                        Radix[ModData.m256i_u32[4]]++;
                        Radix[ModData.m256i_u32[5]]++;
                        Radix[ModData.m256i_u32[6]]++;
                        Radix[ModData.m256i_u32[7]]++;
                    }
                }
                else if constexpr (DataSize == 2) {
                    // 16-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 15; i += 16) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi16(RadixBase));
                        Radix[ModData.m256i_u16[0]]++; Radix[ModData.m256i_u16[1]]++;
                        Radix[ModData.m256i_u16[2]]++; Radix[ModData.m256i_u16[3]]++;
                        Radix[ModData.m256i_u16[4]]++; Radix[ModData.m256i_u16[5]]++;
                        Radix[ModData.m256i_u16[6]]++; Radix[ModData.m256i_u16[7]]++;
                        Radix[ModData.m256i_u16[8]]++; Radix[ModData.m256i_u16[9]]++;
                        Radix[ModData.m256i_u16[10]]++; Radix[ModData.m256i_u16[11]]++;
                        Radix[ModData.m256i_u16[12]]++; Radix[ModData.m256i_u16[13]]++;
                        Radix[ModData.m256i_u16[14]]++; Radix[ModData.m256i_u16[15]]++;
                    }
                }
                else {
                    i = 0;
                }

                for (i; i < Count; i++) {
                    if constexpr (std::is_integral_v<T>) {
                        // integer values
                        Radix[(Data[i] >> BitCountCur) & RadixBase]++;
                    }
                    else {
                        if constexpr (DataSize == 8) {
                            // double
                            Radix[(*(__int64*)&Data[i] >> BitCountCur) & RadixBase]++;
                        }
                        else {
                            // float
                            Radix[(*(int*)&Data[i] >> BitCountCur) & RadixBase]++;
                        }
                    }
                }
            }

            // adjust so that they contain the starting location of the new array
            int last = 0;
            if (std::is_signed_v<T> && std::is_integral_v<T> && BitCountCur + 8 >= BitCount && IgnoreHighBitsCount == 0) {
                // final iteration check for signed values; do negatives first
                const int HalfIdx = (RadixBase + 1) / 2;
                for (int i = HalfIdx; i <= RadixBase; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }
                for (int i = 0; i < HalfIdx; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }
            }
            else {
                // adjust pointers all ascending
                for (int i = 0; i <= RadixBase; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }

            }

            // build output in-order
            {
                __int64 i;

                // 64-bit optimization only
                if (BitCountCur % 8 == 0) {
                    // 8-bit to 32-bit aligned optimizations
                    T* Start = (T*)((unsigned __int64)&Data[0] + (BitCountCur / 8));
                    for (i = 0; i < Count - 7;) {
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                    }
                    while (i < Count) {
                        SortOutput[Radix[*(unsigned char*)Start++]++] = Data[i++];
                    }
                }
                else if constexpr (DataSize == 8) {
                    // 64-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 3; i += 4) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi64x(RadixBase));
                        SortOutput[Radix[ModData.m256i_u64[0]]++] = *(T*)&CurData.m256i_u64[0];
                        SortOutput[Radix[ModData.m256i_u64[1]]++] = *(T*)&CurData.m256i_u64[1];
                        SortOutput[Radix[ModData.m256i_u64[2]]++] = *(T*)&CurData.m256i_u64[2];
                        SortOutput[Radix[ModData.m256i_u64[3]]++] = *(T*)&CurData.m256i_u64[3];
                    }
                }
                else if constexpr (DataSize == 4) {
                    // 32-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 7; i += 8) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi32(RadixBase));
                        SortOutput[Radix[ModData.m256i_u32[0]]++] = *(T*)&CurData.m256i_u32[0];
                        SortOutput[Radix[ModData.m256i_u32[1]]++] = *(T*)&CurData.m256i_u32[1];
                        SortOutput[Radix[ModData.m256i_u32[2]]++] = *(T*)&CurData.m256i_u32[2];
                        SortOutput[Radix[ModData.m256i_u32[3]]++] = *(T*)&CurData.m256i_u32[3];
                        SortOutput[Radix[ModData.m256i_u32[4]]++] = *(T*)&CurData.m256i_u32[4];
                        SortOutput[Radix[ModData.m256i_u32[5]]++] = *(T*)&CurData.m256i_u32[5];
                        SortOutput[Radix[ModData.m256i_u32[6]]++] = *(T*)&CurData.m256i_u32[6];
                        SortOutput[Radix[ModData.m256i_u32[7]]++] = *(T*)&CurData.m256i_u32[7];
                    }
                }
                else if constexpr (DataSize == 2) {
                    // 16-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 15; i += 16) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi16(RadixBase));
                        SortOutput[Radix[ModData.m256i_u16[0]]++] = *(T*)&CurData.m256i_u16[0];
                        SortOutput[Radix[ModData.m256i_u16[1]]++] = *(T*)&CurData.m256i_u16[1];
                        SortOutput[Radix[ModData.m256i_u16[2]]++] = *(T*)&CurData.m256i_u16[2];
                        SortOutput[Radix[ModData.m256i_u16[3]]++] = *(T*)&CurData.m256i_u16[3];
                        SortOutput[Radix[ModData.m256i_u16[4]]++] = *(T*)&CurData.m256i_u16[4];
                        SortOutput[Radix[ModData.m256i_u16[5]]++] = *(T*)&CurData.m256i_u16[5];
                        SortOutput[Radix[ModData.m256i_u16[6]]++] = *(T*)&CurData.m256i_u16[6];
                        SortOutput[Radix[ModData.m256i_u16[7]]++] = *(T*)&CurData.m256i_u16[7];
                        SortOutput[Radix[ModData.m256i_u16[8]]++] = *(T*)&CurData.m256i_u16[8];
                        SortOutput[Radix[ModData.m256i_u16[9]]++] = *(T*)&CurData.m256i_u16[9];
                        SortOutput[Radix[ModData.m256i_u16[10]]++] = *(T*)&CurData.m256i_u16[10];
                        SortOutput[Radix[ModData.m256i_u16[11]]++] = *(T*)&CurData.m256i_u16[11];
                        SortOutput[Radix[ModData.m256i_u16[12]]++] = *(T*)&CurData.m256i_u16[12];
                        SortOutput[Radix[ModData.m256i_u16[13]]++] = *(T*)&CurData.m256i_u16[13];
                        SortOutput[Radix[ModData.m256i_u16[14]]++] = *(T*)&CurData.m256i_u16[14];
                        SortOutput[Radix[ModData.m256i_u16[15]]++] = *(T*)&CurData.m256i_u16[15];
                    }
                }
                else {
                    i = 0;
                }

                for (i; i < Count; i++) {
                    if constexpr (std::is_integral_v<T>) {
                        // integer values
                        SortOutput[Radix[(Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                    }
                    else {
                        if constexpr (DataSize == 8) {
                            // double
                            SortOutput[Radix[(*(__int64*)&Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                        }
                        else {
                            // float
                            SortOutput[Radix[(*(int*)&Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                        }
                    }

                }
            }

            // apply to original array
            std::memcpy(&Data[0], &SortOutput[0], Count * sizeof(Data[0]));

            // move on to next byte
            BitCountCur += 8;
        }
    }

    // radix sort (4-bit aligned, this is only called when ignoring some amount of bits)
    {
        constexpr int RadixArraySize = sizeof(unsigned int) * 0x10;
        unsigned int Radix[0x10];
        constexpr int RadixBase = (RadixArraySize / sizeof(Radix[0])) - 1;

        // radix sort (8-bit aligned)
        while (BitCountCur < BitCount) {
            // reset radix counts
            std::memset(Radix, 0, RadixArraySize);

            // count each occurrence of the current unsigned char value
            {
                __int64 i;

                if constexpr (DataSize == 8) {
                    // 64-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 3; i += 4) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi64x(RadixBase));
                        Radix[ModData.m256i_u64[0]]++;
                        Radix[ModData.m256i_u64[1]]++;
                        Radix[ModData.m256i_u64[2]]++;
                        Radix[ModData.m256i_u64[3]]++;
                    }
                }
                else if constexpr (DataSize == 4) {
                    // 32-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 7; i += 8) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi32(RadixBase));
                        Radix[ModData.m256i_u32[0]]++;
                        Radix[ModData.m256i_u32[1]]++;
                        Radix[ModData.m256i_u32[2]]++;
                        Radix[ModData.m256i_u32[3]]++;
                        Radix[ModData.m256i_u32[4]]++;
                        Radix[ModData.m256i_u32[5]]++;
                        Radix[ModData.m256i_u32[6]]++;
                        Radix[ModData.m256i_u32[7]]++;
                    }
                }
                else if constexpr (DataSize == 2) {
                    // 16-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 15; i += 16) {
                        __m256i ModData = _mm256_srli_epi64(*(__m256i*) & Data[i], BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi16(RadixBase));
                        Radix[ModData.m256i_u16[0]]++; Radix[ModData.m256i_u16[1]]++;
                        Radix[ModData.m256i_u16[2]]++; Radix[ModData.m256i_u16[3]]++;
                        Radix[ModData.m256i_u16[4]]++; Radix[ModData.m256i_u16[5]]++;
                        Radix[ModData.m256i_u16[6]]++; Radix[ModData.m256i_u16[7]]++;
                        Radix[ModData.m256i_u16[8]]++; Radix[ModData.m256i_u16[9]]++;
                        Radix[ModData.m256i_u16[10]]++; Radix[ModData.m256i_u16[11]]++;
                        Radix[ModData.m256i_u16[12]]++; Radix[ModData.m256i_u16[13]]++;
                        Radix[ModData.m256i_u16[14]]++; Radix[ModData.m256i_u16[15]]++;
                    }
                }
                else {
                    i = 0;
                }

                for (i; i < Count; i++) {
                    if constexpr (std::is_integral_v<T>) {
                        // integer values
                        Radix[(Data[i] >> BitCountCur) & RadixBase]++;
                    }
                    else {
                        if constexpr (DataSize == 8) {
                            // double
                            Radix[(*(__int64*)&Data[i] >> BitCountCur) & RadixBase]++;
                        }
                        else {
                            // float
                            Radix[(*(int*)&Data[i] >> BitCountCur) & RadixBase]++;
                        }
                    }
                }
            }

            // adjust so that they contain the starting location of the new array
            int last = 0;
            if (std::is_signed_v<T> && std::is_integral_v<T> && BitCountCur + 4 >= BitCount && IgnoreHighBitsCount == 0) {
                // final iteration check for signed values; do negatives first
                const int HalfIdx = (RadixBase + 1) / 2;
                for (int i = HalfIdx; i <= RadixBase; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }
                for (int i = 0; i < HalfIdx; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }
            }
            else {
                // adjust pointers all ascending
                for (int i = 0; i <= RadixBase; i++) {
                    last += Radix[i];
                    Radix[i] = last - Radix[i];
                }

            }

            // build output in-order
            {
                __int64 i;

                // 64-bit optimization only
                if constexpr (DataSize == 8) {
                    // 64-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 3; i += 4) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi64x(RadixBase));
                        SortOutput[Radix[ModData.m256i_u64[0]]++] = *(T*)&CurData.m256i_u64[0];
                        SortOutput[Radix[ModData.m256i_u64[1]]++] = *(T*)&CurData.m256i_u64[1];
                        SortOutput[Radix[ModData.m256i_u64[2]]++] = *(T*)&CurData.m256i_u64[2];
                        SortOutput[Radix[ModData.m256i_u64[3]]++] = *(T*)&CurData.m256i_u64[3];
                    }
                }
                else if constexpr (DataSize == 4) {
                    // 32-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 7; i += 8) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi32(RadixBase));
                        SortOutput[Radix[ModData.m256i_u32[0]]++] = *(T*)&CurData.m256i_u32[0];
                        SortOutput[Radix[ModData.m256i_u32[1]]++] = *(T*)&CurData.m256i_u32[1];
                        SortOutput[Radix[ModData.m256i_u32[2]]++] = *(T*)&CurData.m256i_u32[2];
                        SortOutput[Radix[ModData.m256i_u32[3]]++] = *(T*)&CurData.m256i_u32[3];
                        SortOutput[Radix[ModData.m256i_u32[4]]++] = *(T*)&CurData.m256i_u32[4];
                        SortOutput[Radix[ModData.m256i_u32[5]]++] = *(T*)&CurData.m256i_u32[5];
                        SortOutput[Radix[ModData.m256i_u32[6]]++] = *(T*)&CurData.m256i_u32[6];
                        SortOutput[Radix[ModData.m256i_u32[7]]++] = *(T*)&CurData.m256i_u32[7];
                    }
                }
                else if constexpr (DataSize == 2) {
                    // 16-bit optimization unaligned using AVX2
                    for (i = 0; i < Count - 15; i += 16) {
                        __m256i CurData = *(__m256i*) & Data[i];
                        __m256i ModData = _mm256_srli_epi64(CurData, BitCountCur);
                        ModData = _mm256_and_si256(ModData, _mm256_set1_epi16(RadixBase));
                        SortOutput[Radix[ModData.m256i_u16[0]]++] = *(T*)&CurData.m256i_u16[0];
                        SortOutput[Radix[ModData.m256i_u16[1]]++] = *(T*)&CurData.m256i_u16[1];
                        SortOutput[Radix[ModData.m256i_u16[2]]++] = *(T*)&CurData.m256i_u16[2];
                        SortOutput[Radix[ModData.m256i_u16[3]]++] = *(T*)&CurData.m256i_u16[3];
                        SortOutput[Radix[ModData.m256i_u16[4]]++] = *(T*)&CurData.m256i_u16[4];
                        SortOutput[Radix[ModData.m256i_u16[5]]++] = *(T*)&CurData.m256i_u16[5];
                        SortOutput[Radix[ModData.m256i_u16[6]]++] = *(T*)&CurData.m256i_u16[6];
                        SortOutput[Radix[ModData.m256i_u16[7]]++] = *(T*)&CurData.m256i_u16[7];
                        SortOutput[Radix[ModData.m256i_u16[8]]++] = *(T*)&CurData.m256i_u16[8];
                        SortOutput[Radix[ModData.m256i_u16[9]]++] = *(T*)&CurData.m256i_u16[9];
                        SortOutput[Radix[ModData.m256i_u16[10]]++] = *(T*)&CurData.m256i_u16[10];
                        SortOutput[Radix[ModData.m256i_u16[11]]++] = *(T*)&CurData.m256i_u16[11];
                        SortOutput[Radix[ModData.m256i_u16[12]]++] = *(T*)&CurData.m256i_u16[12];
                        SortOutput[Radix[ModData.m256i_u16[13]]++] = *(T*)&CurData.m256i_u16[13];
                        SortOutput[Radix[ModData.m256i_u16[14]]++] = *(T*)&CurData.m256i_u16[14];
                        SortOutput[Radix[ModData.m256i_u16[15]]++] = *(T*)&CurData.m256i_u16[15];
                    }
                }
                else {
                    i = 0;
                }

                for (i; i < Count; i++) {
                    if constexpr (std::is_integral_v<T>) {
                        // integer values
                        SortOutput[Radix[(Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                    }
                    else {
                        if constexpr (DataSize == 8) {
                            // double
                            SortOutput[Radix[(*(__int64*)&Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                        }
                        else {
                            // float
                            SortOutput[Radix[(*(int*)&Data[i] >> BitCountCur) & RadixBase]++] = Data[i];
                        }
                    }

                }
            }

            // apply to original array
            std::memcpy(&Data[0], &SortOutput[0], Count * sizeof(Data[0]));

            // move on to next bits (this is technically unnecessary because there should only ever be 1 iteration of this loop!)
            BitCountCur += 4;
        }
    }
    std::free((void*)Allocation);

    // float/double check
    if constexpr (!std::is_integral_v<T>) {
        FltTransformIntrin(&Data[0], Count, true);
    }
}