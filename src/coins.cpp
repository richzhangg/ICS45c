#include "coins.hpp"

#include <iostream>

using namespace std;

// all the definitions for Class 'Coins'

Coins::Coins(int q, int d, int n, int p) : quarters(q), dimes(d), nickels(n), pennies(p) {}

int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + nickels * CENTS_PER_NICKEL + pennies * CENTS_PER_PENNY;
}

void Coins::print(std::ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, " << pennies << " pennies";
}

std::ostream& operator<<(std::ostream& out, const Coins& coins) {
    coins.print(out);
    return out;
}

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
    return quarters >= coins.quarters &&
           dimes >= coins.dimes &&
           nickels >= coins.nickels &&
           pennies >= coins.pennies;
}

Coins Coins::extract_exact_change(Coins coins) {
    if (has_exact_change_for_coins(coins)) {
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;
        return coins;
    }
    return Coins(0, 0, 0, 0);
}

Coins coins_required_for_cents(int amount_in_cents) {
    int quarters = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    int dimes = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    int nickels = amount_in_cents / CENTS_PER_NICKEL;
    amount_in_cents %= CENTS_PER_NICKEL;
    int pennies = amount_in_cents;
    return Coins(quarters, dimes, nickels, pennies);
}

void print_cents(int cents, std::ostream& out) {
    out << "$" << cents / 100 << ".";
    int remaining_cents = cents % 100;
    if (remaining_cents < 10) out << '0';
    out << remaining_cents;
}

Coins ask_for_coins(std::ostream& out, std::istream& in) {
    int quarters, dimes, nickels, pennies;
    
    out << "Quarters? ";
    in >> quarters;
    
    out << "Dimes? ";
    in >> dimes;
    
    out << "Nickels? ";
    in >> nickels;
    
    out << "Pennies? ";
    in >> pennies;
    
    return Coins(quarters, dimes, nickels, pennies);
}

void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    
    char choice;
    do {
        out << "Coins Menu\n";
        out << "1. Deposit Change\n";
        out << "2. Extract Change\n";
        out << "3. Print Balance\n";
        out << "4. Exit\n";
        out << "User Input: ";
        in >> choice;
        
        switch(choice) {
            case '1': {
                Coins deposit = ask_for_coins(out, in);
                myCoins.deposit_coins(deposit);
                out << "Thank you!";
				out << "\n";
                break;
            }
            case '2': {
                Coins extraction = ask_for_coins(out, in);
                if (myCoins.has_exact_change_for_coins(extraction)) {
                    myCoins.extract_exact_change(extraction);	
					out << "Thank you!";
					out << "\n";
                } else {
                    out << "ERROR: Insufficient Funds\n";
                }
                break;
            }
            case '3': {
                print_cents(myCoins.total_value_in_cents(), out);
                out << "\n";
				out << "Thank you!";
				out << "\n";
                break;
            }
            case '4':
                break;
            default:
                out << "ERROR: Invalid Command\n";
        }
    } while (choice != '4');
}
