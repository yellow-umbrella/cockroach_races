#include "player.hpp"
#include <algorithm>
#include <iostream>
#include "utilities.hpp"

using namespace std;

Player::Player(int id, int num_races) : money(rand_from_to(min_bet, max_bet)*num_races), id(id), num_wins(0), last_prize(0) {};

int Player::make_bet(int n) {
    if (money == 0) {
        bet_for = -1;
        return 0;
    }
    bet_for = rand()%n;
    bet_with = min(rand_from_to(min_bet, max_bet), money);
    money -= bet_with;
    return bet_with;
}

int Player::get_bet_for() const {
    return bet_for;
}

int Player::get_bet_with() const {
    return bet_with;
}

void Player::add_prize(int prize) {
    money += prize;
    last_prize = prize;
    if (prize > 0) num_wins++;
}

void Player::print_stats() const {
    cout << "\nPlayer №" << id << ":\n";
    cout << "amount of money: " << money << (last_prize > 0 ? "(+"+to_string(last_prize)+")" : "") << "\n";
    cout << "number of wins in races: " << num_wins << "\n";
    cout << "\n";
}