#include "Console.hpp"
winsize ws;

void setupConsole(){
    //Some code I copied 
    //from someone who copied some code
    //to get unbuffered input on linux
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

}
winsize updateSize(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws;
}
winsize getSize(){
    return ws;
}

void setColour(Colour c){
    std::cout<<"\033["<<c<<"m";
}
void setColourRGB(unsigned int  r, unsigned int  g, unsigned int  b){
    std::cout<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m";
}
void moveCursor(Pos pos){
    std::cout<<"\033["<<pos.x<<";"<<pos.y<<"H";
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
