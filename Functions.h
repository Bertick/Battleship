#ifndef Funct_H
#define Funct_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <curses.h>
#include <ncurses.h>

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

extern int colours[];

void mySleep(float =0.020); //delay
void print(WINDOW*,string,int =0, int =0); //prints a string
void cReturn(WINDOW* ); //acts like std::endl
void cRetafterInput(WINDOW* ); //restore correct cursor position after user input
void acquire(int&, int&, char[], string&); //acquires 2 character and a string, checks if user inputs one digit number or two digit nuber
void acquire(int&, int&, char[]);

#endif
