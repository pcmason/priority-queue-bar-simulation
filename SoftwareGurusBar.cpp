#include <iostream>
//#include "minPQ.h"
#include <vector>
#include "event.h"

using namespace std;

class RandomInteger{
public:
    unsigned int operator () (unsigned int);
}randomizer;

unsigned int RandomInteger::operator () (unsigned int max){
    //rand return random RandomInteger
    //convert to unsigned to make postive
    //take remainder to put in range
    unsigned int rval=rand();
    return rval % max;
}

unsigned int randBetween(int low, int high){
    return low + randomizer(high-low);
}



class SoftwareGurusBar{
public:
    // try with varying number of chairs to figure out max profit
    SoftwareGurusBar() : freeChairs(50), profit(0.0) {}
    bool canSeat(unsigned int numberOfPeople);
    void order(unsigned int beerType);
    void leave(unsigned int numberOfPeople);
    
    unsigned int freeChairs;
    double profit;
};

SoftwareGurusBar theBar;
SimulationFramework theSimulation;

class ArriveEvent: public Event{
public:
    ArriveEvent(unsigned int t, unsigned int gsize) : Event(t), groupSize(gsize) {}
    virtual void processEvent();
private:
    unsigned int groupSize;
};

class OrderEvent : public Event{
public:
    OrderEvent(unsigned int t, unsigned int gsize): Event(t), groupSize(gsize){}
    virtual void processEvent();
private:
    unsigned int groupSize;
};

class LeaveEvent :public Event{
public: 
    LeaveEvent(unsigned int t, unsigned int gsize) : Event(t), groupSize(gsize) {}
    virtual void processEvent();
private:
    unsigned int groupSize;
};

void ArriveEvent::processEvent(){
    if(theBar.canSeat(groupSize)){
        // place an order within 2 and 10 minutes
        theSimulation.scheduleEvent(new OrderEvent(theSimulation.currentTime + randBetween(2,10),groupSize));
    }
}

void OrderEvent::processEvent(){
    // each member of a group orders one of three beers
    vector<unsigned int> a = {15,25,60};
    for( unsigned int i =0;i<groupSize; i++){
        theBar.order(theSimulation.weightedProbability(a));
    }
    unsigned int t = theSimulation.currentTime + randBetween(15,35);
    theSimulation.scheduleEvent(new LeaveEvent(t, groupSize));
}

void LeaveEvent::processEvent(){
    theBar.leave(groupSize);
}

bool SoftwareGurusBar::canSeat(unsigned int numberOfPeople){
    //if enough room customers then are seated
    cout<< "Time: " <<theSimulation.currentTime << endl;
    cout<< "Group of " <<numberOfPeople << " customers arrive.\n";
    if(numberOfPeople<freeChairs){
        cout<< "Group is seated.\n";
        freeChairs-=numberOfPeople;
        return true;
    }
    else{
        cout<< "No room, group leaves.\n";
        return false;
    }
}

void SoftwareGurusBar::order(unsigned int beerType){
    cout<< "Time: " << theSimulation.currentTime << endl;
    int beer = randBetween(1,3);
    if(beer ==1){
        profit+=2;
    }
    else if(beer==2){
        profit+=3;
    }
    else if(beer==3){
        profit+=4;
    }
}

void SoftwareGurusBar::leave(unsigned int numberOfPeople){
    cout<< "Time : " << theSimulation.currentTime << endl;
    cout<< "Group of " << numberOfPeople << " leaves" << endl;
    freeChairs-=numberOfPeople;
}

int main(){
    //load priority queue with initial arrive events to load the SimulationFramework
    unsigned int t=0;
    while(t<240){
        //new group every two to five minutes
        t+=randBetween(2,5);
        //groupsize ranges from 1 to 5
        theSimulation.scheduleEvent(new ArriveEvent(t,randBetween(1,5)));
    }
    //then run simulation and print profits
    theSimulation.run();
    cout<< "Total profits: " <<theBar.profit << endl;
    
    return 0;
}


        
        

