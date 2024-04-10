/* Noah Klein */

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <math.h>

#include "include/RobotWidget.hpp"

RobotWidget::RobotWidget(int x, int y, int width, int height)
    : Fl_Widget(x, y, width, height), x(x), y(y), width(width), height(height), angle(0.0) {}

void RobotWidget::setPose(double newX, double newY, double newAngle) {
    x = newX;
    y = newY;
    angle = newAngle;
}

void RobotWidget::draw() {
    fl_color(FL_BLACK);

    // Compute the coordinates of rectangle corners
    double x1 = -width / 2;
    double y1 = -height / 2;
    double x2 = width / 2;
    double y2 = -height / 2;
    double x3 = width / 2;
    double y3 = height / 2;
    double x4 = -width / 2;
    double y4 = height / 2;

    // Rotate the coordinates
    double cosA = cos(angle);
    double sinA = sin(angle);
    double x1r = x1 * cosA - y1 * sinA;
    double y1r = x1 * sinA + y1 * cosA;
    double x2r = x2 * cosA - y2 * sinA;
    double y2r = x2 * sinA + y2 * cosA;
    double x3r = x3 * cosA - y3 * sinA;
    double y3r = x3 * sinA + y3 * cosA;
    double x4r = x4 * cosA - y4 * sinA;
    double y4r = x4 * sinA + y4 * cosA;

    // Translate the rotated coordinates to the position of the rectangle
    x1r += x; y1r += y;
    x2r += x; y2r += y;
    x3r += x; y3r += y;
    x4r += x; y4r += y;

    // Draw the rotated rectangle
    fl_begin_complex_polygon();
    fl_vertex(x1r, y1r);
    fl_vertex(x2r, y2r);
    fl_vertex(x3r, y3r);
    fl_vertex(x4r, y4r);
    fl_end_complex_polygon();

    // Draw the rotated heading indicator
    const double triDepth = 15;
    const double triInset = 5;
    const double triTipLength = 15;

    fl_color(FL_RED);
    fl_begin_complex_polygon();
    fl_vertex(x1r + triDepth * cosA - triInset * sinA, y1r + triDepth * sinA + triInset * cosA);
    fl_vertex((x1r+x2r)/2 + triTipLength * sinA, (y1r+y2r)/2 - triTipLength * cosA);
    fl_vertex(x2r - triDepth * cosA -  triInset * sinA, y2r - triDepth * sinA + triInset * cosA);
    fl_end_complex_polygon();
}
