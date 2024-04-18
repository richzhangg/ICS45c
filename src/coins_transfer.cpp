#include <iostream>
#include "coins.hpp"

using namespace std;

int main() {
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);
    cout << "Initial piggy bank: " << piggyBank << endl;
    cout << "Initial pocket: " << pocket << endl;
	int chips = 149;
    Coins costs = coins_required_for_cents(chips);
    Coins coins_chips = pocket.extract_exact_change(costs);
    cout << "Bought chips using pocket" << endl;
    cout << "Chips required the coins: " << coins_chips << endl;
    cout << "Pocket after paying for chips: " << pocket << endl;
	int transfer = 405;
	Coins extracted = coins_required_for_cents(transfer);
	Coins transfer_coins = piggyBank.extract_exact_change(extracted);
	pocket.deposit_coins(transfer_coins);
	cout << "Transferring money to pocket" << endl;
    cout << "Coins for transfer: " << transfer_coins << endl;
    cout << "Pocket: " << pocket << endl;
    cout << "Piggy bank: " << piggyBank << endl;
	Coins sofa(10, 10, 10, 10);
    piggyBank.deposit_coins(sofa);
    cout << "Transferring sofa change to piggy bank" << endl;
    cout << "Sofa: " << sofa << endl;
    cout << "Piggy bank: " << piggyBank << endl;
	cout << "Piggy bank total: ";
    print_cents(piggyBank.total_value_in_cents(), cout);
    cout << endl;
}
