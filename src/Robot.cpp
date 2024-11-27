/* Noah Klein */

#include <math.h>
#include <algorithm> 
#include <cmath>
#include <limits>

#include "../include/debug.hpp"
#include "../include/constants.hpp"

#include "../include/Robot.hpp"

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
    //TODO this might not be right
    return remainder(degrees(headingRad), 360) + 180;
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

double Robot::xPos_pix(){
    return this->xPos_m * METERS_TO_PIXELS; 
}

double Robot::yPos_pix(){
    return this->yPos_m * METERS_TO_PIXELS;
}


// Function to calculate the distance from the origin to the nearest intersection with a rectangle
double calculateRayIntersectionDistance(double x0, double y0, double theta, 
                                        double x_min, double x_max, double y_min, double y_max) {
    // Calculate distances to the four boundaries (left, right, bottom, top)
    double d_left = (cos(theta) != 0) ? (x_min - x0) / cos(theta) : std::numeric_limits<double>::infinity();
    double d_right = (cos(theta) != 0) ? (x_max - x0) / cos(theta) : std::numeric_limits<double>::infinity();
    double d_bottom = (sin(theta) != 0) ? (y_min - y0) / sin(theta) : std::numeric_limits<double>::infinity();
    double d_top = (sin(theta) != 0) ? (y_max - y0) / sin(theta) : std::numeric_limits<double>::infinity();

    // Only consider valid distances where the ray intersects the boundaries in the correct direction
    if (cos(theta) < 0) d_left = std::max(d_left, 0.0);  // Ray going left
    else d_right = std::max(d_right, 0.0);  // Ray going right

    if (sin(theta) < 0) d_bottom = std::max(d_bottom, 0.0);  // Ray going down
    else d_top = std::max(d_top, 0.0);  // Ray going up

    // Return the minimum positive distance to an intersection point
    return std::min({d_left, d_right, d_bottom, d_top});
}


double Robot::frontDistanceMeasurement(){
    return calculateRayIntersectionDistance(xPos_m, yPos_m, headingRad, field->leftX, field->rightX, field->topY, field->bottomY);
    //return 1.5;
}

double Robot::rearDistanceMeasurement(){
    return 1.0;
}
