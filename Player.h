#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include "Ship.h"
#include "Grid.h"

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

class Player
{
    public:

    //constructor and initializing functions
    Player(bool);
    ~Player();
    void init();
    void AIinit();

    //"Lost" functions
    bool hasLost();
    void setLost();

    //"Name" functions
    void setName(char*);
    string getname();

    //"AI" attribute
    bool isAI();
    int xai; //AI coordinates for attacking
    int yai;

    //ship status printing function
    void shipDeath();

    //Grids
    Grid* gAttack;
    Grid* gDefense;

    private:
    Ship *n1, *n2, *n3, *n4, *n5;

    bool lost;
    string name;
    bool AI;

};

#endif