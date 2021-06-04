#include "ui.hpp"
#include "utilities.hpp"
#include "competition.hpp"
#include "maze.hpp"
#include <iostream>
using namespace std;

UI::UI() : money(2000) {}

void UI::start() {
    print_title();
    clear_enter();
    open_menu();
}

void UI::open_menu() {
    print_menu();
    int command = input_int("Choose option", 0, 2);
    clear_time(0);
    if (command == 1) {
        open_competition();
    }
    if (command == 2) {
        open_maze();
    }
}

void UI::open_competition() {
    Competition competition;
    competition.init(money);
    money = competition.run();
    clear_enter();
    open_menu();
}

void UI::open_maze() {
    Maze maze(3);
    maze.run();
    clear_enter();
    open_menu();
}