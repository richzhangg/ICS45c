#include "process_numbers.hpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::istream_iterator<int> start(numbers), end;
    std::vector<int> nums(start, end);
    
    std::sort(nums.begin(), nums.end());

    std::ostream_iterator<int> odds_out(odds, " ");
    std::copy_if(nums.begin(), nums.end(), odds_out, [](int n) { return n % 2 != 0; });
    odds << '\n';

    std::ostream_iterator<int> evens_out(evens, "\n");
    std::copy_if(nums.begin(), nums.end(), evens_out, [](int n) { return n % 2 == 0; });
}

