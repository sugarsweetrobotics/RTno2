/*******************************************
 * Timer2ExecutionContext.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include "ecs/ExecutionContext.h"

void Timer2EC_init(double microsecond);
void Timer2EC_start();
void Timer2EC_suspend();
void Timer2EC_resume();
