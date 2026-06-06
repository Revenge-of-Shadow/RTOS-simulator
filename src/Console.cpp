#include "Console.h"
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <unistd.h>

winsize windowsize;

void setupConsole(){
    //Some code I copied 
    //from someone who copied some code
    //to get unbuffered input on linux
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

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
winsize updateSize(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowsize);
    return windowsize;
}
winsize getSize(){
    return windowsize;
}
