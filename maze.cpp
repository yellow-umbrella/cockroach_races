#include "maze.hpp"
#include <algorithm>

using namespace std;

Maze::Maze(int n) {

}

void Maze::destroy_wall(Point p1, Point p2) {
    if (p1.i == p2.i) {
        if (p1.j > p2.j) {
            swap(p1.j, p2.j);
        }
        maze[p1.i][p1.j].right_wall = 0;
    }
    if (p1.j == p2.j) {
        if (p1.i > p2.i) {
            swap(p1.i, p2.i);
        }
        maze[p1.i][p1.j].down_wall = 0;
    }
}

bool Maze::can_connect(Point p1, Point p2) {

}

void Maze::run() {
    
}