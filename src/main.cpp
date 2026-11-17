#include "../include/menu.h"

int main() {
    int spaceX = 10;
    int spaceY = 5;
    int stackSize = 5;
    Stack stack(stackSize);

    initMenu(spaceX, spaceY, stack);
    return 0;
}