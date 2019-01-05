/*Need to do

*/
/*Change Log
Formated file and added more bools
*/
//Basic Prints
/*void BrainPrint(std::string Str,bool render=true,std::string End="",bool clearLine=true,bool newLine=false){
    if(newLine)     Brain.Screen.newLine();
    if(clearLine)   Brain.Screen.clearLine();
    Brain.Screen.print();
    if(End!="")     Brain.Screen.print(int(End));
    if(render)      Brain.Screen.render();
}*/
//Controller Print Functions
void ControllerScreenPrintDriveDir(){
        if(DriveMotorInverted!=DriveMotorInvertedWas){//only change if required
            Controller1.Screen.clearLine();
            if(DriveMotorInverted) Controller1.Screen.print("Fliper");
            else                   Controller1.Screen.print("Baller");
        }
        DriveMotorInvertedWas=DriveMotorInverted;
}
void ControllerScreenPrintAutonos(bool UpdateVars=true){
    if(UpdateVars)  AutonSelFun();
    if(FeildPos!=FeildPosControllerScreenPrintAutonosLast || AutoProg!=AutoProgControllerScreenPrintAutonosLast){//if there is a change requireing to reprint
        Controller1.Screen.clearLine();
        if(FeildPos==StartPos::BackRed){                        //red back
            if(AutoProg==ProgPot::Pink)         Controller1.Screen.print("Red  Back  - Skills");
            else if(AutoProg==ProgPot::Green)   Controller1.Screen.print("Red  Back  - Normal");
            else if(AutoProg==ProgPot::Yellow)  Controller1.Screen.print("Red  Back  - Sniper");
        }
        else if(AutSel1.value(vex::analogUnits::pct)>50){       //red front
            if(AutoProg==ProgPot::Pink)         Controller1.Screen.print("Red  Front - Skills");
            else if(AutoProg==ProgPot::Green)   Controller1.Screen.print("Red  Front - Normal");
            else if(AutoProg==ProgPot::Yellow)  Controller1.Screen.print("Red  Front - Sniper");
        }
        else if(AutSel1.value(vex::analogUnits::pct)>17){       //blue front
            if(AutoProg==ProgPot::Pink)         Controller1.Screen.print("Blue Front - Testin");
            else if(AutoProg==ProgPot::Green)   Controller1.Screen.print("Blue Front - Normal");
            else if(AutoProg==ProgPot::Yellow)  Controller1.Screen.print("Blue Front - Sniper");
        }
        else{                                                   //blue back
            if(AutoProg==ProgPot::Pink)         Controller1.Screen.print("Blue  Back - Testin");
            else if(AutoProg==ProgPot::Green)   Controller1.Screen.print("Blue  Back - Normal");
            else if(AutoProg==ProgPot::Yellow)  Controller1.Screen.print("Blue  Back - Sniper");
        }
    }
    FeildPosControllerScreenPrintAutonosLast=FeildPos;
    AutoProgControllerScreenPrintAutonosLast=AutoProg;
}
//Brain Print Functions
void BrainScreenSetColor(bool render=false,bool UpdateVars=true){//set the background color
    if(UpdateVars)  AutonSelFun();
    if(FeildPos!=FeildPosBrainScreenSetColorLast){//only clear screen if needed
        if(AutSel1.value(vex::analogUnits::pct)>50)//if red selected
            Brain.Screen.clearScreen(vex::color::red);
        else//if blue selected
            Brain.Screen.clearScreen(vex::color::blue);
        if(render)  Brain.Screen.render();
    }
    FeildPosBrainScreenSetColorLast = FeildPos;//update last val
}
void BrainScreenFlash(){//flash colors on the brain screen
    for(int i=0; i<10; i++){
        Brain.Screen.clearScreen(vex::color::orange);
        vex::task::sleep(100);
        Brain.Screen.clearScreen(vex::color::purple);
    }
    BrainScreenSetColor();
}
void BrainScreenPrintAutonos(bool render=false,bool UpdateVars=true){//print auton selection
    if(UpdateVars)  AutonSelFun();
    Brain.Screen.clearLine();
    if(FeildPos==StartPos::BackRed){            //red back
    Brain.Screen.print("Back  Red ");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Skills");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else if(AutSel1.value(vex::analogUnits::pct)>50){       //red front
    Brain.Screen.print("Front Red ");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Skills");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else if(AutSel1.value(vex::analogUnits::pct)>17){       //blue front
    Brain.Screen.print("Front Blue");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Testin");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else{                                                   //blue back
    Brain.Screen.print("Back  Blue");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Testin");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    if(render)  Brain.Screen.render();
}
void BrainScreenPrintSensorAutoFeed(){//print the sensor values for the auto feed on the brain screen
    Brain.Screen.print(PuncSen.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen1.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen2.value(vex::analogUnits::pct));
}
void BrainScreenPrintPuncher(){
    Brain.Screen.print(PuncherSpinToControlRunEnabled);
    Brain.Screen.print(" , ");
    Brain.Screen.print(PuncherSpinToControlEnabled);
    Brain.Screen.print(" , ");
    Brain.Screen.print(PuncherPctSetting);
 
}

void BrainScreenPrintStart(){//functions that run during the preauton
    BrainScreenSetColor();
    BrainScreenPrintAutonos();
}
//Start Prints
int ControllerScreenStartFun(){
    ControllerScreenStartFunEnabled=true;
    while(ControllerScreenStartFunEnabled){
        ControllerScreenPrintAutonos();
        EndTimeSlice(25);
    }
    return 1;
}
int BrainScreenStartFun(){
    BrainScreenStartFunEnabled=true;
    while(BrainScreenStartFunEnabled){
        BrainScreenPrintStart();
        Brain.Screen.render();
        EndTimeSlice(25);
    }
    return 1;
}
//Match Prints
int ControllerScreenUsrFun(){
    ControllerScreenUsrFunEnabled=true;
    while(ControllerScreenUsrFunEnabled){
        ControllerScreenPrintDriveDir();
        vex::task::sleep(25);
    }
    return 1;
}
int BrainScreenUsrFun(){
    BrainScreenUsrFunEnabled=true;
    while(BrainScreenUsrFunEnabled){
        // BrainScreenSetColor();//clears screen
        // BrainScreenPrintAutonos();
        //BallFeedVars();
        Brain.Screen.clearScreen();
        BrainScreenPrintPuncher();
        Brain.Screen.render();
        vex::task::sleep(25);
    }
    return 1;
}