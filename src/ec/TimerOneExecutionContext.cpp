
#include <ec/ExecutionContext.h>

void TimerOneEC_init(double rate) __attribute__((weak));
void TimerOneEC_init(double rate)
{
    EC_fault();
}