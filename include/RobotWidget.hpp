/* Noah Klein  */

#ifndef ROBOT_WIDGET_HPP
#define ROBOT_WIDGET_HPP

#include "Robot.hpp"
#include <FL/Fl_Widget.H>


class RobotWidget : public Fl_Widget {
private:
    struct Point{
        double x;
        double y;
    };

    /* Robot related information */
    double angle_rad; // Rotation angle in radians
    double xPos_pix, yPos_pix;
    double width_pix, height_pix;
    double wheelCenterDist_pix;

    bool showDistanceSensorLines;
    
    Point rotatedOffsetPoint(double xPix, double yPix, double angle, double xOffset, double yOffset);

    void drawRotatedRectangle(Fl_Color color, double x_pix, double y_pix, double width_pix, double height_pix, double angle);
    void drawRotatedTriangle(Fl_Color color, double x_pix, double y_pix, double base_pix, double height_pix, double angle);

    Robot *robot;

public:
    RobotWidget(Robot *robot, double initial_x, double initial_y, double widget_width, double widget_height, bool showDistanceSensorLines);
    void setRotationAngle(double newAngle);

    void draw() override;
};

#endif // ROBOT_WIDGET_HPP
