#ifndef TIMER_H
#define TIMER_H

void startTimer();
void stopTimer();
bool intervalHasPassed(unsigned long interval);
bool timerIsRunning();

#endif