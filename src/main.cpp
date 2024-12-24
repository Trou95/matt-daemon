#include "include/utility/utility.h"
#include "include/TintinReporter.h"

#include <iostream>

int main()
{
    TintinReporter reporter("log2.txt");
    reporter.LogInfo("Hello, World!");
    return 0;
}