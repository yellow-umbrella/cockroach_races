#include "ui.hpp"
#include "utilities.hpp"
#include "competition.hpp"
#include "maze.hpp"
#include <iostream>
using namespace std;

void UI::start() {
    print_title();
    clear_enter();
    open_menu();
}

void UI::open_menu() {
    print_menu(main_player);
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
    competition.init(main_player);
    main_player = competition.run();
    clear_enter();
    open_menu();
}

void UI::open_maze() {
    Maze maze;
    main_player = maze.run(main_player);
    clear_enter();
    open_menu();
}