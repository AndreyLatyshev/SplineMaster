#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"

namespace internal
{
class Segment
{
public:
    //! Default constructor.
    Segment ();

    //! Constructor initializes the segment using two points.
    Segment (const Point& theFirstPoint, const Point& theSecondPoint);

    //! Returns the first point of the segment.
    Point GetFirstPoint() const;

    //! Returns the second point of the segment.
    Point GetSecondPoint() const;

    //! Returns squared magnitude. Faster than method GetMagnitude().
    double GetSquaredMagnitude() const;

    //! Returns squared magnitude.
    double GetMagnitude() const;

    /*! Returns FALSE  if the current segment and theOtherSegment has not an intersection,
        TRUE and theIntersectionPoint otherwise. 
    */
    bool IsIntersecting (const Segment& theOtherSegment, Point& theIntersectionPoint) const;

    //! Analyses the position of the segment w.r.t. thePoint and returns the distance between them.
    double GetDistanceTo (const Point& thePoint) const;

    //! Returns the squared distance to the point.
    double GetSquaredDistanceTo (const Point& thePoint) const;

    //! Analyses the position of the segment w.r.t. the other segment and returns the distance between them.
    double GetDistanceTo (const Segment& theSegment) const;

    //! Returns the squared distance between the segments.
    double GetSquaredDistanceTo (const Segment& theSegment) const;

    //! Sets the corresponding labels (parameters on the line) as each point's attribute.
    void SetLabels (double theFirst, double theSecond);

    //! Returns the pair of labels (parameters).
    pair<double, double> GetLabels() const;

    //! Returns the numerical parameter of point's projection on the line produced by the segment.
    double ProjectionParameter (const Point& thePnt) const;

private:
    pair<Point, Point>      myBorders;
    pair<double, double>    myLabels;
};

}

#endif // !SEGMENT_H
