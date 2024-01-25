#include "coins.hpp"

#include <iostream>

using namespace std;

// all the definitions for Class 'Coins'


// Constructor implementation
Coins::Coins(int q, int d, int n, int p) : quarters(q), dimes(d), nickels(n), pennies(p) {}

// Calculate the total value of all coins in cents
int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + nickels * CENTS_PER_NICKEL + pennies * CENTS_PER_PENNY;
}

// Print the coins in the format "x quarters, y dimes, z nickels, n pennies"
void Coins::print(std::ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, " << pennies << " pennies";
}

// Overload the insertion operator to use the print method
std::ostream& operator<<(std::ostream& out, const Coins& coins) {
    coins.print(out);
    return out;
}

// Add coins from another Coins object to this one
void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    dimes += coins.dimes;
    nickels += coins.nickels;
    pennies += coins.pennies;

    // After deposit, the 'coins' object is assumed to be empty
    coins.quarters = 0;
    coins.dimes = 0;
    coins.nickels = 0;
    coins.pennies = 0;
}

// Check if this Coins object can provide the exact change
bool Coins::has_exact_change_for_coins(const Coins& coins) const {
    return quarters >= coins.quarters &&
           dimes >= coins.dimes &&
           nickels >= coins.nickels &&
           pennies >= coins.pennies;
}

// Extract exact change if possible and return a new Coins object with the extracted coins
Coins Coins::extract_exact_change(Coins coins) {
    if (has_exact_change_for_coins(coins)) {
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;
        return coins;  // Return the extracted coins
    }

    // If exact change is not possible, return an empty Coins object
    return Coins(0, 0, 0, 0);
}

// Non-member function to calculate the required coins for a given amount of cents
Coins coins_required_for_cents(int amount_in_cents) {
    int quarters = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    int dimes = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    int nickels = amount_in_cents / CENTS_PER_NICKEL;
    amount_in_cents %= CENTS_PER_NICKEL;
    int pennies = amount_in_cents;  // Remainder are the pennies

    return Coins(quarters, dimes, nickels, pennies);
}

// Non-member function to print the value in dollar format
void print_cents(int cents, std::ostream& out) {
    out << "$" << cents / 100 << ".";
    int remaining_cents = cents % 100;
    if (remaining_cents < 10) out << '0';  // Print an extra '0' if less than 10 cents
    out << remaining_cents;
}

// Ask the user to input the number of coins
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

// The menu interface for user interaction
void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0); // Initialize a Coins object with no coins
    
    char choice;
    do {
        out << "Coins Menu:\n";
        out << "1. Deposit Change\n";
        out << "2. Extract Change\n";
        out << "3. Print Balance\n";
        out << "4. Exit\n";
        out << "User Input: ";
        in >> choice;
        
        switch(choice) {
            case '1': {
                out << "Enter the coins to deposit:\n";
                Coins deposit = ask_for_coins(out, in);
                myCoins.deposit_coins(deposit);
                out << "Deposited " << deposit << "\n";
                break;
            }
            case '2': {
                out << "Enter the coins to extract:\n";
                Coins extraction = ask_for_coins(out, in);
                if (myCoins.has_exact_change_for_coins(extraction)) {
                    Coins extracted = myCoins.extract_exact_change(extraction);
                    out << "Extracted " << extracted << "\n";
                } else {
                    out << "Insufficient coins to extract the desired amount.\n";
                }
                break;
            }
            case '3': {
                out << "Current balance: ";
                print_cents(myCoins.total_value_in_cents(), out);
                out << "\n";
                break;
            }
            case '4':
                out << "Exiting.\n";
                break;
            default:
                out << "Invalid choice, please try again.\n";
        }
    } while (choice != '4');
}
