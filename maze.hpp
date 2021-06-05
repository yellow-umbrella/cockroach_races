#ifndef _MAZE_HPP_
#define _MAZE_HPP_

#include <vector>
#include <cstdlib>
#include "utilities.hpp"
using namespace std;


struct Cell {
    int i, j;
    bool operator<(const Cell& a) const{
        return make_pair(i, j) < make_pair(a.i, a.j);
    }
    bool operator==(const Cell& a) const{
        return make_pair(i, j) == make_pair(a.i, a.j);
    }
    static Cell random(int height, int width) {
        return {rand()%height, rand()%width};
    }
    Cell neighbor(int height, int width) {
        vector<Cell> neighbors;
        if (i + 1 < height) neighbors.push_back({i+1, j});
        if (i - 1 >= 0) neighbors.push_back({i-1, j});
        if (j + 1 < width) neighbors.push_back({i, j+1});
        if (j - 1 >= 0) neighbors.push_back({i, j-1});
        return neighbors[rand()%neighbors.size()];
    }
};

class Maze {
public:
    MainPlayer run(MainPlayer player);
    void print() const;
    void randomize();
    void destroy_wall(Cell p1, Cell p2);
    Cell change_pos(Cell a, Cell prev);
    void choose_cockroach();
private:
    static const int WIDTH = 5;
    static const int HEIGHT = 10;
    int num_cockroaches;
    MainPlayer main_player;
    struct  Node {
        bool right_wall = 1;
        bool down_wall = 1;
        bool left_wall = 1;
        bool up_wall = 1;
    };
    Node maze[HEIGHT][WIDTH];
    vector<Cell> positions;
    vector<Cell> prev_positions;
};

#endif

/*

o--o--o--o--o
|* |        |
o  o--o  o--o
|           |
o--o--o--o  o
|           |
o--o--o--o--o

*/