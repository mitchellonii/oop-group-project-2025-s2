#include "cargoFix.h"
#include <string>

cargoFix::cargoFix() : Task(5, false), switchesToFlick(3){}
cargoFix::cargoFix(int timeTaken, int switchesToFlick) : Task(timeTaken, false), switchesToFlick(switchesToFlick){};

void cargoFix::fixCargo(){

};

int cargoFix::get_switchesToFlick{
    return(switchesToFlick);
}

void set_switchesToFlick();