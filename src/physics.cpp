/* Noah Klein */

#include <FL/Fl.H>
#include <math.h>

#include "../include/Robot.hpp"
#include "../include/sim.hpp"

#include "../include/debug.hpp"
#include "../include/constants.hpp"

#include "../include/physics.hpp"


template <typename T> int signum(T val) {
    return (T(0) < val) - (val < T(0));
}

void masterPhysics(Robot *robot)
{
    int isW, isA, isS, isD;
    handleKeyboardInput(&isW, &isA, &isS, &isD);

    
    /* Step down the ladder of motion in physics (acceleration, velocity, position) */
    
    masterMotorTorque(robot, isA - isW, isD - isS);
    wheelVelocity(robot);
    masterPose(robot);

}

void masterMotorTorque(Robot *robot, int mVoltsLeft, int mVoltsRight)
{
    /* angularAccel = torque/intertia */
    // robot->accelWheelLeft = robot->motorCurrentDraw(mVoltsLeft) / robot->wheelInertia;
    // robot->accelWheelRight = robot->motorCurrentDraw(mVoltsRight) / robot->wheelInertia;

    robot->accelWheelLeft = mVoltsLeft * 15;
    robot->accelWheelRight = mVoltsRight * 15;
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


void wheelVelocity(Robot *robot)
{
    /* Integrate acceleration over time */
    robot->velLeftDt += robot->accelWheelLeft * DELTA_TIME * robot->driveWheelRadius_m;
    robot->velRightDt += robot->accelWheelRight  * DELTA_TIME * robot->driveWheelRadius_m;

    int mVolts = robot->velLeftDt*10000;
    // printf("MVolts: %d\tAmps: %.2f\n", mVolts, robot->motorCurrentDraw(mVolts));

    applyDampingForce(robot);


    robot->velLinear = (robot->velRightDt + robot->velLeftDt)/2.0;
    robot->velAngular = (robot->velRightDt - robot->velLeftDt)/robot->wheelDistFromCenter;
 
    robot->velX = robot->velLinear * sin(robot->headingRad);
    robot->velY = -robot->velLinear * cos(robot->headingRad);
}

/* Apply kinetic friction opposite the direction the robot is currently being driven */
void applyDampingForce(Robot *robot)
{
    robot->velLeftDt = robot->velLeftDt * (1 - robot->velocityDampingCoefficient);
    robot->velRightDt = robot->velRightDt * (1 - robot->velocityDampingCoefficient);
}


void masterPose(Robot *robot)
{
    /* Integrate velocity over time */
    robot->headingRad += robot->velAngular * DELTA_TIME;
    robot->posX += robot->velX * DELTA_TIME;
    robot->posY += robot->velY * DELTA_TIME;
}
