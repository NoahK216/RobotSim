/* Noah Klein */

#ifndef FIELD_PERIMETER_HPP
#define FIELD_PERIMETER_HPP

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include "constants.hpp"

class FieldPerimeter : public Fl_Widget {
public:
    /**
    * @brief Construct a new Rectangle Widget object with meters as the unit of measurement
    */
    FieldPerimeter(double x, double y, double w, double h)
        : Fl_Widget(x * METERS_TO_PIXELS, y * METERS_TO_PIXELS, w * METERS_TO_PIXELS, h * METERS_TO_PIXELS) {
            this->topLeft = {double(x), double(y)};
            this->topRight = {double(x + w), double(y)};
            this->bottomLeft = {double(x), double(y + h)};
            this->bottomRight = {double(x + w), double(y + h)};

            this->topY = y;
            this->bottomY = y + h;
            this->leftX = x;
            this->rightX = x + w;
        }

    void draw() override {
        fl_color(FL_BLACK);
        fl_rect(x(), y(), w(), h());
    }

    double topY;
    double bottomY;
    double leftX;
    double rightX;

    Point topLeft;
    Point topRight;
    Point bottomLeft;
    Point bottomRight;
};

#endif // FIELD_PERIMETER_HPP