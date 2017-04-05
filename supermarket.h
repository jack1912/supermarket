#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "common.h"

class SuperMarket
{
private :
    queue<int> queueItm;
    pthread_mutex_t queueMtx;

    int goodNum;
    Good* goodPts;

    int cashierNum;
    CashierPara* cashierParaPts;
    pthread_t* cashierItmPts;

public :
    SuperMarket();
    ~SuperMarket();
    void initial(Good* goodPts, Cashier* cashierPts, int goodNum, int cashierNum);
    void run();
    void pushQueue(int itm);
    int popQueue();
    int getQueueLen();
    int getGoodNum();
    Good* getGood(int goodID);
    pthread_t* getThrPts();
    int getThrNum();
};

#endif // SUPERMARKET_H
