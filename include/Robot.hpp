/* Noah Klein */

#include <stdio.h>

#ifndef ROBOT_HPP
#define ROBOT_HPP

class Robot{
private:
    double degrees(double radians);
    double radians(double degrees);

public:
    Robot(double x, double y, double headingDeg, double m_kg)
    {
        accelX = accelY = velX = velY = posX = posY = 0;
        
        posX = x;
        posY = y;
        
        headingRad = radians(headingDeg);

        staticFrictionCoefficient = 0.05; // The measured static coefficient of friciton between rubber and rubber 
        kineticFrictionCoefficient = 1; // The measured kinetic coefficient of friciton between rubber and rubber 

        mass_kg = m_kg;
    }

    double accelX, accelY;
    double velX, velY;
    double posX, posY;

    double staticFrictionCoefficient, kineticFrictionCoefficient;

    double mass_kg;
    double normalForce();

    double headingRad;
    double headingDeg();

};

extern Robot *robot;

#endif // ROBOT_HPP