#include <iostream>
#include "coins.hpp"

int main() {
    // Initialize two Coins objects: piggyBank and pocket
    Coins piggyBank(50, 50, 50, 50); // Piggy bank with 50 of each coin
    Coins pocket(8, 3, 6, 8);        // Pocket with some coins

    // Display initial state
    std::cout << "Initial piggy bank: " << piggyBank << std::endl;
    std::cout << "Initial pocket: " << pocket << std::endl;

    // Simulate buying chips using coins from the pocket
    constexpr int CENTS_FOR_CHIPS = 149; // Cost of chips in cents
    Coins chips_payment = pocket.extract_change(coins_required_for_cents(CENTS_FOR_CHIPS));
    std::cout << "Bought chips using pocket" << std::endl;
    std::cout << "Chips required the coins: " << chips_payment << std::endl;
    std::cout << "Pocket after paying for chips: " << pocket << std::endl;

    // Transfer coins from piggyBank to pocket
    constexpr int CENTS_TO_TRANSFER = 405; // Amount to transfer in cents
    Coins transfer = piggyBank.extract_change(coins_required_for_cents(CENTS_TO_TRANSFER));
    pocket.deposit_coins(transfer);
    std::cout << "Transferred " << transfer << " to pocket" << std::endl;
    std::cout << "Pocket: " << pocket << std::endl;
    std::cout << "Piggy bank: " << piggyBank << std::endl;

    // Simulate finding change in the sofa and depositing to piggyBank
    Coins sofa(10, 10, 10, 10); // Coins found in the sofa
    piggyBank.deposit_coins(sofa);
    std::cout << "Transferred sofa change to piggy bank" << std::endl;
    std::cout << "Sofa: " << sofa << std::endl; // Should be empty now
    std::cout << "Piggy bank: " << piggyBank << std::endl;

    // Print the total value in the piggyBank
    std::cout << "Piggy bank total: ";
    print_cents(piggyBank.total_value_in_cents(), std::cout);
    std::cout << std::endl;

    return 0;
}

