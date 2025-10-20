#include "Task.h"    

Task::Task() : timeTaken(5), toolsNeeded(false){}
Task::Task(int timeTaken, bool toolsNeeded) : timeTaken(timeTaken), toolsNeeded(toolsNeeded){}
 
int Task::get_timeTaken(){
    return(timeTaken);
};

bool Task::get_toolsNeeded(){
    return(toolsNeeded);
}