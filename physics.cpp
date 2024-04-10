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
    
    robot->headingRad -= 0.1*isA - 0.1*isD;

    masterAcceleration(robot, isW - isS);
    masterVelocity(robot);
    masterPosition(robot);

}


void masterAcceleration(Robot *robot, double actingForce)
{
    double robotSin = sin(robot->headingRad);
    double robotCos = cos(robot->headingRad);

    actingForce *= 100;

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
        /* Otherwise lets take kinetic friction into account */
        double kineticFrictionForce = robot->normalForce() * robot->kineticFrictionCoefficient;

        double velocityMagnitude = sqrt(robot->velX * robot->velX + robot->velY * robot->velY);

        double actingForceX = robotSin * actingForce;
        double actingForceY = robotCos * -actingForce;

        // Update the kinetic friction force as the velocity decreases
        double frictionForceX = 0.0;
        double frictionForceY = 0.0;

        /* Calculations if there is a force acting on the robot */
        if(actingForce)
        {
            frictionForceX = -(actingForceX / fabs(actingForce)) * kineticFrictionForce;
            frictionForceY = -(actingForceY / fabs(actingForce)) * kineticFrictionForce;
        }
        /* Calculations if there no force acting on the robot, but the robot is moving */
        else if(velocityMagnitude)
        {
            frictionForceX = -(robot->velX / velocityMagnitude) * kineticFrictionForce;
            frictionForceY = -(robot->velY / velocityMagnitude) * kineticFrictionForce;
        }

        robot->accelX = actingForceX + frictionForceX;
        robot->accelY = actingForceY + frictionForceY;
    }



}

void masterVelocity(Robot *robot)
{
    /*
    VX += AX * dt
    VY += AY * dt
    */
    robot->velX += robot->accelX * DELTA_TIME;
    robot->velY += robot->accelY * DELTA_TIME;
}

void masterPosition(Robot *robot)
{
    /*
    X += VX * dt
    V += VY * dt
    */
    robot->posX += robot->velX * DELTA_TIME;
    robot->posY += robot->velY * DELTA_TIME;
}
