#include "good.h"

Good::Good()
{
}

void Good::initial(GoodItem initItem)
{
    goodItem = initItem;

    ERRORCHECK(pthread_mutex_init(&goodMtx, NULL))
}

int Good::sellGood(int decNum)
{   
    assert(decNum>0);

    int ret = 0;

    ERRORCHECK(pthread_mutex_lock(&goodMtx))

    if((goodItem.num>=decNum))
    {
        goodItem.num -= decNum;
        ret = 1;
        printf("%s:%d\n", goodItem.name.c_str(), goodItem.num);
    }
    else
    {
        ret = 0;
        printf("Don't have enough %s\n", goodItem.name.c_str());
    }

    ERRORCHECK(pthread_mutex_unlock(&goodMtx))

    return ret;
}

int Good::getGoodNum()
{
    return goodItem.num;
}

string Good::getGoodName()
{
    return goodItem.name;
}
