#ifndef GRID_H
#define GRID_H

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

#endif