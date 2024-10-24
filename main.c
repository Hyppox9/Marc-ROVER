#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

int main() {

    while(0 < 10){
        startTimer();
        displayTime();
    }
    stopTimer();


    return 0;
}