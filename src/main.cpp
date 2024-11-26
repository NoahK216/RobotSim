/* Noah Klein */

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <math.h>

#include "../include/Robot.hpp"
#include "../include/RobotWidget.hpp"
#include "../include/physics.hpp"

#include "../include/debug.hpp"
#include "../include/constants.hpp"

#include "../include/main.hpp"


struct windowUpdatePackage{
    Fl_Double_Window *window;
    Robot *robot;
    RobotWidget *robotGUI;
};


void windowUpdate(void *data) {
    static unsigned i = 0;

    /* The loop */
    //Fl_Double_Window *o = (Fl_Double_Window *)data;
    windowUpdatePackage *package = (windowUpdatePackage*)data;
    RobotWidget *robotGUI = package->robotGUI; // Define the extern RobotWidget declared in RobotWidget.hpp
    Robot *robot = package->robot; // Define the extern Robot declared in Robot.hpp


    /* Pass a pointer to the robot to masterPhysics */
    masterPhysics(robot);

    /* Update the robots position after physics calulations */
    robotGUI->setPose(robot->posX, robot->posY, robot->headingRad);
    if(DEBUG) printf("Acceleration\tL: %6.2f\tR: %6.2f\nVelocity\tX: %6.2f\tY: %6.2f\nPosition\tX: %6.2f\tY: %6.2f\n\n"
        , robot->accelWheelLeft, robot->accelWheelRight
        , robot->velX, robot->velY
        , robot->posX, robot->posY);


    /* Finally, redraw */
    package->window->redraw();

    i++;
    Fl::add_timeout(DELTA_TIME, windowUpdate, data);
}

int main(int argc, char **argv) {
    const double fieldLength = 10;


    Fl_Double_Window *window = new Fl_Double_Window(fieldLength*METERS_TO_PIXELS, fieldLength*METERS_TO_PIXELS, "RobotSim");
    /*TODO: Make constants more accurate to real world*/ 
    
    /* Units:   Xm Ym Hdg  WheelRadM  Mkg*/
    Robot robot(5, 5, 180, 0.0523875, 6.8);

    /* Units:            Xm Ym   Xm  Ym*/
    RobotWidget robotGUI(5, 5, 0.4, 0.4);

    /* Create a package to pass to the window timeout */
    windowUpdatePackage package = {window, &robot, &robotGUI};
    
    /* Add the RobotWidget to the window */
    window->add(&robotGUI);

    Fl::add_timeout(0, windowUpdate, &package);
    window->end();
    Fl::visual(FL_DOUBLE | FL_INDEX);
    window->show();

    return Fl::run();
}
