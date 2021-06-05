#ifndef _UI_HPP_
#define _UI_HPP_

#include "utilities.hpp"

class UI {
public:
    void start();
private:
    void open_menu();
    void open_competition();
    void open_maze();
    MainPlayer main_player;
};

#endif