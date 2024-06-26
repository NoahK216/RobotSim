/* Noah Klein */

#include <math.h>
#include <stdio.h>

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

double Robot::motorCurrentDraw(int milliVolts)
{
    /* See https://www.desmos.com/calculator/be4rzwy7sd for more */

    static const double f1 = 2.5;
    static const double k = 70;
    static const double a = 0.6;

    const double pctVolt = abs(milliVolts) / 12000.0;

    return f1 + (1 + tanh(k*(pctVolt-a)))/2 * ((-4.125 * pctVolt) + 4.975 - f1);
}
