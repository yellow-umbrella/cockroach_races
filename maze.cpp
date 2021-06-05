#include "maze.hpp"
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

void Maze::destroy_wall(Cell p1, Cell p2) {
    if (p1.i == p2.i) {
        if (p1.j > p2.j) {
            swap(p1.j, p2.j);
        }
        maze[p1.i][p1.j].right_wall = 0;
        maze[p2.i][p2.j].left_wall = 0;
    }
    if (p1.j == p2.j) {
        if (p1.i > p2.i) {
            swap(p1.i, p2.i);
        }
        maze[p1.i][p1.j].down_wall = 0;
        maze[p2.i][p2.j].up_wall = 0;
    }
}

void Maze::randomize() {
    set<Cell> tree = {Cell::random(HEIGHT, WIDTH)};
    while (tree.size() < HEIGHT*WIDTH) {
        Cell v = Cell::random(HEIGHT, WIDTH);
        if (tree.count(v)) continue;
        vector<Cell> stack = {v};
        while (!tree.count(stack.back())) {
            Cell neighbor = stack.back().neighbor(HEIGHT, WIDTH);
            int ind = find(stack.begin(), stack.end(), neighbor) - stack.begin();
            stack.resize(ind);
            stack.push_back(neighbor);
        }
        for (int i = 1; i < stack.size(); i++) {
            destroy_wall(stack[i-1], stack[i]);
            tree.insert(stack[i-1]);
        }
    }
}

MainPlayer Maze::run(MainPlayer player) {
    num_cockroaches = input_int("Enter number of cockroaches", 2, 5);
    for (int i = 0; i < num_cockroaches; i++) {
        positions.push_back({0, 0});
        prev_positions.push_back({0, 0});
    }
    main_player = player;
    choose_cockroach();
    clear_enter();
    randomize();
    int winner = -1;
    while (winner == -1) {
        print();
        clear_time(1);
        for (int i = 0; i < num_cockroaches; i++) {
            Cell tmp = change_pos(positions[i], prev_positions[i]);
            prev_positions[i] = positions[i];
            positions[i] = tmp;
            if (positions[i].i == HEIGHT-1 && positions[i].j == WIDTH-1) {
                winner = i;
            }
        }
    }
    print();
    cout << "The cockroach №" << winner << " is the winner!\n";
    if (main_player.bet_for == winner) {
        main_player.money += 1000;
        main_player.wins++;
    }
    cout << "Your money: " << main_player.money << "\n";
    cout << "Your number of wins: " << main_player.wins << "\n";
    return main_player;
}

void Maze::print() const {
    for (int i = 0; i < num_cockroaches; i++) {
        cout << "o  o";
        for (int j = 1; j < WIDTH; j++) {
            cout << "--o";
        }
        cout << "    ";
    }
    cout << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < num_cockroaches; j++) {
            int m = WIDTH;
            if (positions[j].i == i) m = positions[j].j;
            cout << "|";
            for (int k = 0; k < m; k++) {
                if (maze[i][k].right_wall) cout << "  |";
                else cout << "   ";
            }
            if (positions[j].i == i) {
                cout << "* ";
                if (maze[i][m].right_wall) cout << "|";
                else cout << " ";
            }
            for (int k = m+1; k < WIDTH; k++) {
                if (maze[i][k].right_wall) cout << "  |";
                else cout << "   ";
            }
            cout << "    ";
        }
        cout << "\n";
        for (int j = 0; j < num_cockroaches; j++) {
            cout << "o";
            for (int k = 0; k < WIDTH; k++) {
                if (maze[i][k].down_wall) cout << "--o";
                else cout << "  o";
            }
            cout << "    ";
        }
        cout << "\n";
    }
}

Cell Maze::change_pos(Cell a, Cell prev) {
    vector<Cell> neighbors;
    if (maze[a.i][a.j].down_wall + maze[a.i][a.j].up_wall + maze[a.i][a.j].right_wall + maze[a.i][a.j].left_wall == 3) prev = a;
    if (!maze[a.i][a.j].down_wall && (prev.i != a.i+1 || prev.j != a.j)) neighbors.push_back({a.i+1, a.j});
    if (!maze[a.i][a.j].up_wall && (prev.i != a.i-1 || prev.j != a.j)) neighbors.push_back({a.i-1, a.j});
    if (!maze[a.i][a.j].right_wall && (prev.i != a.i || prev.j != a.j+1)) neighbors.push_back({a.i, a.j+1});
    if (!maze[a.i][a.j].left_wall && (prev.i != a.i || prev.j != a.j-1)) neighbors.push_back({a.i, a.j-1});
    return neighbors[rand()%neighbors.size()];
}

void Maze::choose_cockroach() {
    main_player.bet_for = input_int("Choose your cockroach", 0, num_cockroaches-1);
}