/* Noah Klein */

#include "Robot.hpp"

void masterAcceleration(Robot *robot, double actingForce);
void masterPhysics(Robot *robot);
void masterPosition(Robot *robot);
void masterVelocity(Robot *robot);
void applyKineticFriction(Robot *robot, double actingForce);
void applyDampingForce(Robot *robot);
