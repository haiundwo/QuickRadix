# QuickRadix
Quick Radix custom sorting algorithm; fast basic radix algorithm that specializes in smaller data types.

# Downsides
Starts to get much slower when the amount of memory to be allocated by std::malloc reaches a certain threshold. In these cases, an in-place radix sort (such as American Flag Sort or skasort) would be better.

Optimizing this source would include branches based on number of elements and data types to use Skasort (or some other faster sort) instead of this sort for some specific cases (8-byte sorts with large size, floating-point sorts with small size, etc.) which would lead to a better overall sorting algorithm.

This code is also only tested for completely random data sets. It may be much slower than comparison sorts for less randomized data.

 # Benchmarks
Benchmarks of the algorithm on various data types under a Windows 10 Home x64 Desktop PC with an Intel 12700K CPU.
 
# Integer Tests
1-byte: Radix was 1.29422x as fast as std::sort for sorting 50x elements 10000 times

1-byte: Radix was 1.73325x as fast as std::sort for sorting 75x elements 10000 times

1-byte: Radix was 2.37958x as fast as std::sort for sorting 100x elements 10000 times

1-byte: Radix was 3.22549x as fast as std::sort for sorting 150x elements 10000 times

1-byte: Radix was 4.18768x as fast as std::sort for sorting 200x elements 10000 times

1-byte: Radix was 4.59485x as fast as std::sort for sorting 250x elements 10000 times

1-byte: Radix was 8.96864x as fast as std::sort for sorting 500x elements 8000 times

1-byte: Radix was 8.74816x as fast as std::sort for sorting 1000x elements 6000 times

1-byte: Radix was 29.125x as fast as std::sort for sorting 2500x elements 4000 times

1-byte: Radix was 37.0268x as fast as std::sort for sorting 5000x elements 2000 times

1-byte: Radix was 38.8729x as fast as std::sort for sorting 10000x elements 1000 times

1-byte: Radix was 34.3327x as fast as std::sort for sorting 15000x elements 750 times

1-byte: Radix was 18.7623x as fast as std::sort for sorting 25000x elements 350 times

1-byte: Radix was 19.178x as fast as std::sort for sorting 50000x elements 200 times

1-byte: Radix was 18.2401x as fast as std::sort for sorting 100000x elements 100 times

1-byte: Radix was 26.0958x as fast as std::sort for sorting 250000x elements 50 times

1-byte: Radix was 26.3785x as fast as std::sort for sorting 500000x elements 25 times

1-byte: Radix was 22.2502x as fast as std::sort for sorting 1000000x elements 10 times

1-byte unsigned: Radix was 1.25325x as fast as std::sort for sorting 50x elements 10000 times

1-byte unsigned: Radix was 2.08596x as fast as std::sort for sorting 75x elements 10000 times

1-byte unsigned: Radix was 2.36463x as fast as std::sort for sorting 100x elements 10000 times

1-byte unsigned: Radix was 3.78407x as fast as std::sort for sorting 150x elements 10000 times

1-byte unsigned: Radix was 4.12093x as fast as std::sort for sorting 200x elements 10000 times

1-byte unsigned: Radix was 5.01478x as fast as std::sort for sorting 250x elements 10000 times

1-byte unsigned: Radix was 8.42183x as fast as std::sort for sorting 500x elements 8000 times

1-byte unsigned: Radix was 8.36422x as fast as std::sort for sorting 1000x elements 6000 times

1-byte unsigned: Radix was 23.6234x as fast as std::sort for sorting 2500x elements 4000 times

1-byte unsigned: Radix was 29.9679x as fast as std::sort for sorting 5000x elements 2000 times

1-byte unsigned: Radix was 35.6377x as fast as std::sort for sorting 10000x elements 1000 times

1-byte unsigned: Radix was 37.6368x as fast as std::sort for sorting 15000x elements 750 times

1-byte unsigned: Radix was 31.0336x as fast as std::sort for sorting 25000x elements 350 times

1-byte unsigned: Radix was 26.4146x as fast as std::sort for sorting 50000x elements 200 times

1-byte unsigned: Radix was 22.1298x as fast as std::sort for sorting 100000x elements 100 times

1-byte unsigned: Radix was 20.0068x as fast as std::sort for sorting 250000x elements 50 times

1-byte unsigned: Radix was 23.7268x as fast as std::sort for sorting 500000x elements 25 times

1-byte unsigned: Radix was 22.5924x as fast as std::sort for sorting 1000000x elements 10 times

2-byte: Radix was 1.17864x as fast as std::sort for sorting 50x elements 10000 times

2-byte: Radix was 1.13863x as fast as std::sort for sorting 75x elements 10000 times

2-byte: Radix was 1.54586x as fast as std::sort for sorting 100x elements 10000 times

