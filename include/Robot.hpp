/* Noah Klein */

#ifndef ROBOT_HPP
#define ROBOT_HPP

class Robot{
private:
    double degrees(double radians);
    double radians(double degrees);

public:
    Robot(double x, double y, double headingDeg, double wheelRadius_m, double m_kg)
    {
        accelX = accelY = velX = velY = posX = posY = 0;
        
        posX = x;
        posY = y;
        
        headingRad = radians(headingDeg);

        staticFrictionCoefficient = 0.05;
        kineticFrictionCoefficient = 0.008;
        velocityDampingCoefficient = 0.05;

        driveWheelRadius_m = wheelRadius_m;

        mass_kg = m_kg;
    }

    double accelX, accelY;
    double velX, velY;
    double posX, posY;

    double staticFrictionCoefficient, kineticFrictionCoefficient;
    double velocityDampingCoefficient;

    double mass_kg;
    double normalForce();

    double headingRad;
    double headingDeg();

    double driveWheelRadius_m;

};

#endif // ROBOT_HPP