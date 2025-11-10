

#include <ec/ExecutionContext.h>

void MainLoopEC_init(double rate) __attribute__((weak));
void MainLoopEC_init(double rate)
{
  EC_fault();
}

void MainLoopEC_svc() __attribute__((weak));
void MainLoopEC_svc()
{
  EC_fault();
}
