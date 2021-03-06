#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include "Player.h"

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

class Game{

    public:
    Player* player1;
    Player* player2;
    static bool newgame ;
    static bool AIactive;
    //int countT; FIXME do we need countT ?

    Game();
    ~Game();
    void initNames();
    void initGame();
    void playGame();
    void askName(char*);
    void attack(Player*, Player*);
    static void ActivateAI();

};

#endif
