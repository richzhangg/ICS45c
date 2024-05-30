#include "process_numbers.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::vector<int> nums((std::istream_iterator<int>(numbers)), std::istream_iterator<int>());

    std::sort(nums.begin(), nums.end());

    std::for_each(nums.begin(), nums.end(), [&](int x) {
        if (x % 2 != 0) {
            odds << x << " ";
        }
    });

    odds << std::endl;

    std::for_each(nums.begin(), nums.end(), [&](int x) {
        if (x % 2 == 0) {
            evens << x << std::endl;
        }
    });
}

