#include "libs.h"

enum Colour {
    Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White, 
    BrightBlack = 90, BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta, BrightCyan, BrightWhite
};
struct Pos{
    unsigned int x;
    unsigned int y;

    Pos (unsigned int x, unsigned int y): x(x), y(y){}
};

void setupConsole();
void setColour(Colour c);
void setColourRGB(unsigned int  r, unsigned int  g, unsigned int  b);
void moveCursor(Pos pos);

winsize updateSize();
winsize getSize();
