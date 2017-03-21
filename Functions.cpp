#include "Functions.h"

void mySleep(float a)
{

    float end_time =clock() + a*CLOCKS_PER_SEC;
    while( clock() <= end_time ){;}
}

void print(WINDOW* win,string s1,int wcolour, int bgcolour) //print function will be used in most classes
{

	int j1, i1;//cursor coordinates
	int j2, i2;//window max lines/cols
	getmaxyx(win,j2,i2);//gets max window size

	if(wcolour>=9||wcolour<0){wcolour=0;}//we have only 9 colours so only 0->8 numbers are accepted
	if(bgcolour>=9||bgcolour<0){bgcolour=0;}

	init_pair(1,colours[wcolour],colours[bgcolour]);//creates colour pair (code, FW colour, BG colour)
	wattron(win,COLOR_PAIR(1));

	for(string::iterator iter=s1.begin(); iter!=s1.end(); iter++)
    {
		getyx(win,j1,i1);//gets cursor position

		if(j1==j2-1){wclear(win); wmove(win,0,0);} //is cursor is at the end of window lets clear it

		waddch(win,*iter); //prints each letter in s1 string
		mySleep(0.01);
	    wrefresh(win); //window refresh
    }
	wattroff(win,COLOR_PAIR(1));
}

void cReturn(WINDOW* win)
{
	int x;
	int y;

	getyx(win,y,x);

	wmove(win,y+1,0);
	wrefresh(win);
}

void cRetafterInput(WINDOW* win)
{
	int x;
	int y;

	getyx(win,y,x);

	wmove(win,y,0);
}

void acquire(int& y, int& x, char p[], string& s)
{
	string lowerCase("abcdefghij");
	string upperCase("ABCDEFGHIJ");
	string numbers("0123456789");

	wgetstr(outwin,p);
	if(p[2]==' ') //if there is a blank space at 3rd position the user is typing A2 or similar
	{
		x=upperCase.find(p[0]);//checks if x is a upper case char
		if(x==-1){x=lowerCase.find(p[0]);}//if x is not upper case the check if is lower case
		if(x==-1){x=numbers.find(p[0]);}//if x neither upper or lower case maybe it's a number

		y=numbers.find(p[1])-1;//converts char to number by finding its position in string

		string s2(p);
		s2.erase(0,3);//removes first 3 characters
		s=s2;
	}
	else if(p[2]=='0') //user is probably typing A10 or similar
	{
		if(p[1]=='1') //user actually typed 10
		{
			x=upperCase.find(p[0]);
			if(x==-1){x=lowerCase.find(p[0]);}
			if(x==-1){x=numbers.find(p[0]);}

			y=9; //9 is the 10th number

			string s2(p);
			s2.erase(0,4);//removes first 4 characters
			s=s2;
		}
		else //user typed something other than 1 and then a 0 ... that's not correct
		{
			x=999; //let's make sure the program fails next ship test
			y=999;
		}
	}
	else //user typed something different than 0 or blank at 3rd space ... that's not correct
	{
		x=999;
		y=999;
	}
}

void acquire(int& y, int& x, char p[])
{
	string lowerCase("abcdefghij");
	string upperCase("ABCDEFGHIJ");
	string numbers("0123456789");

	wgetstr(outwin,p);
	if(p[2]=='0') //user is typing a two digit number
	{
		x=upperCase.find(p[0]);
		if(x==-1){x=lowerCase.find(p[0]);}
		if(x==-1){x=numbers.find(p[0]);}

		y=9;
	}
	else //user is probably typing a one digit number
	{
		x=upperCase.find(p[0]);
		if(x==-1){x=lowerCase.find(p[0]);}
		if(x==-1){x=numbers.find(p[0]);}

		y=numbers.find(p[1])-1;
	}
}
