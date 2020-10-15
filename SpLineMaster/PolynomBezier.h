#ifndef POLYNOMBEZIER_H
#define POLYNOMBEZIER_H

#include "Polynom.h"

namespace internal
{

class PolynomBezier : public Polynom
{
public:
    PolynomBezier ();
    PolynomBezier (std::vector<double>& theCoefficients);
    Polynom Derivative ();//(Polynom& theDerivative);
private:

};

}

#endif // !POLYNOMBEZIER_H
