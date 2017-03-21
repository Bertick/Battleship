#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include "Point.h"

//removing namespace
using std::string;
using std::vector;
using std::cin;
using std::cout;

//externing global variables
extern WINDOW* title;
extern WINDOW* welcome;
extern WINDOW* attackg;
extern WINDOW* defenseg;
extern WINDOW* outwin;
extern WINDOW* closing;
extern WINDOW* turn;

class Ship
{

    friend class Player;

    private:

    string dir; //says in what direction does the ship develop horizontal or vertical
    int dim; //says ship's dimensions
    bool alive;
    Point **p;
    int X0; //coords of initial point
    int Y0;

    public:

    Ship(int, string);
    bool isAlive();
    void checkPointStatus();
    void isWellPlaced(int, int,bool =true);
    void operator =(Ship &);

};

#endif