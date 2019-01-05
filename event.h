#ifndef EVENT_H
#define EVENT_H
//#include "minPQ.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Event{
public:
    Event(unsigned int t) {time=t;}
    virtual void processEvent() {}
    unsigned int time;
};

class eventComparison{
public:
    bool operator () (Event * left, Event * right){return left->time > right->time;}
};

class SimulationFramework{
public:
    SimulationFramework() : eventQueue(), currentTime(0) {}
    void scheduleEvent(Event* newEvent) {eventQueue.push(newEvent); }
    void run();
    unsigned int weightedProbability(vector<unsigned int> a);
    unsigned int currentTime;
protected:
    priority_queue<Event *, vector<Event *>,eventComparison> eventQueue;
};

void SimulationFramework::run() {
    //execute events until queue is empty
    while(! eventQueue.empty() ) {
        //copy and remove min from queue
        Event *nextEvent= eventQueue.top();
        eventQueue.pop();
        //update currentTime
        currentTime=nextEvent->time;
        //process next event
        nextEvent->processEvent();
        //cleanup next event object
        delete nextEvent;
    }
}

unsigned int SimulationFramework::weightedProbability(vector<unsigned int> a){
    unsigned int max=0;
    unsigned int random = rand() % 100;
    for(unsigned int i = 0; i<a.size(); i++){
        max += a[i];
    }
    if (random > 0 && random < a[0]){
        return 0;
    }
    else if ( random > a[0] && random < a[1]){
        return 1;
    }
    else {
        return 2;
    }
}

#endif

