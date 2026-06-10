#ifndef CONSOLE
#define CONSOLE

#include "libs.hpp"

enum Colour {
    Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White, 
    BrightBlack = 90, BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta, BrightCyan, BrightWhite
};
struct Pos{
    int x;
    int y;

    Pos (int x, int y): x(x), y(y){}

    Pos operator=(const Pos& other){
        if(this != &other){
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    Pos operator+(const Pos& other){
        return Pos(x + other.x, y + other.y);
    }
    Pos operator-(const Pos& other){
        return Pos(x - other.x, y - other.y);
    }
};

void setupConsole();
void resetConsole();
void clearConsole();
void setColour(Colour c);
void setColours(unsigned int bg, unsigned int fg);
void setColourRGB(unsigned int  r, unsigned int  g, unsigned int  b);
void setColourRGB(unsigned int rgb);
void setBackgroundRGB(unsigned int  r, unsigned int  g, unsigned int  b);
void setBackgroundRGB(unsigned int rgb);
void moveCursor(Pos pos);
void hideCursor();
void showCursor();

winsize updateSize();
winsize getSize();

void drawLine(Pos p1, Pos p2, const char* ch);
void drawRect(Pos p1, Pos p2, const char* ch);
void drawRectFilled(Pos p1, Pos p2, const char* ch);

#endif // !CONSOLE
