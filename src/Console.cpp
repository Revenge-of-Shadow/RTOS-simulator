#include "Console.hpp"
#include <algorithm>
#include <iostream>
winsize ws;
struct termios old_term, new_term;

winsize updateSize(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws;
}
winsize getSize(){
    return ws;
}

void setupConsole(){
    //Some code I copied 
    //from someone who copied some code
    //to get unbuffered input on linux
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &new_term);

    clearConsole();
}
void resetConsole(){
    tcsetattr(STDIN_FILENO, TCSADRAIN, &old_term);
    showCursor(); 
}
void clearConsole(){
    std::cout<<"\033[2J";
}
void setColour(Colour c){
    std::cout<<"\033["<<c<<"m";
}
void setColourRGB(unsigned int  r, unsigned int  g, unsigned int  b){
    std::cout<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m";
}
void setColourRGB(unsigned int  rgb){
    setColourRGB(rgb >> 8*2, rgb >> 8 & 0xFF, rgb & 0xFF);
}
void setBackgroundRGB(unsigned int  r, unsigned int  g, unsigned int  b){
    std::cout<<"\033[48;2;"<<r<<";"<<g<<";"<<b<<"m";
}
void setBackgroundRGB(unsigned int  rgb){
    setBackgroundRGB(rgb >> 8*2, rgb >> 8 & 0xFF, rgb & 0xFF);
}
void moveCursor(Pos pos){
    std::cout<<"\033["<<pos.y<<";"<<pos.x<<"H";
}
void hideCursor(){
    std::cout<<"\033[?25l";
}
void showCursor(){
    std::cout<<"\033[?25h";
}


void drawLine(Pos p1, Pos p2, const char* ch){
    Pos diff = p2-p1;
    int steps = std::max(abs(diff.x), abs(diff.y));
    double xstep = diff.x / (double)steps; 
    double ystep = diff.y / (double)steps; 

    double x = p1.x; double y = p1.y;
    for(int i = 0; i <= steps; ++i){
        moveCursor(Pos(floor(x),floor(y)));
        std::cout<<ch;
        x+=xstep; y+=ystep;
    } 
}
void drawRect(Pos p1, Pos p2, const char* ch){
    drawLine(Pos(p1.x, p1.y), Pos(p2.x, p1.y), ch);
    drawLine(Pos(p2.x, p1.y), Pos(p2.x, p2.y), ch);
    drawLine(Pos(p1.x, p2.y), Pos(p2.x, p2.y), ch);
    drawLine(Pos(p1.x, p1.y), Pos(p1.x, p2.y), ch);
}
void drawRectFilled(Pos p1, Pos p2, const char* ch){
    int x = std::min(p1.x, p2.x);
    int y = std::min(p1.y, p2.y);
    int max_x = std::max(p1.x, p2.x); 
    int max_y = std::max(p1.y, p2.y); 

    for(; y <= max_y; ++y){
        for(; x <= max_x; ++x){
            moveCursor(Pos(x, y));
            std::cout<<ch;
        }
    }
}
