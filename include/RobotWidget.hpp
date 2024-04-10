/* Noah Klein  */

#ifndef ROBOT_WIDGET_HPP
#define ROBOT_WIDGET_HPP

#include <FL/Fl_Widget.H>

class RobotWidget : public Fl_Widget {
private:
    double x, y; // Position of the rectangle
    double width, height; // Dimensions of the rectangle
    double angle; // Rotation angle in radians

public:
    RobotWidget(int x, int y, int width, int height);
    void setRotationAngle(double newAngle);
    void setPose(double newX, double newY, double newAngle);
    void draw() override;
};


extern RobotWidget *robotGUI;

#endif // ROBOT_WIDGET_HPP
