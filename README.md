# QuickRadix
Quick Radix custom sorting algorithm; fast basic radix algorithm that specializes in smaller data types.

# Downsides
Starts to get much slower when the amount of memory to be allocated by std::malloc reaches a certain threshold. In these cases, an in-place radix sort (such as American Flag Sort or skasort) would be better.
Using skasort instead of this sort for some specific cases (8-byte sorts with large size, floating-point sorts with small size, etc.) would lead to a better overall sorting algorithm.

 # Benchmarks
Benchmarks of the algorithm on various data types under a Windows 10 Home x64 Desktop PC with an Intel 12700K CPU.
 
# Integer Tests
1-byte: Radix was 1.15909x as fast as std::sort for sorting 50x elements 10000 times
1-byte: Radix was 1.78818x as fast as std::sort for sorting 75x elements 10000 times
1-byte: Radix was 2.50873x as fast as std::sort for sorting 100x elements 10000 times
1-byte: Radix was 3.44801x as fast as std::sort for sorting 150x elements 10000 times
1-byte: Radix was 3.13308x as fast as std::sort for sorting 200x elements 10000 times
1-byte: Radix was 4.57013x as fast as std::sort for sorting 250x elements 10000 times
1-byte: Radix was 6.10832x as fast as std::sort for sorting 500x elements 8000 times
1-byte: Radix was 10.2079x as fast as std::sort for sorting 1000x elements 6000 times
1-byte: Radix was 18.4667x as fast as std::sort for sorting 2500x elements 4000 times
1-byte: Radix was 36.6386x as fast as std::sort for sorting 5000x elements 2000 times
1-byte: Radix was 36.9507x as fast as std::sort for sorting 10000x elements 1000 times
1-byte: Radix was 28.1921x as fast as std::sort for sorting 15000x elements 750 times
1-byte: Radix was 18.7435x as fast as std::sort for sorting 25000x elements 350 times
1-byte: Radix was 18.2685x as fast as std::sort for sorting 50000x elements 200 times
1-byte: Radix was 18.3138x as fast as std::sort for sorting 100000x elements 100 times
1-byte: Radix was 24.9902x as fast as std::sort for sorting 250000x elements 50 times
1-byte: Radix was 24.339x as fast as std::sort for sorting 500000x elements 25 times
1-byte: Radix was 22.8571x as fast as std::sort for sorting 1000000x elements 10 times
1-byte unsigned: Radix was 1.89655x as fast as std::sort for sorting 50x elements 10000 times
1-byte unsigned: Radix was 1.82398x as fast as std::sort for sorting 75x elements 10000 times
1-byte unsigned: Radix was 2.62724x as fast as std::sort for sorting 100x elements 10000 times
1-byte unsigned: Radix was 3.50131x as fast as std::sort for sorting 150x elements 10000 times
1-byte unsigned: Radix was 3.95794x as fast as std::sort for sorting 200x elements 10000 times
1-byte unsigned: Radix was 5.24051x as fast as std::sort for sorting 250x elements 10000 times
1-byte unsigned: Radix was 7.73713x as fast as std::sort for sorting 500x elements 8000 times
1-byte unsigned: Radix was 8.52323x as fast as std::sort for sorting 1000x elements 6000 times
1-byte unsigned: Radix was 24.2389x as fast as std::sort for sorting 2500x elements 4000 times
1-byte unsigned: Radix was 31.2315x as fast as std::sort for sorting 5000x elements 2000 times
1-byte unsigned: Radix was 35.2789x as fast as std::sort for sorting 10000x elements 1000 times
1-byte unsigned: Radix was 35.9522x as fast as std::sort for sorting 15000x elements 750 times
1-byte unsigned: Radix was 30.6684x as fast as std::sort for sorting 25000x elements 350 times
1-byte unsigned: Radix was 27.2594x as fast as std::sort for sorting 50000x elements 200 times
1-byte unsigned: Radix was 21.3917x as fast as std::sort for sorting 100000x elements 100 times
1-byte unsigned: Radix was 21.1019x as fast as std::sort for sorting 250000x elements 50 times
1-byte unsigned: Radix was 23.2009x as fast as std::sort for sorting 500000x elements 25 times
1-byte unsigned: Radix was 22.5279x as fast as std::sort for sorting 1000000x elements 10 times
2-byte: Radix was 0.927921x as fast as std::sort for sorting 50x elements 10000 times
2-byte: Radix was 1.42137x as fast as std::sort for sorting 75x elements 10000 times
2-byte: Radix was 1.77017x as fast as std::sort for sorting 100x elements 10000 times
2-byte: Radix was 2.34208x as fast as std::sort for sorting 150x elements 10000 times
2-byte: Radix was 2.23858x as fast as std::sort for sorting 200x elements 10000 times
2-byte: Radix was 3.46725x as fast as std::sort for sorting 250x elements 10000 times
2-byte: Radix was 4.22969x as fast as std::sort for sorting 500x elements 8000 times
2-byte: Radix was 5.97177x as fast as std::sort for sorting 1000x elements 6000 times
2-byte: Radix was 15.9108x as fast as std::sort for sorting 2500x elements 4000 times
2-byte: Radix was 21.8794x as fast as std::sort for sorting 5000x elements 2000 times
2-byte: Radix was 27.8692x as fast as std::sort for sorting 10000x elements 1000 times
2-byte: Radix was 20.9966x as fast as std::sort for sorting 15000x elements 750 times
2-byte: Radix was 23.6066x as fast as std::sort for sorting 25000x elements 350 times
2-byte: Radix was 21.7887x as fast as std::sort for sorting 50000x elements 200 times
2-byte: Radix was 23.2415x as fast as std::sort for sorting 100000x elements 100 times
2-byte: Radix was 24.26x as fast as std::sort for sorting 250000x elements 50 times
2-byte: Radix was 25.0316x as fast as std::sort for sorting 500000x elements 25 times
2-byte: Radix was 18.4289x as fast as std::sort for sorting 1000000x elements 10 times
2-byte unsigned: Radix was 0.822406x as fast as std::sort for sorting 50x elements 10000 times
2-byte unsigned: Radix was 1.21469x as fast as std::sort for sorting 75x elements 10000 times
2-byte unsigned: Radix was 1.64395x as fast as std::sort for sorting 100x elements 10000 times
2-byte unsigned: Radix was 1.96656x as fast as std::sort for sorting 150x elements 10000 times
2-byte unsigned: Radix was 2.20838x as fast as std::sort for sorting 200x elements 10000 times
2-byte unsigned: Radix was 2.76455x as fast as std::sort for sorting 250x elements 10000 times
2-byte unsigned: Radix was 4.07799x as fast as std::sort for sorting 500x elements 8000 times
2-byte unsigned: Radix was 4.49441x as fast as std::sort for sorting 1000x elements 6000 times
2-byte unsigned: Radix was 15.1924x as fast as std::sort for sorting 2500x elements 4000 times
2-byte unsigned: Radix was 20.8824x as fast as std::sort for sorting 5000x elements 2000 times
2-byte unsigned: Radix was 27.0992x as fast as std::sort for sorting 10000x elements 1000 times
2-byte unsigned: Radix was 21.2996x as fast as std::sort for sorting 15000x elements 750 times
2-byte unsigned: Radix was 24.3888x as fast as std::sort for sorting 25000x elements 350 times
2-byte unsigned: Radix was 24.0757x as fast as std::sort for sorting 50000x elements 200 times
2-byte unsigned: Radix was 25.6518x as fast as std::sort for sorting 100000x elements 100 times
2-byte unsigned: Radix was 25.5211x as fast as std::sort for sorting 250000x elements 50 times
2-byte unsigned: Radix was 24.7674x as fast as std::sort for sorting 500000x elements 25 times
2-byte unsigned: Radix was 17.4906x as fast as std::sort for sorting 1000000x elements 10 times
4-byte: Radix was 0.467267x as fast as std::sort for sorting 50x elements 10000 times
4-byte: Radix was 0.567589x as fast as std::sort for sorting 75x elements 10000 times
4-byte: Radix was 0.783293x as fast as std::sort for sorting 100x elements 10000 times
4-byte: Radix was 1.09083x as fast as std::sort for sorting 150x elements 10000 times
4-byte: Radix was 1.56878x as fast as std::sort for sorting 200x elements 10000 times
4-byte: Radix was 1.56397x as fast as std::sort for sorting 250x elements 10000 times
4-byte: Radix was 2.02974x as fast as std::sort for sorting 500x elements 8000 times
4-byte: Radix was 3.08502x as fast as std::sort for sorting 1000x elements 6000 times
4-byte: Radix was 8.77907x as fast as std::sort for sorting 2500x elements 4000 times
4-byte: Radix was 11.1507x as fast as std::sort for sorting 5000x elements 2000 times
4-byte: Radix was 9.25143x as fast as std::sort for sorting 10000x elements 1000 times
4-byte: Radix was 9.86097x as fast as std::sort for sorting 15000x elements 750 times
4-byte: Radix was 10.1499x as fast as std::sort for sorting 25000x elements 350 times
4-byte: Radix was 10.8678x as fast as std::sort for sorting 50000x elements 200 times
4-byte: Radix was 12.2357x as fast as std::sort for sorting 100000x elements 100 times
4-byte: Radix was 10.3881x as fast as std::sort for sorting 250000x elements 50 times
4-byte: Radix was 8.29464x as fast as std::sort for sorting 500000x elements 25 times
4-byte: Radix was 8.21462x as fast as std::sort for sorting 1000000x elements 10 times
4-byte unsigned: Radix was 0.37648x as fast as std::sort for sorting 50x elements 10000 times
4-byte unsigned: Radix was 0.583899x as fast as std::sort for sorting 75x elements 10000 times
4-byte unsigned: Radix was 0.623301x as fast as std::sort for sorting 100x elements 10000 times
4-byte unsigned: Radix was 1.32343x as fast as std::sort for sorting 150x elements 10000 times
4-byte unsigned: Radix was 1.485x as fast as std::sort for sorting 200x elements 10000 times
4-byte unsigned: Radix was 1.64603x as fast as std::sort for sorting 250x elements 10000 times
4-byte unsigned: Radix was 2.14062x as fast as std::sort for sorting 500x elements 8000 times
4-byte unsigned: Radix was 2.6902x as fast as std::sort for sorting 1000x elements 6000 times
4-byte unsigned: Radix was 7.33768x as fast as std::sort for sorting 2500x elements 4000 times
4-byte unsigned: Radix was 11.0081x as fast as std::sort for sorting 5000x elements 2000 times
4-byte unsigned: Radix was 9.79119x as fast as std::sort for sorting 10000x elements 1000 times
4-byte unsigned: Radix was 10.3121x as fast as std::sort for sorting 15000x elements 750 times
4-byte unsigned: Radix was 9.92281x as fast as std::sort for sorting 25000x elements 350 times
4-byte unsigned: Radix was 10.7313x as fast as std::sort for sorting 50000x elements 200 times
4-byte unsigned: Radix was 12.0324x as fast as std::sort for sorting 100000x elements 100 times
4-byte unsigned: Radix was 11.3993x as fast as std::sort for sorting 250000x elements 50 times
4-byte unsigned: Radix was 8.11222x as fast as std::sort for sorting 500000x elements 25 times
4-byte unsigned: Radix was 8.35272x as fast as std::sort for sorting 1000000x elements 10 times
8-byte: Radix was 0.207548x as fast as std::sort for sorting 50x elements 10000 times
8-byte: Radix was 0.334995x as fast as std::sort for sorting 75x elements 10000 times
8-byte: Radix was 0.48562x as fast as std::sort for sorting 100x elements 10000 times
8-byte: Radix was 0.478098x as fast as std::sort for sorting 150x elements 10000 times
8-byte: Radix was 0.597543x as fast as std::sort for sorting 200x elements 10000 times
8-byte: Radix was 0.586625x as fast as std::sort for sorting 250x elements 10000 times
8-byte: Radix was 1.1104x as fast as std::sort for sorting 500x elements 8000 times
8-byte: Radix was 1.62942x as fast as std::sort for sorting 1000x elements 6000 times
8-byte: Radix was 4.20794x as fast as std::sort for sorting 2500x elements 4000 times
8-byte: Radix was 3.33483x as fast as std::sort for sorting 5000x elements 2000 times
8-byte: Radix was 3.76864x as fast as std::sort for sorting 10000x elements 1000 times
8-byte: Radix was 3.82654x as fast as std::sort for sorting 15000x elements 750 times
8-byte: Radix was 4.1518x as fast as std::sort for sorting 25000x elements 350 times
8-byte: Radix was 4.36152x as fast as std::sort for sorting 50000x elements 200 times
8-byte: Radix was 3.98418x as fast as std::sort for sorting 100000x elements 100 times
8-byte: Radix was 2.90792x as fast as std::sort for sorting 250000x elements 50 times
8-byte: Radix was 3.20388x as fast as std::sort for sorting 500000x elements 25 times
8-byte: Radix was 3.10164x as fast as std::sort for sorting 1000000x elements 10 times
8-byte unsigned: Radix was 0.216799x as fast as std::sort for sorting 50x elements 10000 times
8-byte unsigned: Radix was 0.42467x as fast as std::sort for sorting 75x elements 10000 times
8-byte unsigned: Radix was 0.681782x as fast as std::sort for sorting 100x elements 10000 times
8-byte unsigned: Radix was 0.567947x as fast as std::sort for sorting 150x elements 10000 times
8-byte unsigned: Radix was 0.656909x as fast as std::sort for sorting 200x elements 10000 times
8-byte unsigned: Radix was 0.678207x as fast as std::sort for sorting 250x elements 10000 times
8-byte unsigned: Radix was 1.17008x as fast as std::sort for sorting 500x elements 8000 times
8-byte unsigned: Radix was 1.50917x as fast as std::sort for sorting 1000x elements 6000 times
8-byte unsigned: Radix was 3.68869x as fast as std::sort for sorting 2500x elements 4000 times
8-byte unsigned: Radix was 2.94332x as fast as std::sort for sorting 5000x elements 2000 times
8-byte unsigned: Radix was 3.83103x as fast as std::sort for sorting 10000x elements 1000 times
8-byte unsigned: Radix was 4.18957x as fast as std::sort for sorting 15000x elements 750 times
8-byte unsigned: Radix was 4.37438x as fast as std::sort for sorting 25000x elements 350 times
8-byte unsigned: Radix was 4.71957x as fast as std::sort for sorting 50000x elements 200 times
8-byte unsigned: Radix was 4.522x as fast as std::sort for sorting 100000x elements 100 times
8-byte unsigned: Radix was 2.9651x as fast as std::sort for sorting 250000x elements 50 times
8-byte unsigned: Radix was 3.16908x as fast as std::sort for sorting 500000x elements 25 times
8-byte unsigned: Radix was 3.20806x as fast as std::sort for sorting 1000000x elements 10 times

