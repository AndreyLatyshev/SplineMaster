// SpLineMaster.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "Bezier.h"
#include "DistFunction.h"
#include "Point.h"
#include "Segment.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace internal;

int main()
{
    Bezier aSpline_1 ("Spline_1.txt");
    Bezier aSpline_2 ("Spline_2.txt");

    DistFunction aTestDist (aSpline_1, aSpline_2);
    aTestDist.OutputResults ("Output_File.txt");

    return 0;
}

