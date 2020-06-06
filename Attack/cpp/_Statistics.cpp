#include <iostream>
#include <algorithm>

#include "../header/_Statistics.h"
#include "../header/_Constants.h"
#include "../header/_BIGNUM.h"

using namespace std;

/*Compute median time*/
double ComputeMedianTimes(TIMES times)
{
    vectorSize size = times.size(), middle = size/2;

    sort(times.begin(), times.end());

    return (size % 2 == 0 ? (times[middle] + times[middle-1]) / 2 : times[middle]);
}
