#ifndef UNIT_H
#define UNIT_H
#include <vector>

//Make monster library class that just has a bunch of functions for creating pregens?
//No no, that's inefficient. Hit some plaintext/csv library.

class unit
{
private:
    //Lord in heaven there is a LOT of variable for each of these, lordy lord.
    //Note: Don't be tempted to use shorts. For caculation, they're actually worse.
    //They save memory but frankly, that's not a concern. Sucks though, considering that
    //I have absolutely no reason to use such large variable for most of these things.

    //Structs
    struct die {
        int size;
        int numberOf;
    };

    //Random Number Generators
    int x;
    int y;
    unsigned int team;

    //D&D Stuff
    int hp;
    int initiative;
    int moveSpeed;
    int moveLeft;
    bool ranged;
    bool hasRanged;

        //Damages
    int unarmedDamage;
    std::vector<die> meleeDamage;
    std::vector<die> rangedDamage;

        //Is using a finesse melee weapon?
    bool finesseMelee;
        //Is hitting with dex for unarmed? (Likely a monk)
    bool finesseUnarmed;

    //Atributes
    int str;
    int dex;
    int con;
    int intel;
    int wis;
    int cha;

    //Derived
    int ac;
    int strMod;
    int dexMod;
    int conMod;
    int intelMod;
    int wisMod;
    int chaMod;
public:
    //Include handling for bodies left on field? Means multiple units in one grid space.
    int getTeam();
    int getX();
    int getY();
    void setX(int val);
    void setY(int val);
    void assignTeam(int val);
    unit(); //Default Constructor
    unit(int xval,int yval); //Default Unit at location constructor
    unit(int xval, int yval, int hpIn, //Advanced Constructor for pulling from file.
         int strIn, int dexIn, int conIn,
         int intelIn, int wisIn, int chaIn,
         int teamIn, int moveIn, bool ranged_m);
    int move(int tilesMoved);
    int getMoveSpeed();
    bool isRanged();
    bool hasRangedWeapon();
    void resetMoveLeft();

    //D&D Stat Gets
    int getHP();
    int getInitiative();
    int rollInitiative();

    //Attacks
    bool unarmedAttack(unit* enemy);
    bool meleeAttack(unit* enemy);
};

#endif // UNIT_H
