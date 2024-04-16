/* Noah Klein */

void applyDampingForce(Robot *robot);
void applyKineticFriction(Robot *robot, double actingForce);
void masterMotorTorque(Robot *robot, int mVoltsLeft, int mVoltsRight);
void masterPhysics(Robot *robot);
void masterPose(Robot *robot);
template <typename T> int signum(T val) ;
void wheelVelocity(Robot *robot);
