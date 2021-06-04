#include "cockroach.hpp"
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

Cockroach::Cockroach(int id) : num_eyes(MAX_NUM_EYES), num_legs(MAX_NUM_LEGS), ticks_until_awake(0),
                                xp(rand()%MAX_XP), x(0), velocity(0), id(id) {}

int Cockroach::get_coord() {
    return x;
}

void Cockroach::randomize() {
    if (ticks_until_awake) {
        ticks_until_awake--;
        if (ticks_until_awake == 0) xp++;
    } else {
        int t = rand()%7;
        if (t == 0 && num_legs > 0) {
            num_legs--;
            cout << "The cockroach №" << id << " has lost its leg.\n";
        }
        if (t == 1 && num_eyes > 0) {
            num_eyes--;
            cout << "The cockroach №" << id << " has lost its eye.\n";
        }
        if (t == 2 || (num_eyes == 0 && t == 3)) {
            ticks_until_awake = 3;
            cout << "The cockroach №" << id << " has hit its head.\n";
        }
    }
}

void Cockroach::move() {
    if (ticks_until_awake == 0) {
        velocity = num_legs*num_eyes + xp;
    } else {
        velocity = 0;
    }
    x += velocity;
}

bool Cockroach::can_move() const {
    return (num_legs*num_eyes + xp);
}

void Cockroach::print_stats(bool is_racing) const{
    cout << "\n";
    cout << "Cockroach №" << id << ":\n";
    cout << "number of legs: " << num_legs << "  ";
    cout << "number of eyes: " << num_eyes << "  ";
    cout << "experience: " << xp << "  ";
    if (is_racing) {
        cout << "is sleeping: " << (ticks_until_awake == 0 ? "no  " : "yes  ");
        cout << "curent coordinate: " << x;
    }
    cout << "\n\n";
}

void Cockroach::print_track(int track_length) const {
    for (int i = 0; i < x; i++) {
        cout << "_";
    }
    cout << "*";
    for (int i = x + 1; i <= track_length; i++) {
        cout << "_";
    }
    cout << "\n";
}