#include "stdafx.h"

#include "Point.h"
#include "Spline.h"

#include <algorithm>

namespace internal
{

void Spline::SetPoints (const vector<Point>& thePoints)
{
    myPoints.clear();
    for (size_t i = 0; i < thePoints.size(); ++i)
        myPoints.push_back (thePoints[i]);
}

Point Spline::GetPoint (int theIndex)
{
    if (theIndex < (int) myPoints.size() && theIndex >= 0)
        return myPoints[theIndex];
    else
        return Point();
}

Segment Spline::GetBasicSegment()
{
    return Segment (myPoints[0], myPoints.back());
}

vector<Segment> Spline::Polygonize()
{
    pair <double, double> aBorder = BorderParameters ();
    double theTol = .5 * TOLERANCE;
    return Polygonize (aBorder.first, aBorder.second, theTol);
}


vector<Segment> Spline::Polygonize (double theFirstParam, double theLastParam, double theTol)
{
    vector<Segment> aPolyline;
    Segment aNew;
    
    double aT = theFirstParam, aDelta = 0., aRho, aTemp;
    Point aCurr = Value (aT), aNext, aDeriv;
    while (aT < theLastParam)
    {
        aTemp = aT;
        aDeriv = Derivative (aT);
        aNext = SecondDerivative (aT);
        aDelta = aDeriv.GetX() * aNext.GetY() - aDeriv.GetY() * aNext.GetX();
        if (aDelta == 0.) 
        {
            // The case of the straight line
            aT = theLastParam;
        }
        else {
            // The non-zero curvature Rho defines the length of the segment
            // that could be taken as the part of the spline with given tolerance
            aRho = abs (pow (aDeriv.GetSquaredMagnitude(), 1.5) / aDelta);

            // Epsilon = Tolerance / 2 to reach the precision Epsilon for estimating the distance between two polylines
            aDelta = sqrt (theTol * (4 * aRho - theTol)) / (aDeriv.GetMagnitude());
            aT += aDelta;
            aT = min (aT, theLastParam);
        }
        aNext = Value (aT);
        aNew = Segment (aCurr, aNext);
        aNew.SetLabels (aTemp, aT);
        aPolyline.push_back (aNew);
        aCurr = aNext;
    }
    return aPolyline;
}
vector<Segment> Spline::Polygonize (pair<double, double> theBorders, double theTol)
{
    return Polygonize (theBorders.first, theBorders.second, theTol);
}
}
