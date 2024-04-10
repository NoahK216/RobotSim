/* Noah Klein  */

#ifndef ROBOT_WIDGET_HPP
#define ROBOT_WIDGET_HPP

#include <FL/Fl_Widget.H>

#define METERS_TO_PIXELS 80

class RobotWidget : public Fl_Widget {
private:
    double x, y; // Position of the rectangle
    double width, height; // Dimensions of the rectangle
    double angle; // Rotation angle in radians

    double xPix, yPix;
    double widthPix, heightPix;

public:
    RobotWidget(double x, double y, double width, double height);
    void setRotationAngle(double newAngle);
    void setPose(double newX, double newY, double newAngle);
    void draw() override;
};

#endif // ROBOT_WIDGET_HPP
