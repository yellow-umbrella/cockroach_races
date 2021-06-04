#include "ui.hpp"
#include <time.h>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));
    UI ui;
    ui.start();
    return 0;
}