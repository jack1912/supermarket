#include "cashier.h"
#include "supermarket.h"
#include "good.h"

Cashier::Cashier()
{
    cnt = 0;
    flag = 1;
}

void* Cashier::ThreadFun(void* threadPara)
{
    Cashier* cashierPts = ((CashierPara*)threadPara)->customerPts;
    SuperMarket* superMarketPts = ((CashierPara*)threadPara)->superMarketPts;

    cashierPts->hasCustomer(superMarketPts);

    return (void*)NULL;
}

void Cashier::initial(CashierInfo initInfo)
{
    cashierInfo = initInfo;
}

void Cashier::hasCustomer(SuperMarket* superMarketPts)
{
    int goodID = 0;
    Good* goodPts = NULL;

    while(flag)
    {
        goodID = superMarketPts->popQueue();
        goodPts = superMarketPts->getGood(goodID);

        if(-1!=goodID)
        {
            goodPts->sellGood(1);
            cnt += 1;
        }

        cashierInfo.waitTime = random() % 6 + 5;

        sleep(cashierInfo.waitTime);
    }

    return ;
}

int Cashier::getCnt()
{
    return cnt;
}

string Cashier::getName()
{
    return cashierInfo.name;
}

void Cashier::clearFlag()
{
    flag = 0;

    return ;
}



