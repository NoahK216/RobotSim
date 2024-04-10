/* Noah Klein */

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <math.h>

#include "include/Robot.hpp"
#include "include/RobotWidget.hpp"
#include "include/physics.hpp"

#include "include/debug.hpp"
#include "include/constants.hpp"

#include "include/main.hpp"

#define KEYBOARD_BUFFER_SIZE 8

RobotWidget *robotGUI; // Define the extern RobotWidget declared in RobotWidget.hpp
Robot *robot; // Define the extern Robot declared in Robot.hpp

char buffer[KEYBOARD_BUFFER_SIZE];
static int buffer_count = 0;

void keyHandler(int key) {
    /* This currently only grabs the first char of event_text. shouldnt be an issue but might be */
    char c = Fl::event_text()[0];
    if(buffer_count < KEYBOARD_BUFFER_SIZE)
    {
        buffer[buffer_count] = c;
        buffer_count++;
    }
}

void winUpdate(void *data) {
    static unsigned i = 0;

    /* The loop */
    Fl_Double_Window *o = (Fl_Double_Window *)data;

    /* Pass a pointer to the robot to masterPhysics */
    masterPhysics((Robot*)robot, buffer, buffer_count);

    /* Update the robots position after physics calulations */
    robotGUI->setPose(robot->posX, robot->posY, robot->headingRad);
    if(DEBUG) printf("Acceleration\tX: %5.2f\tY:%5.2f\nVelocity\tX: %6.2f\tY:%6.2f\nPosition\tX: %6.2f\tY:%6.2f\n\n"
        , robot->accelX, robot->accelY
        , robot->velX, robot->velY
        , robot->posX, robot->posY);


    /* Finally, redraw */
    o->redraw();

    /* "clear" the buffer */
    buffer_count = 0;

    i++;
    Fl::add_timeout(DELTA_TIME, winUpdate, data);
}

int main(int argc, char **argv) {
    robot = new Robot(100, 100, 180, 2);
    robotGUI = new RobotWidget(200, 200, 75, 75);



    Fl_Double_Window *window = new Fl_Double_Window(1400, 800, "RobotSim");
    
    window->add(robotGUI);
    Fl::add_timeout(0, winUpdate, window);
    window->end();
    Fl::visual(FL_DOUBLE | FL_INDEX);
    window->show();

    /* Add the key handler */
    Fl::add_handler([](int event) {
        /* Handle the event if a key was pressed that is not esc */
        if (event == 12 && Fl::event_key() != FL_Escape) {
            keyHandler(Fl::event_key());
            return 1; /* Event handled */
        }
        return 0; /* Event not handled */
    });




    return Fl::run();
}
