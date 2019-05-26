#include "board.h"
#include <iostream>

board::board() {
    //Should default size be just like, 1x1?
    sizeX = 20;
    sizeY = 20;
    //generator = new std::mt19937;
    grid.resize(sizeY);
    for (int i = 0; i < sizeY; i++) {
        grid[i].resize(sizeX);
        for (int j = 0; j < sizeX; j++) {
            grid[i][j] = nullptr;
        }
    }
}

board::board(int x, int y) {
    sizeX = x;
    sizeY = y;
    grid.resize(sizeY);
    for (int i = 0; i < sizeY; i++) {
        grid[i].resize(sizeX);
        for (int j = 0; j < sizeX; j++) {
            grid[i][j] = nullptr;
        }
    }
}

unit* board::whosAt(int x, int y) {
    return grid[x][y];
}

int board::getSizeX() {
    return sizeX;
}
int board::getSizeY() {
    return sizeY;
}

unit* board::getUnit(int x, int y) {
    return grid[y][x];
}

void board::moveUnitAt(int xOrigin, int yOrigin, int xDest, int yDest) {
    unit* dude = whosAt(xOrigin,yOrigin);
    unitChanger(nullptr, xOrigin, yOrigin);
    unitChanger(dude, xDest, yDest);
}

void board::moveUnit(unit* dude, int x, int y) {
    unitChanger(nullptr, dude->getX(), dude->getY());
    unitChanger(dude, x, y);
    dude->setX(x);
    dude->setY(y);
}

void board::unitChanger(unit* dude, int x, int y) {
    grid[y][x] = dude;//Wait why is it x y?
}

void board::drawBoard() {
    std::cout << std::endl;
    for( int i = sizeY-1; i >= 0; i-- ) {
        for(int j = 0; j < sizeX; j++) {
            if (grid[i][j] == nullptr)
                std::cout << '-';
            else
                std::cout << '@';
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

unit* board::makeUnitAt(int x, int y) {
    unit* dude = new unit(x, y);
    unitChanger(dude, x, y);
    return dude;
}

void board::changeSize(int x, int y) {
    sizeX = x;
    sizeY = y;
    grid.resize(sizeY);
    for (int i = 0; i < sizeY; i++) {
        grid[i].resize(sizeX);
    }
    //Note: This function can create a memory leak.
}

void board::createUnit(int x, int y) {
    grid[y][x] = new unit(x,y); //Due to this being on the stack, look out for memory leaks.
}

void board::createUnits(int lowLeftX, int lowLeftY, int upRightX, int upRightY) {
    for (int i = lowLeftY; i <= upRightY; i++) {
        for (int j = lowLeftX; j <= upRightX; j++ ) {
            createUnit(j,i);
        }
    }
}

void board::removeUnit(int x, int y) {
    delete grid[y][x];
    grid[y][x] = nullptr;
}

void board::removeUnits(int lowLeftX, int lowLeftY, int upRightX, int upRightY) {
    for (int i = lowLeftY; i <= upRightY; i++) {
        for (int j = lowLeftX; j <= upRightX; j++ ) {
            removeUnit(j,i);
        }
    }
}

bool board::unarmedAttack(int unit1X, int unit1Y, int unit2X, int unit2Y) {
    //Distance handling
    if (abs(unit2X - unit1X) > 1 || abs(unit2Y - unit1X) > 1) {
        return false;
    }
    bool result = grid[unit1Y][unit1X]->unarmedAttack(grid[unit2Y][unit2X]);
    return result;
}

int board::getHP(int x, int y) {
    return grid[y][x]->getHP();
}

void board::displayBoardHP() {
    for( int i = sizeY-1; i >= 0; i-- ) {
        for(int j = 0; j < sizeX; j++) {
            if (grid[i][j] != nullptr) {
                std::cout << "Unit at " << j << ", " << i << "     ";
                std::cout << "HP: " << grid[i][j]->getHP();
                std::cout << std::endl;
            }
        }
    }
}

void board::createUnitAdv(int x, int y, int hp, int str, int dex, int con, int intel, int wis, int cha, int team, int move, bool ranged) {
    grid[y][x] = new unit(x,y,hp,str,dex,con,intel,wis,cha,team,move,ranged);
}

void board::rollBoardInitiative() {
    std::vector<int> rolls;
    std::vector<int>::iterator it;
    rolls.push_back(0); //Dummy variable to make the later loop actually work. Works for me.
    int roll;
    for(int i = sizeY-1; i >= 0; i-- ) {
        for(int j = 0; j < sizeX; j++) {
            bool duplicate = true;
//            std::cout <<"A ";
            if (grid[i][j] != nullptr) {
//                std::cout << "B ";
                do {
//                    std::cout << "C ";
                    roll = grid[i][j]->rollInitiative();
//                    std::cout << "D ";
                    //Prevents duplicate values.
                    for (it = rolls.begin(); it != rolls.end();++it) {
//                        std::cout << "E ";
                        if (*it == roll) {
//                            std::cout << "X ";
                            break;
                        }
                        duplicate = false; //If the if statement isn't triggered, leave loop.
                    }
                } while (duplicate == true);
                rolls.push_back(roll);
//                std::cout << "Y ";
            }
        }
    }
}

std::vector<unit*> board::whosIn(int leftX, int topY, int rightX, int botY) {
    std::vector<unit*> units;
    for(int i = topY; i >= botY; i-- ) {
        for(int j = leftX; j <= rightX; j++) {
            if (grid[i][j] != nullptr) {
                units.push_back(grid[i][j]);
            }
        }
    }
    return units;
}
