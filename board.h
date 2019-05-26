#ifndef BOARD_H
#define BOARD_H
#include "unit.h"
#include <vector>

class board
{
private:
    //unit* grid[10][10];//Use Vector in later versions. 2D vector is a vector of vectors.
    std::vector<std::vector<unit*>> grid;
    //int size;
    int sizeX;
    int sizeY;
public:
    board();
    board(int x, int y);
    //bool unitIsAt(unit& dude, int x, int y); //Look into using pair data type instead of x and y for coords?
    unit* whosAt(int x,int y);
    std::vector<unit*> whosIn(int leftX, int topY, int rightX, int botY);
    int getSizeX();
    int getSizeY();
    unit* getUnit(int x, int y);
        //Return 1 if succeeds, 0 if it fails
    void moveUnitAt(int xOrigin,int yOrigin,int xDest,int yDest);
    void moveUnit(unit *dude, int x, int y);
    void unitChanger(unit* dude, int x, int y); //Add a unit or remove it at x,y. Referenced by moveUnit since changer runs twice.
    void drawBoard();
    unit* makeUnitAt(int x, int y);
    void changeSize(int x, int y);
    void createUnit(int x, int y);
    void createUnits(int lowLeftX, int lowLeftY, int upRightX, int upRightY);
    void createUnitAdv(int x, int y, int hp, int str, int dex, int con, int intel, int wis, int cha, int team, int move, bool ranged);
    void removeUnit(int x, int y);
    void removeUnits(int lowLeftX, int lowLeftY, int upRightX, int upRightY);
    void displayBoardHP();
    void rollBoardInitiative();
    //D&D Stat Gets
    int getHP(int x, int y);

    //Attack Functions (Found a way to do this cleaner)
    bool unarmedAttack(int unit1X, int unit1Y, int unit2X, int unit2Y);
};

#endif // BOARD_H
