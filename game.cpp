#include "game.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <util.h>
#include <fstream>
#include "csvparser.h"

game::game() {
    round = 0;
    //Game Board Loading Stuff
    gameBoard = new board(20,20);

    //CSV Loading Stuff
    openUnitsCSV();
    loadUnits();
}

game::game(board* gameBoardIn) {
    round = 0;

    //Game Board Loading Stuff
    gameBoard = gameBoardIn;
    loadInitiative();

    //CSV Loading Stuff
    openUnitsCSV();
    loadUnits();
}

void game::loadInitiative() {
    int i,j;
    int counter = 0;
    //Clean this crap up.
    for (i = 0; i < gameBoard->getSizeY();i++) {
        for (j = 0; j < gameBoard->getSizeX();j++) {
            unit* mike = gameBoard->whosAt(j,i);
            if (mike == nullptr) {
                //Do nothing. Should try to write this more clean.
            } else if (counter == 0) {
                initiativeOrder.push_back(mike);
                counter++;
                //If the initiative of the last element in intiativeOrder is smaller than
                //Mike's, put Mike at the end.
            } else if (mike->getInitiative() > initiativeOrder.back()->getInitiative()) {
                initiativeOrder.push_back(mike);
                //If the initiative of the last element in intiativeOrder
                //is larger than Mike's, check the next element.
            } else if (mike->getInitiative() < initiativeOrder.back()->getInitiative()) {
                std::vector<unit*>::iterator it;
                for (it = initiativeOrder.begin(); it != initiativeOrder.end(); it++) {
                    unit* item = *it; //Necessary to stop compile error.
                    if (mike->getInitiative()< item->getInitiative()) {
                        initiativeOrder.insert(it,mike);
                        break;
                    }
                }
            }
        }
    }
}

void game::printIntiatives() {
    std::vector<unit*>::iterator it;
    for (it = initiativeOrder.begin(); it != initiativeOrder.end(); it++) {
        unit* item = *it; //Necessary to stop compile error.
        std::cout << item->getInitiative() << ", ";
    }
    std::cout << std::endl;
}

void game::runUnitAI(unit* mike) {
    //Is unit in melee?

}

std::vector<unit*> game::findEnemiesInRange(unit* mike, int range) {
    //This appears to be crashing.
    int x = mike->getX();
    int y = mike->getY();
    int leftX, rightX, topY, botY;
    std::vector<unit*> units_m;
    std::vector<unit*>::iterator it;
    //std::vector<unit*> unitsInRange; Unused currently.

    //==========================================//
    //===============Find Borders===============//
    //==========================================//

    //=====Assign Left X Border=====//
    if (x-range <= 0) {
        leftX = 0;
    } else {
        leftX = x-range;
    }
    //=====Assign Right X Border====//
    if (x+range >= gameBoard->getSizeX()) {
        rightX = gameBoard->getSizeX();
    } else {
        rightX = x+range;
    }
    //=====Assign Top Y Border=====//
    if (y+range >= gameBoard->getSizeY()) {
        topY = gameBoard->getSizeY();
    } else {
        topY = y+range;
    }
    //=====Assign Bottom Y Border=====//
    if (y-range <= 0) {
        botY = 0;
    } else {
        botY = y-range;
    }
    //===============Check Board================//
    units_m = gameBoard->whosIn(leftX, topY, rightX, botY);
    std::cout << units_m.size() << std::endl;
    //=============Clean up Vector==============//
    //int tarX, tarY;
    std::vector<unit*> unitsReturn;
    for(it = units_m.begin(); it != units_m.end();++it) {
//      if(units.size() == 0) {break;}
        unit* billy = *it;
        if (billy != nullptr) {
            std::cout << billy->getX() << ", " << billy->getY() << std::endl;
            //If unit isn't itself, and isn't on the same team, add to list.
            if (billy->getX() == x && billy->getY() == y) {
                //Do Nothing. This is a stupid way of doing this but I can't think of another.
            } else if (billy->getTeam() != mike->getTeam()) {
                unitsReturn.push_back(billy);
            }
        }
    }
    std::cout << units_m.size() << std::endl;
    return unitsReturn;
}

