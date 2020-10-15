#ifndef DISTFUNCTION_H
#define DISTFUNCTION_H

#include "Point.h"
#include "Spline.h"

namespace internal
{

class DistFunction
{
public:
    //! Initializes two splines in order to compute distance between.
    DistFunction (Spline& theSplineA, Spline& theSplineB);

    /*! Calculates the distance between two splines. During the work of the algorithm 
        both splines are approximated by the polylines constructed by method Spline::Polygonize().
        The pairs of the closest subsegmets are collected and the corresponding parts of splines 
        are polygonized again but with new tolerance increased by the certain step (e.g. 10 or 100)
        Finally, when desired precision is reached the variables myDistSegments (vector containing
        segments of minimal length connecting two splines or degenerative segmets in case 
        the splines has an intersection) and myParameters (parameters of the corresponding 
        points in myDistSegments).
    */
    double ComputeDistance();

    //! Prints results into console window.
    void PrintDistSegments();

    //! Prints results into the output file.
    void OutputResults (string theFilename);

private:
    Spline&                                   myFirstSpline;
    Spline&                                   mySecondSpline;
    double                                    myDistance;
    vector <Segment>                          myDistSegments;
    vector <pair <double, double>>            myParameters;

};


}


#endif 
