#ifndef PAIROFSEGMENTS_H
#define PAIROFSEGMENTS_H

#include "Point.h"
#include "Segment.h"

namespace internal
{
class PairOfSegments
{
public:
    //! Initializes the storage for two segments, their IDs an the distance between them.
    PairOfSegments (const Segment theSegmentA, const Segment theSegmentB, int theID_A, int theID_B, double theDist);

    //! Returns first segment's ID.
    int GetFirstID() const;

    //! Returns second segment's ID.
    int GetSecondID() const;

    //! Returns first segment.
    Segment GetFirstSegment() const;

    //! Returns second segment.
    Segment GetSecondSegment() const;

    //! Returns the distance between the segments.
    double GetDistance() const;

    //! Calculates the parameters of the closest points.
    pair<double, double> ComputeClosestPoints();

    //! Returns the parameters of the closest points.
    pair <double, double> GetParameters() const;

private:
    pair <Segment, Segment>       mySegments;
    pair <int, int>               mySegmentIDs;
    pair <double, double>         myParameters;
    double                        myDist;
};


}

#endif

