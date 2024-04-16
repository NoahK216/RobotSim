/* Noah Klein */

#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <math.h>

class Robot{
private:
    double degrees(double radians);
    double radians(double degrees);

public:
    Robot(double x, double y, double headingDeg, double wheelRadius_m, double m_kg)
    {
        accelX = accelY = velX = velY = posX = posY = velLeftDt = velRightDt = 0;
        
        posX = x;
        posY = y;
        
        headingRad = radians(headingDeg);

        driveWheelRadius_m = wheelRadius_m;

        mass_kg = m_kg;

        wheelInertia = M_PI * wheelRadius_m / 4.0; // pi*R/4

        //wheelAngularAcceleration = motorTorqueCoefficient * mechEfficiencyCoefficient / wheelInertia;
    }

    double accelWheelLeft, accelWheelRight;
    double velLinear, velAngular;
    double velLeftDt, velRightDt;

    double accelX, accelY;
    double velX, velY;
    double posX, posY;

    const double staticFrictionCoefficient = 0.05;
    const double kineticFrictionCoefficient = 0.008;
    const double velocityDampingCoefficient = 0.05;

    const double motorTorqueCoefficient = 1.1; // Motor torque constant (Nm/A)
    const double mechEfficiencyCoefficient = 0.85; // Mechanical efficiency of transmission system

    const double wheelDistFromCenter = 0.1524;

    double wheelInertia;

    //double wheelAngularAcceleration;

    double mass_kg;
    double normalForce();

    double headingRad;
    double headingDeg();

    double driveWheelRadius_m;

    double motorCurrentDraw(int milliVolts);
    

    //double (double rpm);

    /* If it gets this deep, at some point incorporate the fact that there is more energy loss with higher gearing cartridges, actually measuring that might be tricky */

};

#endif // ROBOT_HPP