void game::menu() {
    util utility;
    bool exit = false;
    while (exit == false) {
        utility.ClearScreen();
        //General Variables
        int input;
        gameBoard->drawBoard();
        std::cout << "1: Change board size" << std::endl;
        std::cout << "2: Add Unit" << std::endl;
        std::cout << "3: Add Unit from File" << std::endl;
        std::cout << "4: Remove Unit" << std::endl;
        std::cout << "5: Move Unit" << std::endl;
        std::cout << "6: Make one unit attack another" << std::endl;
        std::cout << "7: Display unit statuses" << std::endl;
        std::cout << "8: File Management" << std::endl;
        std::cout << "9: Launch Game" << std::endl;
        std::cout << "0: Exit Program." << std::endl;
        //Error Handling
        while (true) {
            std::cin >> input;
            if (!std::cin) {
                std::cout << "Invalid Input." << std::endl;
                std::cin.clear();
                std::cin.ignore(); //This works but returns an errror msg and runs for every char.
            }
            else
                break;
        }
        utility.ClearScreen();
        switch (input) {
        case 1 : //Change Board Size
            menu_changeBoardSize();
            break;
        case 2 : //Add Unit
            menu_addUnit();
            break;
        case 3 : //Add Unit from File
            menu_addUnitFromFile();
            break;
        case 4 : //Remove Unit
            menu_removeUnit();
            break;
        case 5 : //Move Unit
            menu_moveUnit();
            break;
        case 6 : //Make one unit attack another
            menu_makeUnitAttackAnother();
            break;
        case 7 : //Display HP of all units
            menu_displayUnitStatus();
            break;
        case 8 : //File Management
            fileManagementLoop();
            break;
        case 9 : //Launch Game
            launchGameTest();
            break;
        case 0 : //Exit
            exit = true;
            break;
        default :
            gameBoard->drawBoard();
            std::cout << "Invalid." << std::endl;
            break;
        }
    }
    std::cout << "Goodbye!" << std::endl;
}

void game::menu_changeBoardSize() {
    int x, y;
    gameBoard->drawBoard();
    std::cout << "Enter dimensions, X Y, separated by a whitesapce" << std::endl;
    std::cout << "> ";
    std::cin >> x >> y;
    //Move to functions so it can ask for input and handle errors. Also I'm
    //copy pasting this a lot.
    gameBoard->changeSize(x,y);
}

void game::menu_addUnit() {
    int x, y;
    gameBoard->drawBoard();
    std::cout << "Enter unit location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x >> y;
    gameBoard->createUnit(x,y);
}

void game::menu_addUnitFromFile() { //Aint done yet.
    int x, y;
    gameBoard->drawBoard();
    std::cout << "Enter unit location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x >> y;

    gameBoard->createUnit(x,y);
}

void game::menu_removeUnit() {
    int x, y;
    gameBoard->drawBoard();
    std::cout << "Enter unit location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x >> y;
    gameBoard->removeUnit(x,y);
}

void game::menu_moveUnit() {
    int x, y, x2, y2;
    gameBoard->drawBoard();
    std::cout << "Enter existing unit location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x >> y;
    std::cout << "Enter destination, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x2 >> y2;
    gameBoard->moveUnitAt(x,y,x2,y2);
}

void game::menu_makeUnitAttackAnother() {
    int x, y, x2, y2, defendHP;
    bool hit;
    gameBoard->drawBoard();
    std::cout << "Enter attacker's location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x >> y;
    std::cout << "Enter defender's location, X Y, separated by a whitesapce" << std::endl;
    std::cin >> x2 >> y2;
    defendHP = gameBoard->getHP(x2,y2);
    hit = gameBoard->unarmedAttack(x,y,x2,y2);
    if (hit) {
        std::cout << "Successful hit." << std::endl;
        std::cout << "Defender HP reduced from " << defendHP << " to " << gameBoard->getHP(x2,y2) << std::endl;
    } else {
        std::cout << "Attack missed." << std::endl;
    }
    system("pause");
}

void game::menu_displayUnitStatus() {
    gameBoard->drawBoard();
    gameBoard->displayBoardHP();
    system("pause");
}

void game::launchGame() {
    //Load up necessary variables

    //
}

void game::unitTakeTurn(unit* smitty) {
   //Setting up variables...
    int move = smitty->getMoveSpeed();
    std::vector<unit*> enemiesInMelee = findEnemiesInRange(smitty, 1);
    std::vector<unit*> enemiesInMovement = findEnemiesInRange(smitty, move);

    //Is an enemy in melee?

    //Yes, enemy in melee
    if(enemiesInMelee.size() >= 1) {
        //Attack enemy in melee with lowest HP
        //Find lowest HP
        unit* weakest = findLowestHP(enemiesInMelee);
        //smitty->;

    //No, no enemies in melee
    } else {
       //Am I a ranged unit?
       if (smitty->isRanged()) {
           //Is an enemy within my normal range?

       //Can I move toward my closest enemy?
       } else if (move >= 1) {
           //Move towards nearest enemy

       //Do I have a ranged weapon?
       } else if (smitty->hasRangedWeapon()) {
           //
        //I can't do anything
        } else {
           //Do nothing.
       }
    }



   //Can I move towards my closest enemy?
        //Yes
        //No

   //Do I have a ranged weapon?
        //Yes
        //No

   //Do nothing
}

