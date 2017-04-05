#ifndef GOOD_H
#define GOOD_H

#include "common.h"

class Good
{
private :
    GoodItem goodItem;
    pthread_mutex_t goodMtx;

public:
    Good();
    void initial(GoodItem initItem);
    int sellGood(int decNum);
    int getGoodNum();
    string getGoodName();
};

#endif // GOOD_H
