# condition_number_comparison
A little speed test for two methods of calculating condition number.

Compile with:

g++ -std=c++11 -I /usr/include/eigen3/ comparison.cpp -o comparison

g++ -std=c++11 -I /usr/include/eigen3/ equivalency_test.cpp -o equivalency_test