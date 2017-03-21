#include "Point.h"

Point::Point(int x, int y): X(x), Y(y){

    hit = false;
    ship = false;
}

//"get" methods
int Point::getX() const
{
    return X;
}
int Point::getY() const
{
    return Y;
}
bool Point::isHit()const{
    return hit;
}
bool Point::hasShip()const{

    return ship;
}
//"set" methods
void Point::setCoord(int x, int y)
{
    X=x;
    Y=y;
}
void Point::setHit(){
    hit=true;
}
void Point::setShip(){
    ship = true;
}
