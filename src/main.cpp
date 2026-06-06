#include "libs.hpp"
#include "Console.hpp"

int main(int argc, char *argv[])
{
    const char *ch = u8"\u2588";
    
    winsize ws = updateSize();
    hideCursor();


    for(unsigned int j = 0; j < ws.ws_col; ++j){
        for(unsigned int i = 0; i < ws.ws_row; ++i){
            moveCursor(Pos(i+1, j+1));
            setColourRGB(0xff/ws.ws_row*i, 0xff/ws.ws_col*j, (0xff-0xff/(ws.ws_col+ws.ws_row)*(j+i)));
            std::cout<<ch;
        }
    }
    setColourRGB(0xFF,0xFF,0xFF);   
    drawRect(Pos(ws.ws_row, ws.ws_col), Pos(1,1), ch);

    std::cout<<std::endl;


    showCursor();
    return EXIT_SUCCESS;
}