void game::launchGameTest() {
    loadInitiative();
    std::vector<unit*> units_m;
    gameBoard->createUnitAdv(5,5,10,10,10,10,10,10,10,1,6, false);
    unit* mike = gameBoard->getUnit(5,5);
    std::cout << "Welcome to the main game's testing system!" << std::endl;
    std::cout << "Beginning tests: " << std::endl;

    //NearestEnemy Test
    std::cout << "Nearest Enemy Test" << std::endl;
    std::cout << "Mike's Origin: " << mike->getX() << ", " << mike->getY() << std::endl;
    units_m = findEnemiesInRange(mike, 6);
    std::cout << "List built. Beginning loop." << std::endl;
    std::cout << "Number of Units: " << units_m.size() << std::endl;
    for(unsigned int i = 0; i < units_m.size(); i++) {
        int tarX = units_m[i]->getX();
        int tarY = units_m[i]->getY();
        std::cout << "Potential Target: " << std::endl;
        std::cout << "X: " << tarX << "Y: " << tarY << std::endl;
    }
        system("pause");
}

void game::fileManagementLoop() {
    bool exit = false;
    while (exit == false) {
        //Variables
        int input;
        int str, dex, con, intel, wis, cha, hp;
        int move;
        std::string name, atkName;
        int dmgDie, dmgDiceCount, range;

        //Menu
        std::cout << "File Manager" << std::endl << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Add new entry to units.csv" << std::endl;
        std::cout << "2. Add new entry to attacks.csv" << std::endl;

        //Input and error checking
        while (true) {
            std::cin >> input;
            if (!std::cin) {
                std::cout << "Invalid Input." << std::endl;
                std::cin.clear();
                std::cin.ignore(); //This works but returns an errror msg and runs for every char.
            } else
                break;
        }

        //Switch and Cases
        switch (input) {

        case 0 : //Exit
            exit = true;
            break;

        case 1 : //Units
            std::cout << "Enter unit name" << std::endl;
            std::cin >> name;
            std::cout << "Enter HP for " << name << std::endl;
            std::cin >> hp;
            std::cout << "Enter Str, Dex, Con, Int, Wis, and Cha, separated by whitespace" << std::endl;
            std::cin >> str >> dex >> con >> intel >> wis >> cha;
            std::cout << "Enter unit movement speed in feet" << std::endl;
            std::cin >> move;
            units<<name<<','<<hp<<','<<str<<','<<dex<<','<<con<<','<<intel<<','<<wis<<','<<cha<<','<<move<<'\n';
            //Need to hook this up to the CSV Parser.
            break;

        case 2 : //Attacks
            std::cout << "Enter attack name" << std::endl;
            std::cin >> atkName;
            std::cout << "Enter the unit this attack is associated with" << std::endl;
            std::cin >> name;
            std::cout << "Enter the attack's range. 5 for melee, 10 for melee with reach 1, etc." << std::endl;
            std::cin >> range;
            std::cout << "Enter the attack's die size" << std::endl;
            std::cin >> dmgDie;
            std::cout << "Enter the number of dice the attack uses" << std::endl;
            std::cin >> dmgDiceCount;
            std::cout << name<<','<<atkName<<','<<range<<','<<dmgDie<<','<<dmgDiceCount<<std::endl;
            std::cout << "Outputed to console for debugging. csv file output not implemented." << std::endl;
            break;
        }
    }
}

void game::openUnitsCSV() {
    //File Loading
    units = std::fstream("units.csv", std::ios::app);
    if (units.is_open()) {
        std::cout << "Units.csv is loaded" << std::endl;
    } else {
        std::cout <<"Units.csv has failed to load" << std::endl;
    }
    system("pause");
}

void game::loadUnits() {
    //=============================================//
    //===============CSVParser Stuff===============//
    //=============================================//
    CsvParser *csvparser = CsvParser_new("units.csv", ",", false);
    CsvRow *row;
    while ((row = CsvParser_getRow(csvparser)) ) {
        const char **rowFields = CsvParser_getFields(row);
        unitEntry newUnit;
        newUnit.name=       rowFields[0];
        newUnit.hp=atoi(    rowFields[1]);
        newUnit.str=atoi(   rowFields[2]);
        newUnit.dex=atoi(   rowFields[3]);
        newUnit.con=atoi(   rowFields[4]);
        newUnit.intel=atoi( rowFields[5]);
        newUnit.wis=atoi(   rowFields[6]);
        newUnit.cha=atoi(   rowFields[7]);
        newUnit.move=atoi(  rowFields[8]);
        unitsVec.push_back(newUnit);
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);
}

unit* game::findLowestHP(std::vector<unit *> units_m) {
    unit* candidate = units_m[0];
    for(unsigned int i = 1; i <= units_m.size(); i++) {
        if (units_m[i]->getHP() < candidate->getHP()) {
            candidate = units_m[i];
        }
    }
    return candidate;
}
