#include "stdafx.h"

#include "Bezier.h"
#include <fstream>

namespace
{
// Recursively calculates combinatoric number of combinations
int Combination (int k, int n)
{
    if (k > n)
        return -1;
    if (k == 1)
        return n;
    if ((k == 0) || (k == n))
        return 1;
    return Combination (k - 1, n - 1) + Combination (k, n - 1);
}

}

namespace internal
{

Bezier::Bezier ()
{

}

Bezier::Bezier (const std::vector<Point>& thePoints)
{
    SetPoints (thePoints);
    myParameters = std::make_pair (0., 1.);
    myDegree = thePoints.size() - 1;
    ComputePolynoms();
}

Bezier::Bezier (string theFilename)
{
    ifstream aFile (theFilename);

    vector <double> aCoord;
    double aNew;

    while (!aFile.eof())
    { 
        aFile >> aNew;
        aCoord.push_back (aNew);
    }

    vector <Point> aPnts;
    if (aCoord.size() % 2 ==0)
    {
        for (size_t i = 0; i < aCoord.size (); i += 2)
            aPnts.push_back (Point (aCoord[i], aCoord[i + 1]));
    }
    SetPoints (aPnts);
    myParameters = std::make_pair (0., 1.);
    myDegree = aPnts.size () - 1;
    ComputePolynoms ();
}


double Bezier::FirstParameter()
{
    return myParameters.first;
}

double Bezier::LastParameter()
{
    return myParameters.second;
}

void Bezier::ComputePolynoms()
{
    int N = myDegree;
    vector<double> aVecX (N + 1), aVecY (N + 1);
    int aCoef;
    // Computing the vectors of coefficients for X and Y arguments
    for (int i = 0; i <= N; ++i)
    {
        for (int k = 0; k <= N - i; ++k)
        {
            aCoef = (-2 * (k % 2) + 1) * Combination (i, N) * Combination (k, N - i);
            aVecX[i + k] += aCoef * GetPoint(i).GetX();
            aVecY[i + k] += aCoef * GetPoint(i).GetY();
        }
    }
    // Determining the necessary polynoms
    myPolynomX = Polynom (aVecX);
    myPolynomY = Polynom (aVecY);
    myXDerivative = myPolynomX.Derivative();
    myYDerivative = myPolynomY.Derivative();
    myX2Derivative = myXDerivative.Derivative();
    myY2Derivative = myYDerivative.Derivative();
}

double Bezier::Of (const Polynom& thePol, double theT)
{
    double aValue = 0., aMult = 1.;
    int aSize = thePol.GetSize();
    for (int i = 0; i < aSize; ++i)
    {
        aValue += aMult * thePol.GetCoef (i);
        aMult *= theT;
    }
    return aValue;
}

Point Bezier::Value (double theT)
{
    return Point (Of (myPolynomX, theT), Of (myPolynomY, theT));
}

Point Bezier::Derivative (double theT)
{
    return Point (Of (myXDerivative, theT), Of (myYDerivative, theT));
}

Point Bezier::SecondDerivative (double theT)
{
    return Point (Of (myX2Derivative, theT), Of (myY2Derivative, theT));
}

pair<double, double> Bezier::BorderParameters()
{
    return make_pair (myParameters.first, myParameters.second);
}

Segment Bezier::GetBasicSegment ()
{
    Segment aBS (GetPoint (0), GetPoint (myDegree));
    aBS.SetLabels (myParameters.first, myParameters.second);
    return aBS;
}

}