2-byte: Radix was 2.39074x as fast as std::sort for sorting 150x elements 10000 times

2-byte: Radix was 2.08807x as fast as std::sort for sorting 200x elements 10000 times

2-byte: Radix was 2.7083x as fast as std::sort for sorting 250x elements 10000 times

2-byte: Radix was 4.48024x as fast as std::sort for sorting 500x elements 8000 times

2-byte: Radix was 5.70972x as fast as std::sort for sorting 1000x elements 6000 times

2-byte: Radix was 16.3885x as fast as std::sort for sorting 2500x elements 4000 times

2-byte: Radix was 20.6132x as fast as std::sort for sorting 5000x elements 2000 times

2-byte: Radix was 27.4055x as fast as std::sort for sorting 10000x elements 1000 times

2-byte: Radix was 24.2608x as fast as std::sort for sorting 15000x elements 750 times

2-byte: Radix was 22.837x as fast as std::sort for sorting 25000x elements 350 times

2-byte: Radix was 21.0144x as fast as std::sort for sorting 50000x elements 200 times

2-byte: Radix was 23.7659x as fast as std::sort for sorting 100000x elements 100 times

2-byte: Radix was 23.2425x as fast as std::sort for sorting 250000x elements 50 times

2-byte: Radix was 23.5272x as fast as std::sort for sorting 500000x elements 25 times

2-byte: Radix was 18.4471x as fast as std::sort for sorting 1000000x elements 10 times

2-byte unsigned: Radix was 0.871409x as fast as std::sort for sorting 50x elements 10000 times

2-byte unsigned: Radix was 1.0706x as fast as std::sort for sorting 75x elements 10000 times

2-byte unsigned: Radix was 1.48399x as fast as std::sort for sorting 100x elements 10000 times

2-byte unsigned: Radix was 2.28185x as fast as std::sort for sorting 150x elements 10000 times

2-byte unsigned: Radix was 2.55504x as fast as std::sort for sorting 200x elements 10000 times

2-byte unsigned: Radix was 2.94133x as fast as std::sort for sorting 250x elements 10000 times

2-byte unsigned: Radix was 4.09744x as fast as std::sort for sorting 500x elements 8000 times

2-byte unsigned: Radix was 4.77869x as fast as std::sort for sorting 1000x elements 6000 times

2-byte unsigned: Radix was 16.0433x as fast as std::sort for sorting 2500x elements 4000 times

2-byte unsigned: Radix was 21.3868x as fast as std::sort for sorting 5000x elements 2000 times

2-byte unsigned: Radix was 27.0283x as fast as std::sort for sorting 10000x elements 1000 times

2-byte unsigned: Radix was 23.5683x as fast as std::sort for sorting 15000x elements 750 times

2-byte unsigned: Radix was 23.6707x as fast as std::sort for sorting 25000x elements 350 times

2-byte unsigned: Radix was 24.5732x as fast as std::sort for sorting 50000x elements 200 times

2-byte unsigned: Radix was 25.3851x as fast as std::sort for sorting 100000x elements 100 times

2-byte unsigned: Radix was 25.6997x as fast as std::sort for sorting 250000x elements 50 times

2-byte unsigned: Radix was 24.0442x as fast as std::sort for sorting 500000x elements 25 times

2-byte unsigned: Radix was 17.8821x as fast as std::sort for sorting 1000000x elements 10 times

4-byte: Radix was 0.340034x as fast as std::sort for sorting 50x elements 10000 times

4-byte: Radix was 0.645023x as fast as std::sort for sorting 75x elements 10000 times

4-byte: Radix was 0.780506x as fast as std::sort for sorting 100x elements 10000 times

4-byte: Radix was 1.04055x as fast as std::sort for sorting 150x elements 10000 times

4-byte: Radix was 1.45881x as fast as std::sort for sorting 200x elements 10000 times

4-byte: Radix was 1.64066x as fast as std::sort for sorting 250x elements 10000 times

4-byte: Radix was 2.04108x as fast as std::sort for sorting 500x elements 8000 times

4-byte: Radix was 2.76748x as fast as std::sort for sorting 1000x elements 6000 times

4-byte: Radix was 8.34876x as fast as std::sort for sorting 2500x elements 4000 times

4-byte: Radix was 9.73038x as fast as std::sort for sorting 5000x elements 2000 times

4-byte: Radix was 9.78397x as fast as std::sort for sorting 10000x elements 1000 times

4-byte: Radix was 10.2352x as fast as std::sort for sorting 15000x elements 750 times

4-byte: Radix was 9.92439x as fast as std::sort for sorting 25000x elements 350 times

4-byte: Radix was 10.8011x as fast as std::sort for sorting 50000x elements 200 times

