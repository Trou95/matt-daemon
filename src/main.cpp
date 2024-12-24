#include "include/utility/utility.h"
#include "include/logger/logger.h"

#include <iostream>

int main()
{
    Logger logger("log.txt");

    logger.LogInfo("This is an info message");
    return 0;
}