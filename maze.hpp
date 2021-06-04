#include <vector>
using namespace std;


struct Point {
    int i, j;
};

class Maze {
public:
    Maze(int n);
    void run();
    void print() const;
    void randomize();
    void destroy_wall(Point p1, Point p2);
    bool can_connect(Point p1, Point p2);
private:
    static const int WIDTH = 10;
    static const int HIGHT = 15;

    struct  Node {
        bool right_wall = 1;
        bool down_wall = 1;
    };
    Node maze[HIGHT][WIDTH];
};

/*

o--o--o--o--o
|* |        |
o  o--o  o--o
|           |
o--o--o--o  o
|           |
o--o--o--o--o

*/