4-byte: Radix was 11.291x as fast as std::sort for sorting 100000x elements 100 times

4-byte: Radix was 10.8228x as fast as std::sort for sorting 250000x elements 50 times

4-byte: Radix was 8.24083x as fast as std::sort for sorting 500000x elements 25 times

4-byte: Radix was 8.02052x as fast as std::sort for sorting 1000000x elements 10 times

4-byte unsigned: Radix was 0.461475x as fast as std::sort for sorting 50x elements 10000 times

4-byte unsigned: Radix was 0.645993x as fast as std::sort for sorting 75x elements 10000 times

4-byte unsigned: Radix was 0.864583x as fast as std::sort for sorting 100x elements 10000 times

4-byte unsigned: Radix was 1.05045x as fast as std::sort for sorting 150x elements 10000 times

4-byte unsigned: Radix was 1.46284x as fast as std::sort for sorting 200x elements 10000 times

4-byte unsigned: Radix was 1.78364x as fast as std::sort for sorting 250x elements 10000 times

4-byte unsigned: Radix was 2.55903x as fast as std::sort for sorting 500x elements 8000 times

4-byte unsigned: Radix was 2.85632x as fast as std::sort for sorting 1000x elements 6000 times

4-byte unsigned: Radix was 7.38708x as fast as std::sort for sorting 2500x elements 4000 times

4-byte unsigned: Radix was 11.7765x as fast as std::sort for sorting 5000x elements 2000 times

4-byte unsigned: Radix was 9.51227x as fast as std::sort for sorting 10000x elements 1000 times

4-byte unsigned: Radix was 10.197x as fast as std::sort for sorting 15000x elements 750 times

4-byte unsigned: Radix was 9.02649x as fast as std::sort for sorting 25000x elements 350 times

4-byte unsigned: Radix was 11.0735x as fast as std::sort for sorting 50000x elements 200 times

4-byte unsigned: Radix was 12.0337x as fast as std::sort for sorting 100000x elements 100 times

4-byte unsigned: Radix was 10.958x as fast as std::sort for sorting 250000x elements 50 times

4-byte unsigned: Radix was 8.74609x as fast as std::sort for sorting 500000x elements 25 times

4-byte unsigned: Radix was 8.89961x as fast as std::sort for sorting 1000000x elements 10 times

8-byte: Radix was 0.219279x as fast as std::sort for sorting 50x elements 10000 times

8-byte: Radix was 0.370007x as fast as std::sort for sorting 75x elements 10000 times

8-byte: Radix was 0.505312x as fast as std::sort for sorting 100x elements 10000 times

8-byte: Radix was 0.629228x as fast as std::sort for sorting 150x elements 10000 times

8-byte: Radix was 0.600416x as fast as std::sort for sorting 200x elements 10000 times

8-byte: Radix was 0.772758x as fast as std::sort for sorting 250x elements 10000 times

8-byte: Radix was 0.994555x as fast as std::sort for sorting 500x elements 8000 times

8-byte: Radix was 1.39609x as fast as std::sort for sorting 1000x elements 6000 times

8-byte: Radix was 4.24157x as fast as std::sort for sorting 2500x elements 4000 times

8-byte: Radix was 3.33985x as fast as std::sort for sorting 5000x elements 2000 times

8-byte: Radix was 3.85699x as fast as std::sort for sorting 10000x elements 1000 times

8-byte: Radix was 3.93746x as fast as std::sort for sorting 15000x elements 750 times

8-byte: Radix was 4.25026x as fast as std::sort for sorting 25000x elements 350 times

8-byte: Radix was 4.40944x as fast as std::sort for sorting 50000x elements 200 times

8-byte: Radix was 4.34181x as fast as std::sort for sorting 100000x elements 100 times

8-byte: Radix was 2.9971x as fast as std::sort for sorting 250000x elements 50 times

8-byte: Radix was 2.87113x as fast as std::sort for sorting 500000x elements 25 times

8-byte: Radix was 3.21032x as fast as std::sort for sorting 1000000x elements 10 times

8-byte unsigned: Radix was 0.286939x as fast as std::sort for sorting 50x elements 10000 times

8-byte unsigned: Radix was 0.376354x as fast as std::sort for sorting 75x elements 10000 times

8-byte unsigned: Radix was 0.554564x as fast as std::sort for sorting 100x elements 10000 times

8-byte unsigned: Radix was 0.751964x as fast as std::sort for sorting 150x elements 10000 times

8-byte unsigned: Radix was 0.676617x as fast as std::sort for sorting 200x elements 10000 times

8-byte unsigned: Radix was 0.920142x as fast as std::sort for sorting 250x elements 10000 times

8-byte unsigned: Radix was 1.12489x as fast as std::sort for sorting 500x elements 8000 times

