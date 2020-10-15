#include "stdafx.h"
#include "DistFunction.h"
#include "PairOfSegments.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>


namespace internal
{

#define INITIAL_TOLERANCE 1e-1
#define STEP_TOLERANCE 10

DistFunction::DistFunction (Spline& theSplineA, Spline& theSplineB)
    : myFirstSpline (theSplineA), mySecondSpline (theSplineB), myDistance (-1.)
{
}

double DistFunction::ComputeDistance()
{
    double aTol = INITIAL_TOLERANCE, aDist, myDistance = myFirstSpline.GetPoint (0).GetDistance (mySecondSpline.GetPoint (0));
    
    // The bijection between unique ID of the segment and its polyline
    map <int, vector <int>> aPolylineMap;

    // The bijection between unique ID of the segment and its instance
    map <int, Segment> aSegmentMap;

    // Vectors to store correspondin pairs of segments on two splines
    vector <PairOfSegments> aPairs, aNewPairs;

    // Temporary variable to store the output of method Spline::Polygonize
    vector <Segment> aTemp;

    // Vectors of segmets IDs
    array <vector <int>, 2> anIDs;

    // Temporary variables to store the segments
    Segment aCurrent, aNew;

    // Initial pair of basic segments of the splines
    PairOfSegments aPair (myFirstSpline.GetBasicSegment(), mySecondSpline.GetBasicSegment(), 1, -1, myDistance);
    aPairs.push_back (aPair);
    aSegmentMap.insert (make_pair (aPair.GetFirstID(), aPair.GetFirstSegment()));
    aSegmentMap.insert (make_pair (aPair.GetSecondID(), aPair.GetSecondSegment()));

    // Initial IDs (always positive for the 1st spline's segments, 
    // always negative for the 2nd spline's segments)
    int ID_1 = 2, ID_2 = -2;
    
    while (aTol >= TOLERANCE / STEP_TOLERANCE)
    {
        for (size_t idx = 0; idx < aPairs.size(); ++idx)
        {
            anIDs[0].clear(); anIDs[1].clear();
            int toFind1 = aPairs[idx].GetFirstID(), toFind2 = aPairs[idx].GetSecondID();
            

            // Filling the field of the 1st segment's polyline if it's not initialized
            if (aPolylineMap.find (toFind1) == aPolylineMap.end())
            {
                aCurrent = aSegmentMap.find (toFind1)->second;
                aTemp = myFirstSpline.Polygonize (aCurrent.GetLabels(), aTol);
                
                for (size_t jdx = 0; jdx < aTemp.size(); ++jdx)
                {
                    aSegmentMap.insert (make_pair (ID_1, aTemp[jdx]));
                    anIDs[0].push_back (ID_1);
                    ++ID_1;
                }
                aPolylineMap.insert (make_pair (toFind1, anIDs[0]));
            }
            else
            {
                anIDs[0] = aPolylineMap.find (toFind1)->second;
            }

            // Filling the field of the 2nd segment's polyline if it's not initialized
            if (aPolylineMap.find (toFind2) == aPolylineMap.end())
            {
                aCurrent = aSegmentMap.find (toFind2)->second;
                aTemp = mySecondSpline.Polygonize (aCurrent.GetLabels(), aTol);

                for (size_t jdx = 0; jdx < aTemp.size(); ++jdx)
                {
                    aSegmentMap.insert (make_pair (ID_2, aTemp[jdx]));
                    anIDs[1].push_back (ID_2);
                    --ID_2;
                }
                aPolylineMap.insert (make_pair (toFind2, anIDs[1]));
            }
            else
            {
                anIDs[1] = aPolylineMap.find (toFind2)->second;
            }
            
            // Selecting the pairs of segments with minimal distance between
            for (size_t j = 0; j < anIDs[0].size(); ++j)
            {
                aCurrent = aSegmentMap.find (anIDs[0][j])->second;
                for (size_t k = 0; k < anIDs[1].size(); ++k)
                {
                    aNew = aSegmentMap.find (anIDs[1][k])->second;
                    aDist = aCurrent.GetDistanceTo (aNew);
                    if (aDist <= myDistance + aTol)
                    {
                        if (aDist < myDistance - aTol)
                        {
                            aNewPairs.clear();
                        }
                        aPair = PairOfSegments (aCurrent, aNew, anIDs[0][j], anIDs[1][k], aDist);
                        aNewPairs.push_back (aPair);
                        myDistance = min (aDist, myDistance);
                    }
                }
            }

        }
        // Updatint the vector of pairs.
        aPairs = aNewPairs;
        aNewPairs.clear();
        aTol /= STEP_TOLERANCE;
    }
    myParameters.resize (aPairs.size());

    // Saving the algorithm's results
    for (size_t i = 0; i < aPairs.size(); ++i)
    {
        myParameters[i] = aPairs[i].ComputeClosestPoints();
        aNew = Segment (myFirstSpline.Value (myParameters[i].first), mySecondSpline.Value (myParameters[i].second));

        myDistSegments.push_back (aNew);
    }
    return myDistance;
}

void DistFunction::PrintDistSegments()
{
    if (!myDistSegments.empty())
        for (size_t i = 0; i < myDistSegments.size(); ++i)
        {
            cout << "Segment #" << i + 1 << ": (" << myDistSegments[i].GetFirstPoint ().GetX () << ", "
                << myDistSegments[i].GetFirstPoint().GetY() << ") "
                << "(" << myDistSegments[i].GetSecondPoint().GetX() << ", "
                << myDistSegments[i].GetSecondPoint().GetY() << ") "
                << myDistSegments[i].GetMagnitude() << endl;
        }

}

void DistFunction::OutputResults (string theFilename)
{
    ofstream aFile (theFilename);
    double aDistance = ComputeDistance();
    aFile << fixed << setprecision (10);
    aFile << "Distance beetween splines is: " << aDistance << endl;

    vector <Segment> aSeg = myDistSegments;
    int N = aSeg.size();
    aFile << "Pairs of closest points: "<< N << endl << endl;
    for (size_t i = 0; i < aSeg.size(); ++i)
    {
        aFile << "Pair of points #" << i + 1 << ": " << endl;
        
        aFile << "      The 1st spline's point is: (" << aSeg[i].GetFirstPoint().GetX() << ", "
            << aSeg[i].GetFirstPoint().GetY() << ") " << " with parameter " << myParameters[i].first << endl;
        
        aFile << "      The 2nd spline's point is: (" << aSeg[i].GetSecondPoint().GetX() << ", "
            << aSeg[i].GetSecondPoint().GetY() << ") " << " with parameter " << myParameters[i].second << endl;

        aFile << "      The distance is: " << aSeg[i].GetMagnitude () << endl;

    }
    aFile.close();
}

}
