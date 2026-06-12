#ifndef TASK
#define TASK

#include "libs.hpp"


struct Task{
    int id;
    int p, d, t;
    int priority;
    int offset;
    int time_started;
    int left;

    Task(){};
    Task(int p, int t, int d, int id, int priority = 64, int offset = 0, int time_started = -1):p(p), d(d), t(t), id(id), priority(priority), offset(offset), time_started(time_started), left(t){}
    Task operator=(const Task &other){
        if(this != &other){
            p = other.p;
            d = other.d;
            t = other.t;
            id = other.id;
            priority = other.priority;
            offset = other.offset;
            time_started = other.time_started;
            left = other.left;
        }
        return *this;
    }
};


#endif // !TASK
