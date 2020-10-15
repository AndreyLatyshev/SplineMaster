#include "stdafx.h"
#include "PolynomBezier.h"


namespace internal
{

PolynomBezier::PolynomBezier ()
{
    myCoefficients.push_back (0.);
}

PolynomBezier::PolynomBezier (std::vector<double>& theCoefficients)
{
    for (size_t i = 0; i < theCoefficients.size (); ++i)
        myCoefficients.push_back (theCoefficients[i]);
}

Polynom PolynomBezier::Derivative()    // (Polynom& theDerivative)
{
    std::vector<double> aVector;
    for (size_t i = 1; i < myCoefficients.size (); ++i)
        aVector.push_back (i * myCoefficients[i] *4);
    PolynomBezier theDerivative(aVector);
    return theDerivative;
}

}
