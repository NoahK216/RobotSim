/* Noah Klein */

#include <math.h>
#include <algorithm> 
#include <cmath>
#include <limits>
#include <stdio.h>

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


// Function to calculate the distance from the origin to the nearest intersection with a rectangle (Thank you ChatGPT)
double calculateRayIntersectionDistance(double x0, double y0, double theta, 
                                        double x_min, double x_max, double y_min, double y_max) {
    // Calculate the ray's direction
    double dx = std::cos(theta);
    double dy = std::sin(theta);

    // Initialize distances to infinity
    double d_min = std::numeric_limits<double>::infinity();

    // Intersection with left (x = x_min)
    if (dx != 0) { // Avoid division by zero
        double d_left = (x_min - x0) / dx;
        double y_intersect = y0 + d_left * dy;
        if (d_left > 0 && y_intersect >= y_min && y_intersect <= y_max) { // Check valid intersection
            d_min = std::min(d_min, d_left);
        }
    }

    // Intersection with right (x = x_max)
    if (dx != 0) { // Avoid division by zero
        double d_right = (x_max - x0) / dx;
        double y_intersect = y0 + d_right * dy;
        if (d_right > 0 && y_intersect >= y_min && y_intersect <= y_max) { // Check valid intersection
            d_min = std::min(d_min, d_right);
        }
    }

    // Intersection with bottom (y = y_min)
    if (dy != 0) { // Avoid division by zero
        double d_bottom = (y_min - y0) / dy;
        double x_intersect = x0 + d_bottom * dx;
        if (d_bottom > 0 && x_intersect >= x_min && x_intersect <= x_max) { // Check valid intersection
            d_min = std::min(d_min, d_bottom);
        }
    }

    // Intersection with top (y = y_max)
    if (dy != 0) { // Avoid division by zero
        double d_top = (y_max - y0) / dy;
        double x_intersect = x0 + d_top * dx;
        if (d_top > 0 && x_intersect >= x_min && x_intersect <= x_max) { // Check valid intersection
            d_min = std::min(d_min, d_top);
        }
    }

    return d_min;
}


// VEX Distance sensor range is 20mm to 2,000mm

double Robot::frontDistanceMeasurement(){
    double realDistance = calculateRayIntersectionDistance(xPos_m, yPos_m, headingRad - M_PI/2, field->leftX, field->rightX, field->topY, field->bottomY);
    return std::clamp(realDistance, 0.02, 2.0); 
}

double Robot::rearDistanceMeasurement(){
    double realDistance = calculateRayIntersectionDistance(xPos_m, yPos_m, headingRad + M_PI/2, field->leftX, field->rightX, field->topY, field->bottomY);
    return std::clamp(realDistance, 0.02, 2.0);
}