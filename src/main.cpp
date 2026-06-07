#include "libs.hpp"
#include "Console.hpp"
#include "Shortlist.hpp"

int main(int argc, char *argv[])
{
    const char *ch = u8"\u2588";
    
    setupConsole();
    winsize ws = updateSize();
    hideCursor();


    constexpr int str_len = 3;
    char c[str_len] = {0};

    do {
    
        setColourRGB(0x0A,0x0A,0x0A);   
        drawRectFilled(Pos(ws.ws_row, ws.ws_col), Pos(1,1), ch);
        setColourRGB(0xFF,0xFF,0xFF);   
        drawRect(Pos(ws.ws_row, ws.ws_col), Pos(1,1), ch);
                

        pollfd fds;
        fds.fd = STDIN_FILENO;
        fds.events = POLLIN;
        nfds_t nfds = 1;

        if(poll(&fds,  nfds, 100) > 0){
            char c[str_len] = {0};
            read(STDIN_FILENO, &c[0], 1);
            if(c[0] == 0x1B){
                if(poll(&fds,  nfds, 20) > 0){
                    read(STDIN_FILENO, &c[1], 1);
                    if(c[1] == 0x5B){}
                }
                else
                    break;
            }
        }

        
        moveCursor(Pos(ws.ws_row/2, ws.ws_col/2));
        std::cout<<c;

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }while (1);


    std::cout<<std::endl;


    resetConsole();
    return EXIT_SUCCESS;
}
