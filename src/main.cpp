#include "libs.hpp"
#include "Console.hpp"
#include "Shortlist.hpp"
#include "Task.hpp"
#include "GUI.hpp"

// enum Menu {Idle, Tasks, Buttons, TaskEdit};


int main(int argc, char *argv[])
{
    const char *ch = u8"\u2588";
    Shortlist<Task> tasks;
    Pos option(0,0);
    // Menu curr_menu = Idle;
    
    setupConsole();
    winsize ws = updateSize();

    int queue_len = ws.ws_col-2;
    int input_val = 0;

   
    clearConsole();
    drawBG(ws, ch);
                


    do {
        
        pollfd fds;
        fds.fd = STDIN_FILENO;
        fds.events = POLLIN;
        nfds_t nfds = 1;

        if(poll(&fds,  nfds, 100) > 0){
            char keys[3] = {0};

            read(STDIN_FILENO, &keys[0], 1);
            if(keys[0] == 0x1B){//  ESC and similar begin on this code.
                if(poll(&fds,  nfds, 20) > 0){
                    read(STDIN_FILENO, &keys[1], 1);
                    if(keys[1] == 0x5B && poll(&fds,  nfds, 20) > 0){
                        read(STDIN_FILENO, &keys[2], 1);
                        switch (keys[2]) {
                            case 'A':
                                option.y == 0?
                                    option.y = tasks.getSize()-1 : --option.y; 
                                break;
                            case 'B':
                                option.y == tasks.getSize()-1?
                                    option.y = 0 : ++option.y; 
                                break;
                            case 'C':
                                option.x == 3?
                                    option.x = 0 : ++option.x; 
                                break;
                            case 'D':
                                option.x == 0? 
                                    option.x = 3: --option.x; 
                                break;
                        }
                    }
                }
                else    //  Just ESC pressed.
                        break;
                input_val = -1;
            }
            else if(tasks.getSize() 
                && keys[0] <= '9' && keys[0] >= '0'){
                if(input_val == -1) input_val = keys[0]-'0';
                else input_val = input_val*10 + keys[0]-'0';

                
                switch (option.x) {
                    case 0:
                        tasks.getPtr(option.y)->priority = input_val;
                        break;
                    case 1:
                        tasks.getPtr(option.y)->p = input_val;
                        break;
                    case 2:
                        tasks.getPtr(option.y)->t = input_val;
                        break;
                    case 3:
                        tasks.getPtr(option.y)->d = input_val;
                        break;
                }
            }
            else {
                switch (keys[0] & ~0b00100000) {// Unsafe uppercase.
                    case 'A':
                        tasks.add(Task(100, 50, 50));
                        break;
                    case 'D':
                        if(tasks.getSize()){
                            tasks.pop(option.y);
                            if(option.y) option.y--;
                        }
                        break;
                }
            }
        }

        
        hideCursor();
        drawTaskBar(ws, *tasks, ch);
        drawTaskList(ws, *tasks, option);
        moveCursor(Pos(
                    ws.ws_col/2 + ws.ws_col*option.x/8,
                    9+option.y
        ));
        setColourRGB(0xFFFFFF);
        showCursor();

        std::this_thread::sleep_for(std::chrono::milliseconds(80));

    }while (1);


    std::cout<<std::endl;


    resetConsole();
    return EXIT_SUCCESS;
}
