#include "coins.hpp"

#include <iostream>

using namespace std;

// all the definitions for Class 'Coins'
Coins::Coins(int q, int d, int n, int p): quarters(q), dimes(d), nickels(n), pennies(p) {}

void Coins::deposit_coins(Coins& coins) {
	quarters += coins.quarters;
	dimes += coins.dimes;
	nickels += coins.nickels;
	pennies += coins.pennies;
	coins.quarters = 0;
	coins.dimes = 0;
	coins.nickels = 0;
	coins.pennies = 0;
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const {
	if (quarters >= coins.quarters && dimes >= coins.dimes && nickels >= coins.nickels && pennies >= coins.pennies) {
		return true;
	} else {
		return false;
	}
}

Coins Coins::extract_exact_change(const Coins& coins) {
	if (quarters >= coins.quarters && dimes >= coins.dimes && nickels >= coins.nickels && pennies >= coins.pennies) {
		quarters -= coins.quarters;
		dimes -= coins.dimes;
		nickels -= coins.nickels;
		pennies -= coins.pennies;
		return Coins(coins.quarters, coins.dimes, coins.nickels, coins.pennies);
	} else {
		return Coins(0,0,0,0);
	}	
}

int Coins::total_value_in_cents() const {
	int total = 0;
	total += 25 * quarters;
	total += 10 * dimes;
	total += 5 * nickels;	
	total += pennies;	
	return total;
}

// format: "6 quarters, 2 dimes, ..."
void Coins::print(std::ostream& out) const {
	out << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, " << pennies << " pennies";
}

std::ostream& operator<<(std::ostream& out, const Coins& coins) {
	coins.print(out);
	return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
	int quarters = amount_in_cents / 25;
	amount_in_cents %= 25;
	int dimes = amount_in_cents / 10;
	amount_in_cents %= 10;
	int nickels = amount_in_cents / 5;
	amount_in_cents %= 5;
	int pennies = amount_in_cents;
	return Coins(quarters, dimes, nickels, pennies);
}

void print_cents(int cents, std::ostream& out) {
	out << "$" << cents/100 << ".";
	int remaining = cents % 100;
	if (remaining < 10) out << '0';
	out << remaining;
}

Coins ask_for_coins(std::istream& in, std::ostream& out) {
	int quarters, dimes, nickels, pennies;
	out << "Quarters? ";
	in >> quarters;
	out << "Dimes? ";
	in >> dimes;
	out << "Nickels? ";
	in >> nickels;
	out << "Pennies? ";
	out << pennies;
	return Coins(quarters, dimes, nickels, pennies);
}

void coins_menu(std::istream& in, std::ostream& out) {
	Coins bank(0,0,0,0);
	out << "Coins Menu" << endl;
	out << endl;

	int choice = 0;
	while (choice != 4) {
		out << "1. Deposit Change" << endl;
		out << "2. Extract Change" << endl;
		out << "3. Print Balance" << endl;
		out << "4. Exit" << endl;
		out << endl;
		out << "User Input: ";
		in >> choice;

		if (choice == 1) {
			Coins deposit = ask_for_coins(in, out);
			bank.deposit_coins(deposit);
			out << endl;
            out << "Thank you!" << endl;
            out << endl;
		} else if (choice == 2) {
			Coins extract = ask_for_coins(in, out);
			out << endl;
            out << "Thank you!" << endl;
            out << endl;
			if (extract.has_exact_change_for_coins(bank)) {
				bank.extract_exact_change(extract);
			} else {
				out << "ERROR: Insufficient Funds" << endl;
			}
		} else if (choice == 3) {
			print_cents(bank.total_value_in_cents(), out);
			out << endl;
			out << endl;
            out << "Thank you!" << endl;
            out << endl;
		} else if (choice == 4) {
			break;
		} else {
			out << "ERROR: Invalid Command" << endl;
			out << endl;
		}
	}
}
