#include "stdafx.h"
#include "Point.h"


namespace internal
{

Point::Point ()
{
    Point (0., 0.);
}

Point::Point (double theX, double theY)
{
    myCoordinates.first = theX;
    myCoordinates.second = theY;
}

double Point::GetX() const
{
    return myCoordinates.first;
}

double Point::GetY() const
{
    return myCoordinates.second;
}

double Point::GetSquaredDistance (const Point& theOtherPoint) const
{
    return pow (GetX() - theOtherPoint.GetX(), 2) + pow (GetY() - theOtherPoint.GetY(), 2);
}

double Point::GetDistance (const Point& theOtherPoint) const
{
    return sqrt (GetSquaredDistance (theOtherPoint));
}

double Point::GetSquaredMagnitude() const 
{
    return pow (GetX(), 2) + pow (GetY(), 2);
}

double Point::GetMagnitude() const 
{
    return sqrt (GetSquaredMagnitude ());
}

}
