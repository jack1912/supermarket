#include "common.h"
#include "customer.h"
#include "supermarket.h"
#include "cashier.h"
#include "good.h"

GoodItem goodTable[3] =
{
    {"Apple", 15},
    {"Macbook", 15},
    {"Cookie", 15}
};

CashierInfo cashierTable[3] =
{
    {"lili", 5},
    {"lisa", 5},
    {"mery", 5},
};

int main(int argc, char *argv[])
{
    int* goodTime = NULL;
    int closeTime = 0;
    int waitTime = 0;
    int flag = 0;

    printf("start......\n");

    // create and initial good & cashier
    int itemNum = sizeof(goodTable) / sizeof(GoodItem);
    int cashierNum = sizeof(cashierTable) / sizeof(CashierInfo);

    Good* goodPts = new Good[itemNum];
    for(int i=0; i<itemNum; i++) goodPts[i].initial(goodTable[i]);

    Cashier* cashierPts = new Cashier[cashierNum];
    for(int i=0; i<cashierNum; i++) cashierPts[i].initial(cashierTable[i]);

    // initial and kick off super market
    SuperMarket superMarket;
    superMarket.initial(goodPts, cashierPts, itemNum, cashierNum);
    superMarket.run();

    // initial and kick off customer
    Customer customer;
    customer.initial(1);
    customer.run(&superMarket);

    // watcher
    goodTime = (int*)malloc(itemNum*sizeof(int));
    memset(goodTime, 0, itemNum*sizeof(int));

    while(1)
    {
        flag = 1;

        for(int i=0; i<itemNum; i++)
        {
            if(0==goodPts[i].getGoodNum())
            {
                if(0==goodTime[i]) goodTime[i] = closeTime;
            }
            else
            {
                flag = 0;
            }
        }

        if(1==flag)
        {
            for(int i=0; i<cashierNum; i++)
            {
                cashierPts[i].clearFlag();
            }
            customer.clearFlag();

            for(int i=0; i<itemNum; i++)
            {
                printf("%s平均售出时间 : %d秒\n", goodPts[i].getGoodName().c_str(), goodTime[i]/goodTable[i].num);
            }

            printf("从开始销售到售完总共时间 : %d秒\n", closeTime);


            for(int i=0; i<cashierNum; i++)
            {
                printf("%s接待的顾客数量 : %d个\n", cashierPts[i].getName().c_str(), cashierPts[i].getCnt());
            }

            printf("每个客户平均等待时间 : %d秒\n", waitTime/customer.getCnt());

            int marThrNum = superMarket.getThrNum();
            pthread_t* marThrPts = superMarket.getThrPts();

            for(int i=0; i<marThrNum; i++)
            {
                pthread_join(marThrPts[i], NULL);
            }

            pthread_t* cusThrPts = customer.getThrPts();
            pthread_join(*cusThrPts, NULL);

            delete[] goodPts;
            delete[] cashierPts;
            free(goodTime); goodTime = NULL;

            return 0;
        }

        sleep(1);

        closeTime += 1;
        waitTime += superMarket.getQueueLen();
    }

    return 0;
}