8-byte unsigned: Radix was 1.4159x as fast as std::sort for sorting 1000x elements 6000 times

8-byte unsigned: Radix was 3.57962x as fast as std::sort for sorting 2500x elements 4000 times

8-byte unsigned: Radix was 3.48442x as fast as std::sort for sorting 5000x elements 2000 times

8-byte unsigned: Radix was 3.77885x as fast as std::sort for sorting 10000x elements 1000 times

8-byte unsigned: Radix was 4.04902x as fast as std::sort for sorting 15000x elements 750 times

8-byte unsigned: Radix was 4.45094x as fast as std::sort for sorting 25000x elements 350 times

8-byte unsigned: Radix was 4.71354x as fast as std::sort for sorting 50000x elements 200 times

8-byte unsigned: Radix was 4.34136x as fast as std::sort for sorting 100000x elements 100 times

8-byte unsigned: Radix was 3.17322x as fast as std::sort for sorting 250000x elements 50 times

8-byte unsigned: Radix was 3.18676x as fast as std::sort for sorting 500000x elements 25 times

8-byte unsigned: Radix was 3.23655x as fast as std::sort for sorting 1000000x elements 10 times


# Float Tests
4-byte float: Radix was 0.368507x as fast as std::sort for sorting 50x elements 10000 times

4-byte float: Radix was 0.652071x as fast as std::sort for sorting 75x elements 10000 times

4-byte float: Radix was 1.0745x as fast as std::sort for sorting 100x elements 10000 times

4-byte float: Radix was 1.07505x as fast as std::sort for sorting 150x elements 10000 times

4-byte float: Radix was 1.47428x as fast as std::sort for sorting 200x elements 10000 times

4-byte float: Radix was 1.67052x as fast as std::sort for sorting 250x elements 10000 times

4-byte float: Radix was 2.03166x as fast as std::sort for sorting 500x elements 8000 times

4-byte float: Radix was 3.0799x as fast as std::sort for sorting 1000x elements 6000 times

4-byte float: Radix was 8.11983x as fast as std::sort for sorting 2500x elements 4000 times

4-byte float: Radix was 11.4517x as fast as std::sort for sorting 5000x elements 2000 times

4-byte float: Radix was 9.64911x as fast as std::sort for sorting 10000x elements 1000 times

4-byte float: Radix was 10.3067x as fast as std::sort for sorting 15000x elements 750 times

4-byte float: Radix was 10.3816x as fast as std::sort for sorting 25000x elements 350 times

4-byte float: Radix was 11.0713x as fast as std::sort for sorting 50000x elements 200 times

4-byte float: Radix was 11.8943x as fast as std::sort for sorting 100000x elements 100 times

4-byte float: Radix was 11.3605x as fast as std::sort for sorting 250000x elements 50 times

4-byte float: Radix was 7.98725x as fast as std::sort for sorting 500000x elements 25 times

4-byte float: Radix was 8.11588x as fast as std::sort for sorting 1000000x elements 10 times

8-byte float: Radix was 0.239516x as fast as std::sort for sorting 50x elements 10000 times

8-byte float: Radix was 0.405612x as fast as std::sort for sorting 75x elements 10000 times

8-byte float: Radix was 0.523181x as fast as std::sort for sorting 100x elements 10000 times

8-byte float: Radix was 0.678421x as fast as std::sort for sorting 150x elements 10000 times

8-byte float: Radix was 0.690005x as fast as std::sort for sorting 200x elements 10000 times

8-byte float: Radix was 0.82371x as fast as std::sort for sorting 250x elements 10000 times

8-byte float: Radix was 1.16442x as fast as std::sort for sorting 500x elements 8000 times

8-byte float: Radix was 1.26162x as fast as std::sort for sorting 1000x elements 6000 times

8-byte float: Radix was 1.57502x as fast as std::sort for sorting 2500x elements 4000 times

8-byte float: Radix was 1.58911x as fast as std::sort for sorting 5000x elements 2000 times

8-byte float: Radix was 3.74223x as fast as std::sort for sorting 10000x elements 1000 times

8-byte float: Radix was 4.24705x as fast as std::sort for sorting 15000x elements 750 times

8-byte float: Radix was 4.35016x as fast as std::sort for sorting 25000x elements 350 times

8-byte float: Radix was 4.73954x as fast as std::sort for sorting 50000x elements 200 times

8-byte float: Radix was 4.46708x as fast as std::sort for sorting 100000x elements 100 times

8-byte float: Radix was 3.08107x as fast as std::sort for sorting 250000x elements 50 times

8-byte float: Radix was 3.05739x as fast as std::sort for sorting 500000x elements 25 times

8-byte float: Radix was 3.10849x as fast as std::sort for sorting 1000000x elements 10 times
