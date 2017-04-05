#include "supermarket.h"
#include "cashier.h"
#include "good.h"

SuperMarket::SuperMarket()
{
    goodNum = 0;
    goodPts = NULL;

    cashierNum = 0;
    cashierParaPts = NULL;
    cashierItmPts = NULL;
}

SuperMarket::~SuperMarket()
{
    if(NULL!=cashierParaPts) { free(cashierParaPts); cashierParaPts = NULL; }
    if(NULL!=cashierItmPts) { free(cashierItmPts); cashierItmPts = NULL; }
}

void SuperMarket::initial(Good* goodPts, Cashier* cashierPts, int goodNum, int cashierNum)
{
    ERRORCHECK(pthread_mutex_init(&queueMtx, NULL))

    this->goodNum = goodNum;
    this->goodPts = goodPts;

    this->cashierNum = cashierNum;
    cashierParaPts = (CashierPara*)malloc(cashierNum*sizeof(CashierPara));
    for(int i=0; i<cashierNum; i++)
    {
        cashierParaPts[i].customerPts = &(cashierPts[i]);
        cashierParaPts[i].superMarketPts = this;
    }
    cashierItmPts = (pthread_t*)malloc(cashierNum*sizeof(pthread_t));

    return ;
}

void SuperMarket::run()
{
    for(int i=0; i<cashierNum; i++)
    {
        ERRORCHECK(pthread_create(&(cashierItmPts[i]), NULL, Cashier::ThreadFun, &(cashierParaPts[i])))
    }

    return ;
}

void SuperMarket::pushQueue(int itm)
{
    ERRORCHECK(pthread_mutex_lock(&queueMtx))

    queueItm.push(itm);

    ERRORCHECK(pthread_mutex_unlock(&queueMtx))

    return ;
}

int SuperMarket::popQueue()
{
    int ret = 0;

    ERRORCHECK(pthread_mutex_lock(&queueMtx))

    if(0==queueItm.empty())
    {
        ret = queueItm.front();
        queueItm.pop();
    }
    else
    {
        ret = -1;
    }

    ERRORCHECK(pthread_mutex_unlock(&queueMtx))

    return ret;
}

int SuperMarket::getQueueLen()
{
    return queueItm.size();
}

int SuperMarket::getGoodNum()
{
    return goodNum;
}

Good* SuperMarket::getGood(int goodID)
{
    return &(goodPts[goodID]);
}

pthread_t* SuperMarket::getThrPts()
{
    return cashierItmPts;
}

int SuperMarket::getThrNum()
{
    return cashierNum;
}
