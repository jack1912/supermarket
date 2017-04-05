#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common.h"

class Customer
{
private :
    pthread_t customerItm;
    CustomerPara customerPara;
    int waitTime;
    int cnt;
    int flag;

public :
    Customer();
    static void* ThreadFun(void* threadPara);
    void initial(int waitTime);
    void hasGood(SuperMarket* superMarketPts);
    void run(SuperMarket* superMarketPts);
    int getCnt();
    pthread_t* getThrPts();
    void clearFlag();
};

#endif // CUSTOMER_H
