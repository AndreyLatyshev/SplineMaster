#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>

namespace internal
{

class Polynom
{
public:
    //! Default empty polynom equal to 0.
    Polynom();

    //! Polynom defined by the vector of its coefficients.
    Polynom (const vector<double>& theCoefficients);

    //! Returns the derivative of the polynom
    virtual Polynom Derivative();

    //! Returns the polynom's Size  (that is equal to Degree + 1).
    int GetSize() const;

    //! Returns the polynom's coefficient with index = theNum.
    double GetCoef (int theNum) const;
protected:
    vector<double>         myCoefficients;
};

}

#endif // !POLYNOM_H
