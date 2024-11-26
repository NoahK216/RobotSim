/* Noah Klein */

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Rect.H>

#include <math.h>

#include "../include/Robot.hpp"
#include "../include/RobotWidget.hpp"
#include "../include/RectWidget.hpp"
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
    windowUpdatePackage *package = (windowUpdatePackage*)data;
    RobotWidget *robotGUI = package->robotGUI; // Define the extern RobotWidget declared in RobotWidget.hpp
    Robot *robot = package->robot; // Define the extern Robot declared in Robot.hpp


    /* Pass a pointer to the robot to masterPhysics */
    masterPhysics(robot);

    if(DEBUG) printf("Accel M/SS\tL: %6.2f\tR: %6.2f\nVelocity M/S\tX: %6.2f\tY: %6.2f\nPosition M\tX: %6.2f\tY: %6.2f\n\n"
        , robot->accelWheelLeft, robot->accelWheelRight
        , robot->velX, robot->velY
        , robot->xPos_m, robot->yPos_m);


    /* Finally, redraw, RobotWidget has a pointer to robot */
    package->window->redraw();

    i++;
    Fl::add_timeout(DELTA_TIME, windowUpdate, data);
}

int main(int argc, char **argv) {
    const double windowLength_m = 6;
    const double fieldLength_m = 3.6576;
    const double center_m = windowLength_m/2;

    Fl_Double_Window *window = new Fl_Double_Window(windowLength_m*METERS_TO_PIXELS, windowLength_m*METERS_TO_PIXELS, "RobotSim");

    /* Units:   Xm        Ym        Wm   Hm   Hdg  WheelRadM  Mkg */
    Robot robot(center_m, center_m, 0.4, 0.4, 180, 0.0523875, 6.8);
    
    RobotWidget robotGUI(&robot, true);

    /* Create a package to pass to the window timeout */
    windowUpdatePackage package = {window, &robot, &robotGUI};
    
    /* Add the RobotWidget to the window */
    window->add(&robotGUI);

    /* Add the field outline to the window */
    RectangleWidget *rect = new RectangleWidget(center_m- fieldLength_m/2, center_m- fieldLength_m/2, fieldLength_m, fieldLength_m);
    window->add(rect);

    Fl::add_timeout(0, windowUpdate, &package);
    window->end();
    Fl::visual(FL_DOUBLE | FL_INDEX);
    window->show();

    return Fl::run();
}
