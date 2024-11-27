/* Noah Klein */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define DELTA_TIME 0.05
#define GRAVITY_MSS 9.807
#define METERS_TO_PIXELS 80

struct Point{
    double x;
    double y;
};

struct Particle{
    double x;
    double y;
    double theta;
    double weight;
};

#endif
