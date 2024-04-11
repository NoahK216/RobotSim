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

        wheelAngularAcceleration = motorTorqueCoefficient * mechEfficiencyCoefficient / wheelInertia;
    }

    double accelLeftDt, accelRightDt;
    double velLeftDt, velRightDt;

    double accelX, accelY;
    double velX, velY;
    double posX, posY;

    const double staticFrictionCoefficient = 0.05;
    const double kineticFrictionCoefficient = 0.008;
    const double velocityDampingCoefficient = 0.05;

    const double motorTorqueCoefficient = 0.8; // Motor torque constant (Nm/A)
    const double mechEfficiencyCoefficient = 0.95; // Mechanical efficiency of transmission system

    double wheelInertia;

    double wheelAngularAcceleration;

    double mass_kg;
    double normalForce();

    double headingRad;
    double headingDeg();

    double driveWheelRadius_m;

};

#endif // ROBOT_HPP