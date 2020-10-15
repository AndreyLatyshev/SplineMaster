#include "stdafx.h"

#include "PairOfSegments.h"

namespace internal
{

PairOfSegments::PairOfSegments (const Segment theSegmentA, const Segment theSegmentB, int theID_A, int theID_B, double theDist) :
    mySegments (make_pair (theSegmentA, theSegmentB)),
    mySegmentIDs (make_pair (theID_A, theID_B)),
    myDist (theDist)
{
}

int PairOfSegments::GetFirstID() const
{
    return mySegmentIDs.first;
}

int PairOfSegments::GetSecondID() const
{
    return mySegmentIDs.second;
}

Segment PairOfSegments::GetFirstSegment() const
{
    return mySegments.first;
}

Segment PairOfSegments::GetSecondSegment()const
{
    return mySegments.second;
}

double PairOfSegments::GetDistance() const 
{
    return myDist;
}

pair<double, double> PairOfSegments::ComputeClosestPoints()
{
    Point aPnt;
    double aF, aS;
    pair <double, double> aPars;
    if (GetFirstSegment().IsIntersecting (GetSecondSegment(), aPnt))
    {
        aF = aPnt.GetDistance (GetFirstSegment().GetFirstPoint()) / GetFirstSegment().GetMagnitude();
        aS = aPnt.GetDistance (GetSecondSegment().GetFirstPoint()) / GetSecondSegment().GetMagnitude();

        aPars = GetFirstSegment().GetLabels();
        myParameters.first = aPars.first + aF * (aPars.second - aPars.first);
        aPars = GetSecondSegment().GetLabels();
        myParameters.second = aPars.first + aS * (aPars.second - aPars.first);
    }
    else
    {
        Segment aS1 = GetFirstSegment(), aS2 = GetSecondSegment();
        Point aP11 = aS1.GetFirstPoint(), aP12 = aS1.GetSecondPoint();

        aPars.second = (aS2.GetDistanceTo (aP11) < aS2.GetDistanceTo (aP12)) ?
            aS2.ProjectionParameter (aP11):
            aS2.ProjectionParameter (aP12);
        myParameters.second = aPars.second < aS2.GetLabels().first ?
            aS2.GetLabels().first :
                (aPars.second > aS2.GetLabels().second ?
                aS2.GetLabels().second :
                aPars.second);

        Point aP21 = aS2.GetFirstPoint(), aP22 = aS2.GetSecondPoint();
        aPars.first = (aS1.GetDistanceTo (aP21) < aS1.GetDistanceTo (aP22)) ?
            aS1.ProjectionParameter (aP21) :
            aS1.ProjectionParameter (aP22);
        myParameters.first = aPars.first < aS1.GetLabels().first ?
            aS1.GetLabels().first :
            (aPars.first > aS1.GetLabels().second ?
                aS2.GetLabels().second :
                aPars.first);
    }
    return myParameters;
}

pair<double, double> PairOfSegments::GetParameters() const
{
    return myParameters;
}

}

