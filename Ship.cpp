#include "Functions.h"
#include "Ship.h"
#include "Point.h"

Ship::Ship(int dimention, string direction)
{
    dim=dimention;
    dir=direction;
}

void Ship::isWellPlaced(int y, int x,bool verbose)
{
    if(x>=0 && x<10 && y>=0 && y<10) //check that points at the beginning and at the end of the Ship aren't out of the grid
    {
        if((dir=="right"))
        {
            if(x+dim<=10){alive=true;} //if direction is right check along x-axis
            else{alive=false;print(outwin,"end point out-of-grid");cReturn(outwin);}
        }

        else if((dir=="down"))
        {
            if(y+dim<=10){alive=true;} //if direction is right check along x-axis
            else{alive=false;print(outwin,"end point out-of-grid");cReturn(outwin);}
        }

        else{alive=false; print(outwin,"Direction not recognised");cReturn(outwin);}
    }
    else{alive=false;print(outwin,"start point out-of-grid");cReturn(outwin);} //Position out-of-grid

    if(alive) //now lets check for overlap
    {
        if((dir=="right"))
        {
            for(int j=x;j<x+dim;j++)
            {
                if(p[y][j].hasShip())
                {
                	alive=false;
                	if(verbose)
                	{
                		print(outwin,"found overlap");
                	}
                	cReturn(outwin);
                	break;
                }
            }
            if(alive)
            {
                this->X0=x;
                this->Y0=y;
                for(int j=X0;j<X0+dim;j++) //If all point haven't got a ship let's assign them
                {
                    if(alive){p[Y0][j].setShip();}
                }
            }
        }
        else if((dir=="down"))
        {
            for(int i=y;i<y+dim;i++)
            {
                if(p[i][x].hasShip())
                {
                	alive=false;
                	if(verbose)
                	{
                		print(outwin,"found overlap");
                	}
                	cReturn(outwin);
                	break;
                }
            }
            if(alive)
            {
                this->X0=x;
                this->Y0=y;
                for(int i=Y0;i<Y0+dim;i++) //If all point haven't got a ship let's assign them
                {
                    if(alive){p[i][X0].setShip();}
                }
            }
        }
    }
}

void Ship::checkPointStatus()
{
    bool OnePointStanding=false;
    if(alive)
    {
        if((dir=="right"))
        {
            for(int j=X0;j<X0+dim;j++)
            {
                if(!p[Y0][j].isHit()){OnePointStanding=true;break;}
            }
            if(!OnePointStanding){alive=false;}

        }
        else if((dir=="down"))
        {
            for(int i=Y0;i<Y0+dim;i++)
            {
                if(!p[i][X0].isHit()){OnePointStanding=true;break;}
            }
            if(!OnePointStanding){alive=false;}
        }
    }
}

bool Ship::isAlive()
{
    return alive;
}

void Ship::operator =(Ship &n1)
{
    dir=n1.dir;
    dim=n1.dim;
    alive=n1.alive;
    p=n1.p;
    X0=n1.X0;
    Y0=n1.Y0;
}
