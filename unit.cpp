#include "unit.h"
#include <cstdlib>
#include <iostream>

unit::unit() {
    //Location
    x = 0;
    y = 0;
    //Misc.
    hp = 7;
    team = 0;
    initiative = 0;
    moveSpeed = 6; //In D&D, movement is 5 ft per tile. This is given in tiles.
    moveLeft = moveSpeed;
    ranged = false;
    //Attributes
    str = 10;
    dex = 10;
    con = 10;
    intel = 10;
    wis = 10;
    cha = 10;
    //Derived - Misc.
    ac = 10 + ((dex - 10) / 2);
    //Derived - Mods
    strMod = ((str - 10) / 2);
    dexMod = ((dex - 10) / 2);
    conMod = ((con - 10) / 2);
    intelMod = ((intel - 10) / 2);
    wisMod = ((wis - 10) / 2);
    chaMod = ((cha - 10) / 2);
}
unit::unit(int xval, int yval) {
    //Locations
    x = xval;
    y = yval;
    //Misc.
    hp = 7;
    team = 0;
    initiative = 0;
    moveSpeed = 6;//In D&D, movement is 5 ft per tile. This is given in tiles.
    moveLeft = moveSpeed;
    ranged = false;
    //Attributes
    str = 10;
    dex = 10;
    con = 10;
    intel = 10;
    wis = 10;
    cha = 10;
    //Derived - Misc.
    ac = 10 + ((dex - 10) / 2);
    //Derived - Mods
    strMod = ((str - 10) / 2);
    dexMod = ((dex - 10) / 2);
    conMod = ((con - 10) / 2);
    intelMod = ((intel - 10) / 2);
    wisMod = ((wis - 10) / 2);
    chaMod = ((cha - 10) / 2);
}

unit::unit(int xval, int yval, int hpIn,
           int strIn, int dexIn, int conIn,
           int intelIn, int wisIn, int chaIn,
           int teamIn, int moveIn, bool ranged_m) {
    //Locations
    x = xval;
    y = yval;
    //Misc.
    hp = hpIn;
    team = teamIn;
    moveSpeed = moveIn;//In D&D, movement is 5 ft per tile. This is given in tiles.
    moveLeft = moveSpeed;
    ranged = ranged_m;
    //Attributes
    str = strIn;
    dex = dexIn;
    con = conIn;
    intel = intelIn;
    wis = wisIn;
    cha = chaIn;
    //Derived - Misc.
    ac = 10 + ((dex - 10) / 2);
    //Derived - Mods
    strMod = ((str - 10) / 2);
    dexMod = ((dex - 10) / 2);
    conMod = ((con - 10) / 2);
    intelMod = ((intel - 10) / 2);
    wisMod = ((wis - 10) / 2);
    chaMod = ((cha - 10) / 2);
}
int unit::getX() {
    return x;
}
int unit::getY() {
    return y;
}
void unit::setX(int val) {
    x = val;
}
void unit::setY(int val) {
    y = val;
}

//D&D Stat Gets
int unit::getHP() {
    return hp;
}

//===================================================================================
//======================================Attacks======================================
//===================================================================================

bool unit::unarmedAttack(unit* enemy) { //Build a D&D Library for doing this cleaner?
    int attack = std::rand() % 20 + 1 + strMod;
    if (attack > enemy->ac) {
        enemy->hp -= strMod + 1;
        return true;
    } else {
        return false;
    }
}

bool unit::meleeAttack(unit *enemy) {

}

void unit::assignTeam(int val) {
    team = val;
}

int unit::getTeam() {
    return team;
}

int unit::getInitiative() {
        return initiative;
}

int unit::rollInitiative() { //You need to seed this with srand at some point, OUTSIDE the function.
    initiative = (rand()%30000)+1;
    return initiative;
}

int unit::move(int tilesMoved) {
    moveLeft -= tilesMoved;
    return moveLeft;
}

int unit::getMoveSpeed() {
    return moveSpeed;
}

void unit::resetMoveLeft() {
    moveLeft = moveSpeed;
}

/**
 * @brief Access function for private variable hasRanged. If true, the unit has a ranged weapon, like a bow.
 * To find out if the unit has the role of a ranged combatant, use isRanged().
 * @return Whether the unit has a ranged weapon
 */
bool unit::hasRangedWeapon() {
    return hasRanged;
}

/**
 * @brief Access function for private variable ranged. If true, the unit has a ranged role, like an archer.
 * To find out if the unit has a ranged weapon, use hasRangedWeapon().
 * @return Whether the unit is a ranged unit.
 */
bool unit::isRanged() {
    return ranged;
}
