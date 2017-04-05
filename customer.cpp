#include "customer.h"
#include "supermarket.h"

Customer::Customer()
{
    waitTime = 0;
    cnt = 0;
    flag = 1;
}

void* Customer::ThreadFun(void* threadPara)
{
    Customer* customerPts = ((CustomerPara*)threadPara)->customerPts;
    SuperMarket* superMarketPts = ((CustomerPara*)threadPara)->superMarketPts;

    customerPts->hasGood(superMarketPts);

    return (void*)NULL;
}

void Customer::initial(int waitTime)
{
    this->waitTime = waitTime;
}

void Customer::hasGood(SuperMarket* superMarketPts)
{
    int goodID = 0;
    int goodNum = superMarketPts->getGoodNum();

    while(flag)
    {
        goodID = random() % goodNum;

        superMarketPts->pushQueue(goodID);

        waitTime = random() % 3 + 1;
        cnt += 1;

        sleep(waitTime);
    }

    return ;
}

void Customer::run(SuperMarket* superMarketPts)
{
    customerPara.superMarketPts = superMarketPts;
    customerPara.customerPts = this;

    ERRORCHECK(pthread_create(&customerItm, NULL, Customer::ThreadFun, &customerPara))

    return ;
}

int Customer::getCnt()
{
    return cnt;
}

pthread_t* Customer::getThrPts()
{
    return &customerItm;
}

void Customer::clearFlag()
{
    flag = 0;

    return ;
}




