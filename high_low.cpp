// high_low.cpp

#include "high_low.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

high_low::high_low() {
    srand(time(0)); // Seed for random number generation
    secretNumber = rand() % 100 + 1; // Secret number between 1 and 100
    userBank = 10; // Starting bank with 10 points
    plays = 0;
    wins = 0;
    losses = 0;
}

void high_low::play() {
    int wager;

    cout << "Welcome to the Number Guessing Game!" << endl;

    while (true) {
        int guessCount = 0; // Counter for the number of guesses in each round

        cout << "\nYour bank: " << userBank << " points" << endl;
        cout << "Enter your wager (0 to exit): ";
        cin >> wager;

        if (wager == 0) {
            cout << "Thanks for playing! Exiting the game." << endl;
            break;
        }

        if (wager > userBank) {
            cout << "Invalid wager. Your wager cannot exceed your current bank." << endl;
            continue;
        }

        plays++;

        // Wager system based on guess number
        while (true) {
            int guess;
            guessCount++;
            cout << "Guess #" << guessCount << ": ";
            cin >> guess;

            if (guess < 1 || guess > 100) {
                cout << "Invalid guess. Please enter a number between 1 and 100." << endl;
                continue;
            }

            if (guess == secretNumber) {
                cout << "Congratulations! You guessed the correct number." << endl;
                wins++;

                // Adjust user's bank based on guess number
                if (guessCount <= 5) {
                    userBank += wager * 2; // Double the points if guess count is 5 or lower
                } else {
                    userBank -= wager; // Lose the points if guess count is more than 5
                }

                secretNumber = rand() % 100 + 1; // Generate a new secret number for the next round
                break; // Exit the guessing loop after a correct guess
            } else {
                // Provide feedback to the user about whether their guess was too high or too low
                if (guess < secretNumber) {
                    cout << "Your guess is too low." << endl;
                } else {
                    cout << "Your guess is too high." << endl;
                }
            }
        }

        if (userBank <= 0) {
            cout << "Game over. You have run out of points." << endl;
            break;
        }
    }

    cout << "\nGame Summary:" << endl;
    cout << "Final Points: " << userBank << endl;
    cout << "Total Plays: " << plays << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
}

