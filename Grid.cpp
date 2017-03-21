//HAL 9000 is watching you
#include "Functions.h"
#include "Game.h"

Grid::Grid(bool status):cols(23),lines(12)
{

    //sets the grid type (attack or defense)
    defense_grid = status;

    //dynamic allocation of the grid
    points=new Point*[10];
    for(int i=0; i<10; i++)
    {
        points[i]=new Point[10];
    }

    //lets initialize the points
    for(int j=0; j<10; j++)
    {
        for(int i=0; i<10; i++)
        {
            points[i][j].setCoord(i,j);
        }
    }
}

Grid::~Grid(){

    //remove the grid from memory
    for(int i=0; i<10;i++)
    {
        delete[] points[i];
    }
    delete[] points;

}

void Grid::print(){

    string nhead(" 1 2 3 4 5 6 7 8 910");//standard header string
    string chead("ABCDEFGHIJ");

    WINDOW* myPos;//pointer to print window

    int i=0, j=0; //iteration variables
    float t = 0.0010; //delay between prints

    //defense grid should be on the left
    if(defense_grid)
    {

        myPos=defenseg;
        wmove(myPos,0,7);
        waddstr(myPos,"Defense Grid");
    }
    //attack grid should be on the right
    else
    {

    	myPos=attackg;
        wmove(myPos,0,7);
        waddstr(myPos,"Attack Grid");
    }

    i=3;
    j=1;

    //lets print the top header
    for(string::iterator iter=chead.begin(); iter!=chead.end(); iter++)
    {
        wmove(myPos,j,i);
        waddch(myPos,*iter);

        //mySleep(t);
        wrefresh(myPos);

        i+=2;
    }

    i=0;
    j=2;

    //lets print the left side header
    for(string::iterator iter=nhead.begin(); iter!=nhead.end(); iter+=2)
    {
        wmove(myPos,j,i);
        waddch(myPos,*iter);
        wmove(myPos,j,i+1);
        waddch(myPos,*(iter+1));

        //mySleep(t);
        wrefresh(myPos);

        j++;
    }

    //creates colour pair (code, FW colour, BG colour)
    init_pair(2,colours[0],colours[5]);
    init_pair(3,colours[0],colours[5]);
    init_pair(4,colours[2],colours[5]);
    init_pair(5,colours[4],colours[5]);

    //lets print the grid borders
    for(j=2; j<lines; j++)
    {
    	for(i=2; i<cols; i+=2)
    	{
    		wattron(myPos,COLOR_PAIR(2));
    		wmove(myPos,j,i);
    		waddch(myPos,'|');
    		wattroff(myPos,COLOR_PAIR(2));

    		//mySleep(t);
    		wrefresh(myPos);
    	}
    }

    i=0;
    j=0;

    //Lets print the middle grid
    for(int k=3; k<cols; k+=2)
    {
        for(int z=2; z<lines; z++)
        {
            wmove(myPos,z,k);
            //check grid status (attack or defense)
            if(defense_grid)
            {
                //check point status
                if(points[i][j].isHit())
                {
                    if(points[i][j].hasShip())
                    {
                    	wattron(myPos,A_BOLD | COLOR_PAIR(5));//activates colour
                    	waddch(myPos,'@');//prints char
                    	wattroff(myPos,A_BOLD | COLOR_PAIR(5));//deactivates colour
                    }
                    else
                    {
                    	wattron(myPos, A_BOLD | COLOR_PAIR(4));
                    	waddch(myPos,'X');
                    	wattroff(myPos, A_BOLD | COLOR_PAIR(4));
                    }
                }
                else
                {
                    if(points[i][j].hasShip())
                    {
                    	wattron(myPos, A_BOLD | COLOR_PAIR(3));
                    	waddch(myPos,'O');
                    	wattroff(myPos, A_BOLD | COLOR_PAIR(3));
                    }
                    else
                    {
                    	wattron(myPos,COLOR_PAIR(2));
                    	waddch(myPos,' ');
                    	wattroff(myPos,COLOR_PAIR(2));
                    }
                }
            }
            else
            {
                //check point status
                if(points[i][j].isHit())
                {
                	if(points[i][j].hasShip())
                	{
                		wattron(myPos,A_BOLD | COLOR_PAIR(5));
                		waddch(myPos,'@');
                		wattroff(myPos,A_BOLD | COLOR_PAIR(5));
                	}
                	else
                	{
                		wattron(myPos, A_BOLD | COLOR_PAIR(4));
                		waddch(myPos,'X');
                		wattroff(myPos, A_BOLD | COLOR_PAIR(4));
                	}
                }
                else
                {
                	wattron(myPos,COLOR_PAIR(2));
                	waddch(myPos,' ');
                	wattroff(myPos,COLOR_PAIR(2));
                }
            }

            //refresh & delay
            wrefresh(myPos);
            //mySleep(t);
            i++;
        }
        j++;
        i=0;
    }
}

void Grid::operator =(Grid & griglia1)
{
    this->defense_grid=griglia1.defense_grid;
    this->cols=griglia1.cols;
    this->lines=griglia1.lines;
    this->points=griglia1.points;
}
