#ifndef SPLINE_H
#define SPLINE_H

#include "Point.h"
#include "Polynom.h"
#include "Segment.h"

#include <vector>

namespace internal
{

class Spline
{
public:
    //! Initializing the vector of basic points of the spline.
    void SetPoints (const std::vector<Point>& thePoints);

    //! Computes the polynoms by variables X and Y and their first and second derivative.
    virtual void ComputePolynoms() = 0;

    //! Returns the basic point of spline by its number.
    Point GetPoint (int theIndex);

    //! Computes the polynom's value of parameter T.
    virtual double Of (const Polynom& thePol, double theT) = 0;

    //! Returns the point of parameter T on the spline.
    virtual Point Value (double theT) = 0;

    //! Returns the 1st derivative point of parameter T on the spline.
    virtual Point Derivative (double theT) = 0;

    //! Returns the 2nd derivative point of parameter T on the spline.
    virtual Point SecondDerivative (double theT) = 0;

    //! Returns the pair of parametric borders of the polynom
    virtual pair<double, double> BorderParameters() = 0;

    //! Returns the segment that connects two boundary vertices of the polynom
    virtual Segment GetBasicSegment();

    //! Returns a polyline that approximates the spline with the default tolerance 
    vector<Segment> Polygonize();

    //! Returns a polyline that approximates the spline on the interval [theFP, theLP] with the given tolerance 
    vector<Segment> Polygonize (double theFirstParam, double theLastParam, double theTol);

    //! The same as previous defined by theBorders with the given tolerance 
    vector<Segment> Polygonize (pair <double, double> theBorders, double theTol);

private:
    vector<Point>      myPoints;
};

}
#endif
