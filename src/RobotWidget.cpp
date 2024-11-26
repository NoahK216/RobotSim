/* Noah Klein */

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <math.h>

#include "../include/RobotWidget.hpp"

// Constructor for RobotWidget class, representing a widget for a robot
RobotWidget::RobotWidget(Robot *robot, double initial_x, double initial_y, double widget_width, double widget_height)
    : Fl_Widget(initial_x, initial_y, widget_width, widget_height), 
      robot(robot),
      widthPix(widget_width * METERS_TO_PIXELS), 
      heightPix(widget_height * METERS_TO_PIXELS)
{}

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

RobotWidget::Point RobotWidget::rotatedOffsetPoint(double xPix, double yPix, double angle, double xOffset, double yOffset)
{
    return {xPix + cos(angle) * xOffset - sin(angle) * yOffset, yPix + sin(angle) * xOffset + cos(angle) * yOffset};
}

void RobotWidget::draw()
{
    xPix = this->robot->posX * METERS_TO_PIXELS;
    yPix = this->robot->posY * METERS_TO_PIXELS;
    angle = this->robot->headingRad;

    const double cosA = cos(angle);
    const double sinA = sin(angle);

    const double wheelOffsetPix = 0.1524 * METERS_TO_PIXELS;

    Point rotatedPoint;
    
    /* Draw the robot */
    drawRotatedRectangle(FL_BLACK, xPix, yPix, widthPix, heightPix, angle);

    /* Draw the heading indicator */
    rotatedPoint = rotatedOffsetPoint(xPix, yPix, angle, 0, -heightPix/2 - 3);
    drawRotatedTriangle(FL_RED, rotatedPoint.x, rotatedPoint.y, widthPix - 10, 10, angle);

    /* Draw the wheels */
    rotatedPoint = rotatedOffsetPoint(xPix, yPix, angle, wheelOffsetPix, 0);
    drawRotatedRectangle(FL_RED, rotatedPoint.x, rotatedPoint.y, 5, heightPix-12, angle);

    rotatedPoint = rotatedOffsetPoint(xPix, yPix, angle, -wheelOffsetPix, 0);
    drawRotatedRectangle(FL_RED, rotatedPoint.x, rotatedPoint.y, 5, heightPix-12, angle);
}
