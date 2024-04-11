/* Noah Klein  */

#ifndef ROBOT_WIDGET_HPP
#define ROBOT_WIDGET_HPP

#include <FL/Fl_Widget.H>

#define METERS_TO_PIXELS 80

class RobotWidget : public Fl_Widget {
private:
    struct Point{
        double x;
        double y;
    };

    double x, y; // Position of the rectangle
    double width, height; // Dimensions of the rectangle
    double angle; // Rotation angle in radians

    double xPix, yPix;
    double widthPix, heightPix;
    double wheelCenterDistPix;
    
    Point rotatedOffsetPoint(double xPix, double yPix, double angle, double xOffset, double yOffset);

    void drawRotatedRectangle(Fl_Color color, double x_pix, double y_pix, double width_pix, double height_pix, double angle);
    void drawRotatedTriangle(Fl_Color color, double x_pix, double y_pix, double base_pix, double height_pix, double angle);

public:
    RobotWidget(double x, double y, double width, double height);
    void setRotationAngle(double newAngle);
    void setPose(double newX, double newY, double newAngle);
    void draw() override;
};

#endif // ROBOT_WIDGET_HPP
