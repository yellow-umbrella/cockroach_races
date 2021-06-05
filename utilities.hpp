#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include <string>

struct MainPlayer {
    int money = 2000;
    int wins = 0;
    int bet_for = -1;
    int bet_with = 0;
    int last_prize = 0;
};

int input_int(std::string prompt, int min, int max);
void clear_enter();
void clear_time(int seconds);
int rand_from_to(int min, int max);
void print_title();
void print_start();
void print_menu(MainPlayer player);


#endif