/* Noah Klein */

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <math.h>

#include "../include/debug.hpp"
#include "../include/constants.hpp"
#include "../include/RobotWidget.hpp"


void RobotWidget::drawRotatedRectangle(Fl_Color color, double x_pix, double y_pix, double width_pix, double height_pix, double angle)
{
    fl_color(color);

    // Define the vertices of the rectangle
    Point vertices[4] = {
        {-width_pix / 2, -height_pix / 2},
        {width_pix / 2, -height_pix / 2},
        {width_pix / 2, height_pix / 2},
        {-width_pix / 2, height_pix / 2}
    };

    // Rotate the coordinates
    double cosA = cos(angle);
    double sinA = sin(angle);
    for (int i = 0; i < 4; i++)
    {
        double x = vertices[i].x;
        double y = vertices[i].y;
        vertices[i].x = x * cosA - y * sinA;
        vertices[i].y = x * sinA + y * cosA;
    }

    // Translate the rotated coordinates to the position of the rectangle
    for (int i = 0; i < 4; i++)
    {
        vertices[i].x += x_pix;
        vertices[i].y += y_pix;
    }

    // Draw the rotated rectangle
    fl_begin_complex_polygon();
    for (int i = 0; i < 4; i++)
    {
        fl_vertex(vertices[i].x, vertices[i].y);
    }
    fl_end_complex_polygon();
}


void RobotWidget::drawRotatedTriangle(Fl_Color color, double x_pix, double y_pix, double base_pix, double height_pix, double angle)
{
    fl_color(color);

    // Define the vertices of the triangle
    Point vertices[3] = {
        {0.0, -height_pix / 2}, // Top vertex
        {-base_pix / 2, height_pix / 2}, // Bottom left vertex
        {base_pix / 2, height_pix / 2} // Bottom right vertex
    };

    // Rotate the coordinates
    double cosA = cos(angle);
    double sinA = sin(angle);
    for (int i = 0; i < 3; i++) {
        double x = vertices[i].x;
        double y = vertices[i].y;
        vertices[i].x = x * cosA - y * sinA;
        vertices[i].y = x * sinA + y * cosA;
    }

    // Translate the rotated coordinates to the position of the triangle
    for (int i = 0; i < 3; i++)
    {
        vertices[i].x += x_pix;
        vertices[i].y += y_pix;
    }

    // Draw the rotated triangle
    fl_begin_complex_polygon();
    for (int i = 0; i < 3; i++)
    {
        fl_vertex(vertices[i].x, vertices[i].y);
    }
    fl_end_complex_polygon();
}

Point RobotWidget::rotatedOffsetPoint(double xPix, double yPix, double angle, double xOffset, double yOffset)
{
    return {xPix + cos(angle) * xOffset - sin(angle) * yOffset, yPix + sin(angle) * xOffset + cos(angle) * yOffset};
}

void RobotWidget::drawDistanceSensorLines(){
    fl_color(FL_BLUE); // Set the line color
    fl_line_style(FL_SOLID, 2); // Set the line style to solid with width 5

    int frontLineLength = robot->frontDistanceMeasurement() * METERS_TO_PIXELS;
    Point frontPoint = rotatedOffsetPoint(xPos_pix, yPos_pix, angle_rad, 0, -frontLineLength);

    int backLineLength = robot->rearDistanceMeasurement() * METERS_TO_PIXELS;
    Point backPoint = rotatedOffsetPoint(xPos_pix, yPos_pix, angle_rad, 0, backLineLength);

    if(DEBUG)
        printf("Front Distance M: %f\nRear Distance M: %f\n\n", robot->frontDistanceMeasurement(), robot->rearDistanceMeasurement());

    fl_line(xPos_pix, yPos_pix, frontPoint.x, frontPoint.y);
    fl_line(xPos_pix, yPos_pix, backPoint.x, backPoint.y);

    fl_line_style(0); // Reset the line style to default
}

void RobotWidget::draw()
{
    xPos_pix = this->robot->xPos_pix();
    yPos_pix = this->robot->yPos_pix();
    angle_rad = this->robot->headingRad;

    const double cosA = cos(angle_rad);
    const double sinA = sin(angle_rad);

    const double wheelOffsetPix = 0.1524 * METERS_TO_PIXELS;

    Point rotatedPoint;
    
    /* Draw the robot */
    drawRotatedRectangle(FL_BLACK, xPos_pix, yPos_pix, width_pix, height_pix, angle_rad);

    /* Draw the heading indicator */
    rotatedPoint = rotatedOffsetPoint(xPos_pix, yPos_pix, angle_rad, 0, -height_pix/2 - 3);
    drawRotatedTriangle(FL_RED, rotatedPoint.x, rotatedPoint.y, width_pix - 10, 10, angle_rad);

    /* Draw the wheels */
    rotatedPoint = rotatedOffsetPoint(xPos_pix, yPos_pix, angle_rad, wheelOffsetPix, 0);
    drawRotatedRectangle(FL_RED, rotatedPoint.x, rotatedPoint.y, 5, height_pix-12, angle_rad);

    rotatedPoint = rotatedOffsetPoint(xPos_pix, yPos_pix, angle_rad, -wheelOffsetPix, 0);
    drawRotatedRectangle(FL_RED, rotatedPoint.x, rotatedPoint.y, 5, height_pix-12, angle_rad);

    if(showDistanceSensorLines)
        drawDistanceSensorLines();
    
}
