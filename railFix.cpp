#include "railFix.h"

railFix::railFix() : Task(5, true), necessaryTool("wrench"){};

railFix::railFix(int timeTaken, string necessaryTool) : Task(timeTaken, true), necessaryTool(necessaryTool){};
        
void railFix::fixRail(){
    //Get player input by showing them a nut, a screw, or a nail, 
    // and stating "This nut/nail/screw came loose." then asking which tool
    //they want to use paired with three clickable sprites, A HAMMER, a screwdriver, and a monkey wrench.""
    string playerToolSelection;
    if(playerToolSelection == necessaryTool){
        //pause player motion for 7 seconds and fill the progress bar
        //success, task completed
    }
    else{
        // fail (game fails, show game over screen with the text "Roggert failed to repair
        // the hand rail and thereby commited a SOSHA violation"
    }

}