#include "libs.hpp"
#include "Console.hpp"
#include "Shortlist.hpp"
#include "Task.hpp"
#include "GUI.hpp"

// enum Menu {Idle, Tasks, Buttons, TaskEdit};
int option;

// void addTask(Shortlist<Task> &tasks){  }
// void rmTask(Shortlist<Task> &tasks, unsigned int ind){ }

int main(int argc, char *argv[])
{
    const char *ch = u8"\u2588";
    Shortlist<Task> tasks;
    option = 0;
    // Menu curr_menu = Idle;
    
    setupConsole();
    winsize ws = updateSize();
    hideCursor();

    int queue_len = ws.ws_col-2;

   
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
                    if(keys[1] == 0x5B){}
                }
                else    //  Just ESC pressed.
                        break;
            }
            else switch (keys[0] & ~0b00100000) {// Unsafe uppercase.
                case 'A':
                    tasks.add(Task(100, 50, 50));
                    break;
                case 'D':
                    if(tasks.getSize()) tasks.pop(option);
                    break;
            }
            
        }

        
        drawTaskBar(ws, ch);
        drawTaskList(ws, *tasks);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }while (1);


    std::cout<<std::endl;


    resetConsole();
    return EXIT_SUCCESS;
}
