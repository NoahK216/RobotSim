/* Noah Klein */

#include <FL/Fl.H>

#include "include/debug.hpp"

#include "include/sim.hpp"

void handleKeyboardInput(int *isW, int *isA, int *isS, int *isD)
{
    *isW = Fl::get_key('w') != 0;
    *isA = Fl::get_key('a') != 0;
    *isS = Fl::get_key('s') != 0;
    *isD = Fl::get_key('d') != 0;

    if(0) printf("W:%d, A:%d, S:%d, D:%d\n", *isW, *isA, *isS, *isD);
}
