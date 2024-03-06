/*
 *  high_low.h
 *  CSCE 306 - Live Coding 2
 *  See source code implementation at high_low.cpp
 *  Authors: Tyler M. and Camden W.
 */

#ifndef INC_306_RACE_1_HIGH_LOW_H
#define INC_306_RACE_1_HIGH_LOW_H

class high_low {
private:
    int secretNumber;
    int userBank;
    int plays;
    int wins;
    int losses;

public:
    high_low(); // Constructor declaration
    void play(); // Member function declaration
};

#endif //INC_306_RACE_1_HIGH_LOW_H
