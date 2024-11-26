/* Noah Klein */

#ifndef RECT_WIDGET_HPP
#define RECT_WIDGET_HPP

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include "../include/constants.hpp"

class RectangleWidget : public Fl_Widget {
public:
    /**
    * @brief Construct a new Rectangle Widget object with meters as the unit of measurement
    */
    RectangleWidget(int x, int y, int w, int h)
        : Fl_Widget(x * METERS_TO_PIXELS, y * METERS_TO_PIXELS, w * METERS_TO_PIXELS, h * METERS_TO_PIXELS) {}

    void draw() override {
        fl_color(FL_BLACK);
        fl_rect(x(), y(), w(), h());
    }
};

#endif // RECT_WIDGET_HPP