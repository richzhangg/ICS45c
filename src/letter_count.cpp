#include <iostream>
using namespace std;
#include "letter_count.hpp"

constexpr int N_CHARS = ('Z' - 'A' + 1); // will be 26

int main()
{
	int letter_counts[N_CHARS] = {0};
	std::string line;
    while (std::getline(std::cin, line)) {
        count(line, letter_counts);
		print_counts(letter_counts, N_CHARS);
	}
    return 0;
}	
