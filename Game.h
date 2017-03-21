#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstdlib>

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

//classes prototype
class Point;
class Grid;
class Ship;
class Player;
class Game;

class Point
{

    public:
    Point(int x=0, int y=0); //constructor with default args

    void operator =(Point &p1)
    {
        X=p1.X;
        Y=p1.Y;
        hit=p1.hit;
        ship=p1.ship;
    }


    //"get" functions
    int getX() const;
    int getY() const;
    bool isHit() const;
    bool hasShip()const;
    //"set" functions
    void setCoord(int , int);
    void setHit();
    void setShip();

    private:

    int X; // Position on X axys; Not yet const, only for debug
    int Y; // Position on Y axys; Not yet const, only for debug
    bool hit; //    Stores infos about the state of the point (true=hit)
    bool ship; //    Stores infos about the state of the point (true= there is a ship)
};

class Grid
{

    public:

    Grid(bool);
    Grid();
    ~Grid();
    Point **points;
    void operator =(Grid &);

    void print();

    private:

    int cols;
    int lines;
    bool defense_grid;

};

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
