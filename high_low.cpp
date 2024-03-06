/*
 *  High Low Game
 *  CSCE 306 - Live Coding 2
 *  Authors: Tyler M. and Camden W.
 *  Description: This game allows for the user to wager on guessing a randomly generated number between 1 and 100.
 *  With each guess, the user is told if they are too high or too low and has 7 attempts to guess the number.
 *  If the number is correctly guessed within 7 attempts, the user is rewarded by the amount that they wagered,
 *  otherwise, the user loses the amount of points that they wagered, and the secret number is revealed.
 *
 *  Note: OpenAI's GPT-3 language model played a role in the development of this program. Throughout the program,
 *  GPT-3's contributions will be highlighted with external resources.
 */

#include "high_low.h"
#include <iostream>
#include <random>
#include <limits>

using namespace std;

// Constructor for the high_low class
high_low::high_low() {
    // Random number generation implementation was assisted by GPT-3.
    // Initialize a random device to obtain seed entropy.
    random_device rd;   // Learn more at https://en.cppreference.com/w/cpp/numeric/random/random_device
    // Create a Mersenne Twister engine with the obtained seed.
    mt19937 gen(rd());  // Learn more at https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    // Define a uniform distribution for integers between 1 and 100.
    uniform_int_distribution<int> dis(1, 100);  // Learn more at https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    secretNumber = dis(gen); // Generate a new random number within the specified range and assign it to secretNumber.
    userBank = 10; // Starting bank with 10 points
    plays = 0;     // Initialize plays to 0.
    wins = 0;      // Initialize wins to 0.
    losses = 0;    // Initialize losses to 0.
}

// Method to start and play the high-low game
void high_low::play() {
    int wager;

    // Introductory Text
    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "A number will be randomly generated. You will guess between numbers 1-100, and I will tell you if your "
            "guess is too high or too low.\nYou have 7 attempts to correctly guess the number. Good Luck!" << endl;

    // Game Flow Loop
    while (true) {
        int guessCount = 0; // Counter for the number of guesses in each round

        cout << "\nYour bank: " << userBank << " points" << endl;

        // Input validation for wager
        while (true) {
            cout << "Enter your wager (0 to exit): ";

            // Check if the input is a valid integer and there is no trailing non-numeric input
            if (cin >> wager && cin.peek() == '\n') {
                // Check if the wager is within valid bounds
                if (wager >= 0 && wager <= userBank) {
                    break; // Exit the loop if the input is valid
                } else {
                    cout << "Invalid wager. Please enter a non-negative integer not exceeding your current bank." << endl;
                }
            } else {
                cout << "Invalid input. Please enter a valid integer." << endl;
                cin.clear(); // Clear the error flag

                // Discard invalid input, including non-numeric characters, until a new line is reached
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }


        // Handle case where user wants to exit game.
        if (wager == 0) {
            cout << "Thanks for playing! Exiting the game." << endl;
            break;
        }

        plays++;

        // Wager system based on guess number
        for (int attempt = 1; attempt <= 7; ++attempt) {
            int guess;
            guessCount++;
            cout << "Guess #" << guessCount << ": ";

            // Input validation for the guess
            while (true) {
                // Check if the input is a valid integer within the range
                if (cin >> guess && guess >= 1 && guess <= 100) {
                    break; // Exit the loop if the input is valid
                } else {
                    cout << "Invalid input. Please enter a number between 1 and 100." << endl;
                    cin.clear(); // Clear the error flag

                    // Discard invalid input, including non-numeric characters
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            // Check if the guess is correct
            if (guess == secretNumber) {
                cout << "Congratulations! You guessed the correct number." << endl;
                wins++;

                // Adjust user's bank based on guess number
                userBank += wager; // Gain the points if the correct guess is made within 7 attempts

                // Initialize a random device to obtain seed entropy.
                random_device rd;
                // Create a Mersenne Twister engine with the obtained seed.
                mt19937 gen(rd());
                // Define a uniform distribution for integers between 1 and 100.
                uniform_int_distribution<int> dis(1, 100);
                // Generate a new random number within the specified range and assign it to secretNumber.
                secretNumber = dis(gen);

                break; // Exit the guessing loop after a correct guess
            } else {
                // Provide feedback to the user about whether their guess was too high or too low
                if (attempt < 7) {
                    cout << "Incorrect guess. ";
                    if (guess < secretNumber) {
                        cout << "Your guess is too low." << endl;
                    } else {
                        cout << "Your guess is too high." << endl;
                    }
                } else {
                    // If the maximum attempts are reached, reveal the secret number and deduct points
                    cout << "Sorry! You have reached the maximum number of attempts. The secret number was: " << secretNumber << endl;
                    losses++;
                    userBank -= wager;
                }
            }
        }

        // Check if the user has run out of points
        if (userBank <= 0) {
            cout << "Game over. You have run out of points." << endl;
            break;
        }
    }

    // Display game summary
    cout << "\nGame Summary:" << endl;
    cout << "Final Points: " << userBank << endl;
    cout << "Total Plays: " << plays << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
}
