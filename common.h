#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <queue>
#include <pthread.h>
#include <assert.h>
#include <string.h>

using namespace std;

typedef struct _GoodItem
{
    string name;
    int num;
}
GoodItem;

typedef struct _CashierInfo
{
    string name;
    int waitTime;
}
CashierInfo;

class SuperMarket;
class Cashier;
class Customer;
class Good;

typedef struct _ThreadPara
{
    SuperMarket* superMarketPts;
    Cashier* customerPts;
}
CashierPara;


typedef struct _CustomerPara
{
    SuperMarket* superMarketPts;
    Customer* customerPts;
}
CustomerPara;

#define ERRORCHECK(fun) if(0!=(fun)) { printf("error : %s, %d\n", __FILE__, __LINE__); exit(-1); }

#endif // COMMON_H
