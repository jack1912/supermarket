#ifndef CASHIER_H
#define CASHIER_H

#include "common.h"

class Cashier
{
private :
    CashierInfo cashierInfo;
    int cnt;
    int flag;

public :
    Cashier();
    static void* ThreadFun(void* threadPara);
    void initial(CashierInfo initInfo);
    void hasCustomer(SuperMarket* superMarketPts);
    int getCnt();
    string getName();
    void clearFlag();
};

#endif // CASHIER_H
