#ifndef POINT_H
#define POINT_H

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

#endif