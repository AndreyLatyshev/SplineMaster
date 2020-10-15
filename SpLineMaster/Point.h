#ifndef POINT_H
#define POINT_H

#include <map>

using namespace std;

namespace internal
{

#define TOLERANCE 1e-9



class Point 
{
public:
    //! Default conctructor. Returns point (0,0) called Origin.
    Point();

    //! Constructor initializing point (X, Y).
    Point (double theX, double theY);

    //! Returns coordinate X.
    double GetX() const;

    //! Returns coordinate Y.
    double GetY() const;

    //! Returns squared distance between this point and OtherPoint. Faster than method GetDistance().
    double GetSquaredDistance (const Point& theOtherPoint) const;

    //! Returns distance between this point and OtherPoint.
    double GetDistance (const Point& theOtherPoint) const;

    //! Returns the squared distance to Origin. Faster than method GetMagnitude().
    double GetSquaredMagnitude() const;

    //! Returns the distance to Origin.
    double GetMagnitude() const;

private:
    pair <double, double>      myCoordinates;
};


}
#endif
