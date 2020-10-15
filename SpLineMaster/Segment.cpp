//#define _USE_MATH_DEFINES
#include <cmath>

#include "stdafx.h"

#include "Point.h"
#include "Segment.h"


#include <array>

namespace
{

double Det (double a, double b, double c, double d)
{
    return a * d - b * c;
}

bool Between (double a, double b, double x)
{
    return (min (a, b) <= x + TOLERANCE) && (x < max (a, b) + TOLERANCE);
}

bool Intersect (double a, double b, double c, double d) {
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    return max (a, c) <= min (b, d);
}

double sqr (double x)
{
    return x * x;
}

}

namespace internal
{

Segment::Segment()
{
    myBorders.first = Point();
    myBorders.second = Point();
}

Segment::Segment (const Point& theFirstPoint, const Point& theSecondPoint)
{
    myBorders.first = theFirstPoint;
    myBorders.second = theSecondPoint;
}

Point Segment::GetFirstPoint() const
{
    return myBorders.first;
}

Point Segment::GetSecondPoint() const
{
    return myBorders.second;
}

double Segment::GetSquaredMagnitude() const
{
    return myBorders.first.GetSquaredDistance (myBorders.second);
}

double Segment::GetMagnitude() const 
{
    return myBorders.first.GetDistance (myBorders.second);
}

bool Segment::IsIntersecting (const Segment& theOtherSegment, Point& theIntersectionPoint) const
{
    array<Point, 4> aP;
    aP[0] = GetFirstPoint(), aP[2] = theOtherSegment.GetFirstPoint();
    aP[1] = GetSecondPoint(), aP[3] = theOtherSegment.GetSecondPoint();

    // Computing the coefficients of the lines that produce current segments
    double A1 = aP[0].GetY() - aP[1].GetY(), A2 = aP[2].GetY() - aP[3].GetY();
    double B1 = aP[1].GetX() - aP[0].GetX(), B2 = aP[3].GetX() - aP[2].GetX();
    double C1 = -A1 * aP[0].GetX() - B1 * aP[0].GetY(), C2 = -A2 * aP[2].GetX() - B2 * aP[2].GetY();

    // Finding out whether the segments are parallel (if Z=0)
    double Z = Det (A1, A2, B1, B2);
    if (Z != 0)
    {
        double X = -Det (C1, B1, C2, B2) / Z;
        double Y = -Det (A1, C1, A2, C2) / Z;

        // Only if both the segments contains the Point (X, Y) there is an intersection between them
        if (Between (aP[0].GetX (), aP[1].GetX (), X) && Between (aP[0].GetY (), aP[1].GetY (), Y) &&
            Between (aP[2].GetX (), aP[3].GetX (), X) && Between (aP[2].GetY (), aP[3].GetY (), Y))
        {
            theIntersectionPoint = Point (X, Y);
            return true;
        }
        return false;
    }
    else
    {
        // Finding out whether the segments are on the same line
        return ((Det (A1, C1, A2, C2) == 0) && (Det (B1, C1, B2, C2) == 0)
            && Intersect (aP[0].GetX(), aP[1].GetX(), aP[2].GetX(), aP[3].GetX())
            && Intersect (aP[0].GetY(), aP[1].GetY(), aP[2].GetY(), aP[3].GetY()));
    }
}

double Segment::GetDistanceTo (const Point& thePoint) const
{
    return sqrt (GetSquaredDistanceTo (thePoint));
}

double Segment::GetSquaredDistanceTo (const Point& thePoint) const
{
    array<double, 3> X, Y;
    X[0] = GetSecondPoint().GetX() - GetFirstPoint().GetX();
    X[1] = thePoint.GetX() - GetFirstPoint().GetX();
    X[2] = thePoint.GetX() - GetSecondPoint().GetX();
    Y[0] = GetSecondPoint().GetY() - GetFirstPoint().GetY();
    Y[1] = thePoint.GetY() - GetFirstPoint().GetY();
    Y[2] = thePoint.GetY() - GetSecondPoint().GetY();

    if (Det (-X[2], Y[2], Y[0], X[0]) > 0 &&
        Det (X[1], Y[1], -Y[0], X[0]) > 0)
    {
        return sqr (Det (X[1], Y[1], X[0], Y[0])) / GetSquaredMagnitude();
    }
    else 
        return min (thePoint.GetSquaredDistance (GetFirstPoint()), thePoint.GetSquaredDistance (GetSecondPoint()));
}

double Segment::GetDistanceTo (const Segment& theSegment) const
{
    return sqrt (GetSquaredDistanceTo (theSegment));
}

double Segment::GetSquaredDistanceTo (const Segment& theSegment) const
{
    Point aPoint;
    if (!IsIntersecting (theSegment, aPoint))
        return min (min (GetSquaredDistanceTo (theSegment.GetFirstPoint()),
                         GetSquaredDistanceTo (theSegment.GetSecondPoint())),
                    min (theSegment.GetSquaredDistanceTo (GetFirstPoint()),
                         theSegment.GetSquaredDistanceTo (GetSecondPoint())));
    return 0.;
}

void Segment::SetLabels (double theFirst, double theSecond)
{
    myLabels.first  = theFirst;
    myLabels.second = theSecond;
}

pair<double, double> Segment::GetLabels() const
{
    return myLabels;
}

double Segment::ProjectionParameter (const Point& thePnt) const
{
    double X1 = thePnt.GetX() - GetFirstPoint().GetX(), X2 = GetSecondPoint().GetX() - GetFirstPoint().GetX();
    double Y1 = thePnt.GetY() - GetFirstPoint().GetY(), Y2 = GetSecondPoint().GetY() - GetFirstPoint().GetY();

    // Projection parameter is equal to the scalar product divided by squared length of the segment
    return (X1 * X2 + Y1 * Y2) / GetSquaredMagnitude();
}

}
