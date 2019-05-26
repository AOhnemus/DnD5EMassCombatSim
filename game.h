#ifndef GAME_H
#define GAME_H
#include <vector>
#include "unit.h"
#include "board.h"
#include <fstream>

class game
{
private:
    struct unitEntry {
        std::string name;
        int hp;
        int str;
        int dex;
        int con;
        int intel;
        int wis;
        int cha;
        int move;
    };
    int round;
    std::vector<unit*> initiativeOrder;
    std::fstream units;
    std::vector<unitEntry> unitsVec;
public:
    board* gameBoard;
    game();
    game(board* gameBoardIn);
    void loadInitiative();
    void printIntiatives();
    void runUnitAI(unit* mike);

    //Enemy Finding
    std::vector<unit*> findEnemiesInRange(unit* mike, int range);
    unit* findLowestHP(std::vector<unit*> units_m);

    //Menu and Menu Options
    void menu();
    void menu_changeBoardSize();
    void menu_addUnit();
    void menu_addUnitFromFile();
    void menu_removeUnit();
    void menu_moveUnit();
    void menu_makeUnitAttackAnother();
    void menu_displayUnitStatus();

    void launchGame();
    void unitTakeTurn(unit* smitty);

    void launchGameTest();

    void fileManagementLoop();
    void openUnitsCSV();
    void loadUnits();
};

#endif // GAME_H
