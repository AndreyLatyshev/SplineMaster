#ifndef BEZIER_H
#define BEZIER_H

#include "Point.h"
#include "Polynom.h"
#include "Spline.h"

#include <vector>

namespace internal
{

class Bezier : public Spline
{
public:
    // Default Bezier constructor
    Bezier ();

    //! Constructs Bezier by the vector of points.
    Bezier (const vector<Point>& thePoints);

    //! Reads Bezier from the file.
    Bezier (string theFilename);

    //! Returns Tmin.
    double FirstParameter();

    //! Returns Tmax.
    double LastParameter();

    //! Implements Spline::ComputePolynoms() for class Bezier.
    void ComputePolynoms();

    //! Implements Spline::Of(const Polynom& thePol, double theT) for class Bezier.
    double Of (const Polynom& thePol, double theT);

    //! Implements Spline::Value (double theT) for class Bezier.
    Point Value (double theT);

    //! Implements Spline::Derivative (double theT) for class Bezier.
    Point Derivative (double theT);

    //! Implements Spline::SecondDerivative (double theT) for class Bezier.
    Point SecondDerivative (double theT);

    //! Implements Spline::BorderParameters() for class Bezier.
    pair<double, double> BorderParameters();

    //! Implements Spline::GetBasicSegment() for class Bezier.
    Segment GetBasicSegment();
private:
    pair<double, double>        myParameters;
    Polynom                     myPolynomX;
    Polynom                     myPolynomY;
    Polynom                     myXDerivative;
    Polynom                     myYDerivative;
    Polynom                     myX2Derivative;
    Polynom                     myY2Derivative;
    int                         myDegree;
};

}
#endif // !BEZIER_H

