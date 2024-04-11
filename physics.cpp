/* Noah Klein */

#include <FL/Fl.H>
#include <math.h>

#include "include/Robot.hpp"
#include "include/sim.hpp"

#include "include/debug.hpp"
#include "include/constants.hpp"

#include "include/physics.hpp"


template <typename T> int signum(T val) {
    return (T(0) < val) - (val < T(0));
}

void masterPhysics(Robot *robot)
{
    int isW, isA, isS, isD;
    handleKeyboardInput(&isW, &isA, &isS, &isD);

    
    /* Step down the ladder of motion in physics (slew?, accel, velocity, position) */
    
    //robot->headingRad -= 0.1*isA - 0.1*isD;
    wheelAcceleration(robot, isA - isW, isD - isS);
    //masterVelocity(robot);
    //masterPosition(robot);

}

void wheelAcceleration(Robot *robot, double drivePowerLeft, double drivePowerRight)
{

    double accelLeft = robot->wheelAngularAcceleration * drivePowerLeft;
    double accelRight = robot->wheelAngularAcceleration * drivePowerRight;

    robot->velLeftDt += accelLeft * DELTA_TIME * robot->driveWheelRadius_m;
    robot->velRightDt += accelRight  * DELTA_TIME * robot->driveWheelRadius_m;

    applyDampingForce(robot);

    const double wheelDistFromCenter = 0.1524;

    double velocity = (robot->velRightDt + robot->velLeftDt)/2.0;
    double angularVel = (robot->velRightDt - robot->velLeftDt)/wheelDistFromCenter;
 
    robot->velX = velocity * sin(robot->headingRad);
    robot->velY = -velocity * cos(robot->headingRad);

    robot->headingRad += angularVel * DELTA_TIME;
    robot->posX += robot->velX * DELTA_TIME;
    robot->posY += robot->velY * DELTA_TIME;

    printf("%.2f %.2f\n", velocity, angularVel);

    /*
    AX = cos(robot->headingRad) * actingForce
    AY = sin(robot->headingRad) * actingForce
    */


}

void masterAcceleration(Robot *robot, double actingForce)
{

    actingForce *= 5;

    /*
    AX = cos(robot->headingRad) * actingForce
    AY = sin(robot->headingRad) * actingForce
    */

    double staticFrictionForce = robot->normalForce() * robot->staticFrictionCoefficient;

    /* If the robot was at rest and the magnitude of acceleration doesn't overcome static friction, leave */
    if(!robot->velX && !robot->velY && (actingForce < staticFrictionForce))
    {
        robot->accelX = 0;
        robot->accelY = 0;
        actingForce = 0;
    }
    else 
    {
        applyKineticFriction(robot, actingForce);
    }

}

/* Apply kinetic friction opposite the direction the robot is currently being driven */
void applyKineticFriction(Robot *robot, double actingForce)
{
    double robotSin = sin(robot->headingRad);
    double robotCos = cos(robot->headingRad);

    double kineticFrictionForce = robot->normalForce() * robot->kineticFrictionCoefficient;

    double actingForceX = robotSin * actingForce;
    double actingForceY = robotCos * -actingForce;

    robot->accelX = actingForceX + signum(actingForceX) * robotSin * kineticFrictionForce;
    robot->accelY = actingForceY + signum(actingForceY) * robotCos * kineticFrictionForce;
}


void masterVelocity(Robot *robot)
{
    /* Integrate acceleration over time */
    robot->velX += robot->accelX * DELTA_TIME;
    robot->velY += robot->accelY * DELTA_TIME;

    applyDampingForce(robot);
}

/* Apply kinetic friction opposite the direction the robot is currently being driven */
void applyDampingForce(Robot *robot)
{
    robot->velLeftDt = robot->velLeftDt * (1 - robot->velocityDampingCoefficient);
    robot->velRightDt = robot->velRightDt * (1 - robot->velocityDampingCoefficient);
}


void masterPosition(Robot *robot)
{
    /* Integrate velocity over time */
    robot->posX += robot->velX * DELTA_TIME;
    robot->posY += robot->velY * DELTA_TIME;
}
