#ifndef TASK
#define TASK

#include "libs.hpp"


struct Task{
    int p, d, t;
    int priority;

    Task(){};
    Task(int p, int d, int t, int priority = 64):p(p), d(d), t(t), priority(priority){}
    Task operator=(Task &other){
        if(this != &other){
            p = other.p;
            d = other.d;
            t = other.t;
            priority = other.priority;
        }
        return *this;
    }
};


#endif // !TASK
