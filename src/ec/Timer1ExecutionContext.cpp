
#include <ec/ExecutionContext.h>

void Timer1EC_init(double rate) __attribute__((weak));
void Timer1EC_init(double rate)
{
  EC_fault();
}