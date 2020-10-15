#include "stdafx.h"

#include "Point.h"
#include "Polynom.h"

namespace internal
{

Polynom::Polynom()
{
    myCoefficients.push_back (0.);
}

Polynom::Polynom (const std::vector<double>& theCoefficients) 
{
    for (size_t i = 0; i < theCoefficients.size(); ++i)
        myCoefficients.push_back (theCoefficients[i]);
}

Polynom Polynom::Derivative()
{
    std::vector<double> aVector;
    for (size_t i = 1; i < myCoefficients.size(); ++i)
        aVector.push_back (i * myCoefficients[i]);
    return Polynom (aVector);
}

int Polynom::GetSize() const
{
    return myCoefficients.size();
}

double Polynom::GetCoef (int theNum) const
{
    return myCoefficients[theNum];
}

}