# Float Tests
4-byte float: Radix was 0.408666x as fast as std::sort for sorting 50x elements 10000 times
4-byte float: Radix was 0.560113x as fast as std::sort for sorting 75x elements 10000 times
4-byte float: Radix was 0.562773x as fast as std::sort for sorting 100x elements 10000 times
4-byte float: Radix was 1.11102x as fast as std::sort for sorting 150x elements 10000 times
4-byte float: Radix was 1.14163x as fast as std::sort for sorting 200x elements 10000 times
4-byte float: Radix was 1.62246x as fast as std::sort for sorting 250x elements 10000 times
4-byte float: Radix was 1.79648x as fast as std::sort for sorting 500x elements 8000 times
4-byte float: Radix was 2.07556x as fast as std::sort for sorting 1000x elements 6000 times
4-byte float: Radix was 7.69905x as fast as std::sort for sorting 2500x elements 4000 times
4-byte float: Radix was 11.3662x as fast as std::sort for sorting 5000x elements 2000 times
4-byte float: Radix was 9.34023x as fast as std::sort for sorting 10000x elements 1000 times
4-byte float: Radix was 8.85225x as fast as std::sort for sorting 15000x elements 750 times
4-byte float: Radix was 10.7065x as fast as std::sort for sorting 25000x elements 350 times
4-byte float: Radix was 11.5605x as fast as std::sort for sorting 50000x elements 200 times
4-byte float: Radix was 10.9237x as fast as std::sort for sorting 100000x elements 100 times
4-byte float: Radix was 11.5482x as fast as std::sort for sorting 250000x elements 50 times
4-byte float: Radix was 7.39393x as fast as std::sort for sorting 500000x elements 25 times
4-byte float: Radix was 8.41218x as fast as std::sort for sorting 1000000x elements 10 times
8-byte float: Radix was 0.198986x as fast as std::sort for sorting 50x elements 10000 times
8-byte float: Radix was 0.354463x as fast as std::sort for sorting 75x elements 10000 times
8-byte float: Radix was 0.441407x as fast as std::sort for sorting 100x elements 10000 times
8-byte float: Radix was 0.498372x as fast as std::sort for sorting 150x elements 10000 times
8-byte float: Radix was 0.591653x as fast as std::sort for sorting 200x elements 10000 times
8-byte float: Radix was 0.810906x as fast as std::sort for sorting 250x elements 10000 times
8-byte float: Radix was 1.22882x as fast as std::sort for sorting 500x elements 8000 times
8-byte float: Radix was 1.15942x as fast as std::sort for sorting 1000x elements 6000 times
8-byte float: Radix was 3.84186x as fast as std::sort for sorting 2500x elements 4000 times
8-byte float: Radix was 3.41463x as fast as std::sort for sorting 5000x elements 2000 times
8-byte float: Radix was 3.75725x as fast as std::sort for sorting 10000x elements 1000 times
8-byte float: Radix was 2.92235x as fast as std::sort for sorting 15000x elements 750 times
8-byte float: Radix was 4.29515x as fast as std::sort for sorting 25000x elements 350 times
8-byte float: Radix was 4.68467x as fast as std::sort for sorting 50000x elements 200 times
8-byte float: Radix was 4.26563x as fast as std::sort for sorting 100000x elements 100 times
8-byte float: Radix was 3.0068x as fast as std::sort for sorting 250000x elements 50 times
8-byte float: Radix was 3.0201x as fast as std::sort for sorting 500000x elements 25 times
8-byte float: Radix was 3.04767x as fast as std::sort for sorting 1000000x elements 10 times
