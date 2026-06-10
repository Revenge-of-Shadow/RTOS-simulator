#include "libs.hpp"
#include "Console.hpp"
#include "Shortlist.hpp"
#include "Task.hpp"
#include <iostream>

void drawBG(winsize ws, const char* ch){
    //  Initial graphics.
    setBackgroundRGB(0x303030);   
    setColourRGB(0x303030);
    drawRectFilled(Pos(1,1), Pos(ws.ws_col, ws.ws_row), ch);
    drawRect(Pos(1,1), Pos(ws.ws_col, ws.ws_row), ch);
    setColourRGB(0x484848);   
    drawRect(Pos(2,2), Pos(ws.ws_col-1, 5), ch);
    drawRect(Pos(2,4), Pos(ws.ws_col-1, 5), ch);
    drawRect(Pos(2,6), Pos(ws.ws_col-1, ws.ws_row-1), ch);
    setBackgroundRGB(0x404040);   
    setColourRGB(0xFFFFFF);
    for(int i = 5; i < ws.ws_col-2; i+=5){
        moveCursor(Pos(i + 2, 4));
        std::cout<<i;
    }
    setBackgroundRGB(0x303030);   
    setColourRGB(0xFFFFFF);
}
void drawTaskBar(winsize ws, const char* ch){
    setColourRGB(0x101010);
    drawLine(Pos(3,3), Pos(ws.ws_col-2, 3), ch);
}
void drawTaskList(winsize ws, const Shortlist<Task>* tasks, Pos option){
    setBackgroundRGB(0x707070);    
    setColourRGB(0x000000);
    drawLine(Pos(3, 7), Pos(ws.ws_col-2, 7), " ");

    moveCursor(Pos(3+2, 7));
    std::cout<<"Task";
    moveCursor(Pos(ws.ws_col*4/8, 7));
    std::cout<<"Prior";
    moveCursor(Pos(ws.ws_col*5/8, 7));
    std::cout<<"p";
    moveCursor(Pos(ws.ws_col*6/8, 7));
    std::cout<<"t";
    moveCursor(Pos(ws.ws_col*7/8, 7));
    std::cout<<"d";

    for(int i = 0; i < ws.ws_row-9; ++i){
        setColours(i%2? 0x282828 : 0x202020, 
            (i+1)*(0xFFFFFF/ws.ws_row));
        drawLine(Pos(3, 8+i), Pos(ws.ws_col-2, 8+i), " ");
         
        if(i >= tasks->getSize()) continue;
    
        moveCursor(Pos(3+2, 8+i));
        std::cout<<"Task_"<<i;
        if(tasks->peek(i).t > tasks->peek(i).d 
            || tasks->peek(i).t > tasks->peek(i).p
            || tasks->peek(i).d > tasks->peek(i).p){
            setColourRGB(0xFF0000);
            std::cout<<"\t(invalid data)";
            setColours(i%2? 0x282828 : 0x202020, 
                (i+1)*(0xFFFFFF/ws.ws_row));
        }

        if(option.y == i && option.x == 0) setColours(0, 0xFFFFFF);
        moveCursor(Pos(ws.ws_col*4/8, 8+i));
        std::cout<<tasks->peek(i).priority;
        setColours(i%2? 0x282828 : 0x202020, 
            (i+1)*(0xFFFFFF/ws.ws_row));

        if(option.y == i && option.x == 1) setColours(0, 0xFFFFFF); 
        moveCursor(Pos(ws.ws_col*5/8, 8+i));
        std::cout<<tasks->peek(i).p;
        setColours(i%2? 0x282828 : 0x202020, 
            (i+1)*(0xFFFFFF/ws.ws_row));

        if(option.y == i && option.x == 2) setColours(0, 0xFFFFFF); 
        moveCursor(Pos(ws.ws_col*6/8, 8+i));
        std::cout<<tasks->peek(i).t;
        setColours(i%2? 0x282828 : 0x202020, 
            (i+1)*(0xFFFFFF/ws.ws_row));

        if(option.y == i && option.x == 3) setColours(0, 0xFFFFFF); 
        moveCursor(Pos(ws.ws_col*7/8, 8+i));
        std::cout<<tasks->peek(i).d;
    }
}
