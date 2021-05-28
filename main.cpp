#include <iostream>
#include "board.h"
#include "unit.h"
#include <vector>
#include <time.h>
#include <windows.h>
#include <fstream>
#include "csvparser.h"
#include "game.h"
#include "util.h"

using namespace std;

/* Documentation of known issues:
 * - Crashes if you attempt to attack an empty cell. Implement error handling.
 * - Non-technical issue. I'm going to need a second file for all attacks, which needs to be joined with the
 * existing units.csv stuff, because each creature has different kinds of, and numbers of, abilities.
 * CSV might actually be a terrible format. I'm beginning to wonder how the we make this work.
 * How am I going to design this? Gonna put some thought into it.
 */


int main()
{
    cout << sizeof (int);
    system("pause");
    srand(time(NULL)); //Set time seed for all randomizers to run.
    board mainBoard;
    game DnD(&mainBoard);
    DnD.menu();
}
