#ifndef BACKGROUNDCOUNTTOTASK_H
#define BACKGROUNDCOUNTTOTASK_H
#include <cstdlib>
#include <iostream>
#include "courseCorrection.h"
#include "railFix.h"

void BackgroundCountdown(bool taskActive){
srand(time(0));
    while(taskActive == false){
        int randomizer = rand() % 3; 
        switch(randomizer)
        {
        case 1:
            int randomtask = rand() % 2;
                switch (randomtask)
                {
                case 0:
                    //courseCorrection task
                    break;
                case 1:
                    //railFix task
                    break;
                }
            taskActive = true;
            break;
        case 2:
            int randomPirate = rand() % 3;
                switch (randomPirate)
                {
                case 0:
                    //green pirates
                    break;
                case 1:
                    //Pink Pirates
                    break;
                case 2:
                    //yellow Pirates
                    break;
                }
            taskActive = true;
            break;
        default:
            return;
        }
    }

}



#endif