/* Noah Klein  */

#ifndef ROBOT_WIDGET_HPP
#define ROBOT_WIDGET_HPP

#include "Robot.hpp"
#include <FL/Fl_Widget.H>

#define METERS_TO_PIXELS 80

class RobotWidget : public Fl_Widget {
private:
    struct Point{
        double x;
        double y;
    };
    double angle; // Rotation angle in radians

    double xPix, yPix;
    double widthPix, heightPix;
    double wheelCenterDistPix;
    
    Point rotatedOffsetPoint(double xPix, double yPix, double angle, double xOffset, double yOffset);

    void drawRotatedRectangle(Fl_Color color, double x_pix, double y_pix, double width_pix, double height_pix, double angle);
    void drawRotatedTriangle(Fl_Color color, double x_pix, double y_pix, double base_pix, double height_pix, double angle);

    Robot *robot;

public:
    RobotWidget(Robot *robot, double x, double y, double width, double height);
    void draw() override;
};

#endif // ROBOT_WIDGET_HPP
