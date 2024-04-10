/* Noah Klein */

#include <math.h>

#include "include/debug.hpp"
#include "include/constants.hpp"

#include "include/Robot.hpp"

double Robot::degrees(double radians)
{
    return radians * (180/M_PI);
}

double Robot::radians(double degrees)
{
    return degrees * (M_PI/180);
}

double Robot::normalForce()
{
    return mass_kg * GRAVITY_MSS;
}

double Robot::headingDeg()
{
    return degrees(headingRad);
}
