#include <iostream>
#include "coins.hpp"

using namespace std;

int main() {
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);
    cout << "Initial piggy bank: " << piggyBank << endl;
    cout << "Initial pocket: " << pocket << endl;

    int chipsCost = 149;
    Coins costForChips = coins_required_for_cents(chipsCost);
    Coins coinsUsedForChips = pocket.extract_exact_change(costForChips);
    cout << "Bought chips using pocket" << endl;
    cout << "Chips required the coins: " << coinsUsedForChips << endl;
    cout << "Pocket after paying for chips: " << pocket << endl;

    int transferAmount = 405;
	Coins extractedCoins = coins_required_for_cents(transferAmount);
    Coins coinsToTransfer = piggyBank.extract_exact_change(extractedCoins);
    pocket.deposit_coins(coinsToTransfer);
    cout << "Transferring money to pocket" << endl;
    cout << "Coins for transfer: " << coinsToTransfer << endl;
    cout << "Pocket: " << pocket << endl;
    cout << "Piggy bank: " << piggyBank << endl;

    Coins sofaChange(10, 10, 10, 10);
    piggyBank.deposit_coins(sofaChange);
    cout << "Transferring sofa change to piggy bank" << endl;
    cout << "Sofa: " << sofaChange << endl;
    cout << "Piggy bank: " << piggyBank << endl;

    cout << "Piggy bank total: ";
    print_cents(piggyBank.total_value_in_cents(), cout);
    cout << endl;

    return 0;
}

