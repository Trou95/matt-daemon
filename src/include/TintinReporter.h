#include "logger/logger.h"

class TintinReporter : public Logger
{
public:
    TintinReporter(const char *log_file) : Logger(log_file) {}
    ~TintinReporter() {}
};
