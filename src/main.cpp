#include "libs.hpp"
#include "Console.hpp"
#include "Shortlist.hpp"
#include "Task.hpp"
#include "GUI.hpp"



int main(int argc, char *argv[])
{
    const char *ch = u8"\u2588";
    Shortlist<Task> tasks;
    Pos option(0,0);

    
    setupConsole();
    winsize ws = updateSize();

    const int queue_len = ws.ws_col-4;
    int queue_bits[queue_len];
    int input_val = 0;
    //  Shortlist<int> free_ids;
    int free_id = 0;

   
    clearConsole();
    hideCursor();
    drawBG(ws, ch);

    do {
        Task curr;
        Shortlist<Task> stack;
        
        for(int i = 0; i < queue_len; ++i){
            queue_bits[i] = -1;

            for(int t = 0; t < tasks.getSize(); ++t){
                if(tasks[t].offset == i%tasks[t].p){
                    //At this moment a task should start.
                    if(curr.time_started != -1){
                        //Task present.
                        if(curr.priority < tasks[t].priority){
                            //New has lower priority, stash it.
                            Task pending = tasks[t];
                            pending.time_started = i;
                            stack.add(pending);
                        }
                        else{
                            //Current has lower priority, stash it.
                            stack.add(curr);
                            curr = tasks[t];
                            curr.time_started = i;
                        }
                    }
                    else{
                        curr = tasks[t];
                        curr.time_started = i;
                    }
                }
           }

           if(curr.time_started != -1){
                //Task present.
                queue_bits[i] = curr.id;
                if(!curr.left){
                    curr.time_started = -1;
                    if(stack.getSize()){
                        int ind = stack.getSize()-1;
                        for(int s = stack.getSize()-2; s >=0; --s)
                            if(stack[s].priority < stack[ind].priority)
                                ind = s;
                        curr = stack.pop(ind);
                    }
                }
            }
        }
        
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
                                option.x == 4?
                                    option.x = 0 : ++option.x; 
                                break;
                            case 'D':
                                option.x == 0? 
                                    option.x = 4: --option.x; 
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
                        tasks.getPtr(option.y)->offset = input_val;
                        break;
                    case 1:
                        tasks.getPtr(option.y)->priority = input_val;
                        break;
                    case 2:
                        tasks.getPtr(option.y)->p = input_val;
                        break;
                    case 3:
                        tasks.getPtr(option.y)->t = input_val;
                        tasks.getPtr(option.y)->left = input_val;
                        break;
                    case 4:
                        tasks.getPtr(option.y)->d = input_val;
                        break;
                }
            }
            else {
                switch (keys[0] & ~0b00100000) {// Unsafe uppercase.
                    case 'A':
                        tasks.add(Task(10, 5, 10, free_id));
                        free_id = tasks.getSize();
                        break;
                    case 'D':
                        if(tasks.getSize()){
                            free_id = option.y;
                            tasks.pop(option.y);
                            if(option.y) option.y--;
                        }
                        break;
                }
            }
        }

        
        drawTaskBar(ws, queue_bits, queue_len, ch);
        drawTaskList(ws, *tasks, option);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        drawStats(ws, *tasks);

    }while (1);


    std::cout<<std::endl;


    resetConsole();
    return EXIT_SUCCESS;
}
