#include "courseCorrection.h"
#include <string>

courseCorrection::courseCorrection() : Task(4, false), correctionDirection("up"){};
courseCorrection::courseCorrection(int timeTaken, std::string correctionDirection) : Task(timeTaken, false), correctionDirection(correctionDirection) {};

void correctCourse(){

}

std::string courseCorrection::get_correctionDirection(){
    return(correctionDirection);
};

void courseCorrection::set_correctionDirection(std::string newCorrectionDirection){
    this -> correctionDirection = newCorrectionDirection;
}