#include "libs.h"
#include "Console.h"

int main(int argc, char *argv[])
{
    
    // std::cout<<"\033[38;2;{255};{0};{0}m"<<"R";
    // std::cout<<"\033[38;2;{0};{255};{0}m"<<"G";
    // std::cout<<"\033[38;2;{0};{0};{255}m"<<"B";
    
    winsize ws = updateSize();

    for(unsigned int j = 1; j < ws.ws_col; ++j){
        for(unsigned int i = 1; i < ws.ws_row; ++i){
            moveCursor(Pos(i, j));
            setColourRGB(0xff/ws.ws_row*i, 0xff/ws.ws_col*j, 0xff/(ws.ws_col+ws.ws_row)*(j+i));
            std::cout<<"█";
        }
    }
    
    return EXIT_SUCCESS;
}
