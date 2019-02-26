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
    void ControllerScreenPrintDriveDir(){//Mode;bat;IntakeAutoEnabled;Balls;Charged
        if(ControlMode!=ControlModeConPrintWas
        // ||BrainBatWas!=Brain.Battery.capacity()
        || IntakeAutoEnabled!=IntakeAutoEnabledConPrintWas
        // || Balls!=BallsWas
        // || Charged!=ChargedWas
        ){//only change if required
            Controller1.Screen.clearLine();
            //mode
                if(ControlMode==ControlModes::Caps){
                    if(IntakeAutoEnabled)                   Controller1.Screen.print("Caps Auto");
                    else                                    Controller1.Screen.print("Caps !Auto");
                }
                else if(ControlMode==ControlModes::Flag){
                    if(IntakeAutoEnabled)                   Controller1.Screen.print("Flag Auto");
                    else                                    Controller1.Screen.print("Flag !Auto");
                }
            //VarWasUpdate
                ControlModeConPrintWas=ControlMode;
                IntakeAutoEnabledConPrintWas=IntakeAutoEnabled;
        }
    }
    void ControllerScreenPrintAutonos(bool UpdateVars=true){
        if(UpdateVars)  AutonSelFun();
        if(FeildPos!=FeildPosControllerScreenPrintAutonosLast || AutoProg!=AutoProgControllerScreenPrintAutonosLast || AVariant!=AVariantControllerScreenPrintAutonosLast){//if there is a change requireing to reprint
            Controller1.Screen.clearLine();
            if(FeildPos==StartPos::BackRed){                //red back
                if(AutoProg==ProgPot::Pink){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BR-Park");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BR-Park");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BR-Park");
                }
                else if(AutoProg==ProgPot::Green){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BR-FFlag");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BR-FFlag");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BR-FFlag");
                }
                else if(AutoProg==ProgPot::Yellow){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BR-CapP");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BR-CapP");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BR-CapP");
                } 
            }
            else if(FeildPos==StartPos::FrontRed){          //red front
                if(AutoProg==ProgPot::Pink){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FR-Normal");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FR-Normal");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FR-Normal");
                }
                else if(AutoProg==ProgPot::Green){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FR-NorMid Bot");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FR-NorMid Top");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FR-NorMid Bth");
                }
                else if(AutoProg==ProgPot::Yellow){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FR-ZBread");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FR-Skills");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FR-ZBread");
                } 
            }
            else if(FeildPos==StartPos::FrontBlue){         //blue front
                if(AutoProg==ProgPot::Pink){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FB-Normal");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FB-Normal");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FB-Normal");
                }
                else if(AutoProg==ProgPot::Green){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FB-NorMid Bot");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FB-NorMid Top");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FB-NorMid Bth");
                }
                else if(AutoProg==ProgPot::Yellow){
                    if(AVariant==Variant::White)            Controller1.Screen.print("FB-Sniper");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("FB-ZBread");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("FB-ZBread");
                } 
            }
            else if(FeildPos==StartPos::BackBlue){      //blue back
                if(AutoProg==ProgPot::Pink){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BB-Park");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BB-Park");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BB-Park");
                }
                else if(AutoProg==ProgPot::Green){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BB-FFlags");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BB-FFlags");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BB-FFlags");
                }
                else if(AutoProg==ProgPot::Yellow){
                    if(AVariant==Variant::White)            Controller1.Screen.print("BB-CapP");
                    else if(AVariant==Variant::Black)       Controller1.Screen.print("BB-CapP");
                    else if(AVariant==Variant::Purple)      Controller1.Screen.print("BB-CapP");
                } 
            }
        }
        FeildPosControllerScreenPrintAutonosLast=FeildPos;
        AutoProgControllerScreenPrintAutonosLast=AutoProg;
        AVariantControllerScreenPrintAutonosLast=AVariant;
    }
//Brain Print Functions
    void BrainScreenSetColor(bool render=false,bool UpdateVars=true){//set the background color
        if(UpdateVars)  AutonSelFun();
        if(FeildPos!=FeildPosBrainScreenSetColorLast){//only clear screen if needed
            if(FeildPos==StartPos::FrontRed || FeildPos==StartPos::BackRed)//if red selected
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
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          Brain.Screen.print("Park");
                else if(AVariant==Variant::Black)     Brain.Screen.print("Park");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("Park");
            }
            else if(AutoProg==ProgPot::Green){
                if(AVariant==Variant::White)          Brain.Screen.print("FFlags");
                else if(AVariant==Variant::Black)     Brain.Screen.print("FFlags");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("FFlags");
            }
                else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          Brain.Screen.print("CapP");
                else if(AVariant==Variant::Black)     Brain.Screen.print("CapP");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("CapP");
            }
        }
        else if(FeildPos==StartPos::FrontRed){      //red front
            Brain.Screen.print("Front Red ");
            Brain.Screen.print("-");
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          Brain.Screen.print("Normal");
                else if(AVariant==Variant::Black)     Brain.Screen.print("Normal");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("Normal");
            }
            else if(AutoProg==ProgPot::Green){
                if(AVariant==Variant::White)          Brain.Screen.print("NorMid Bot");
                else if(AVariant==Variant::Black)     Brain.Screen.print("NorMid Top");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("NorMid Bth");
            }
                else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          Brain.Screen.print("ZBread");
                else if(AVariant==Variant::Black)     Brain.Screen.print("Skills");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("ZBread");
            }
        }
        else if(FeildPos==StartPos::FrontBlue){     //blue front
            Brain.Screen.print("Front Blue");
            Brain.Screen.print("-");
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          Brain.Screen.print("Normal");
                else if(AVariant==Variant::Black)     Brain.Screen.print("Normal");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("Normal");
            }
            else if(AutoProg==ProgPot::Green){
                if(AVariant==Variant::White)          Brain.Screen.print("NorMid Bot");
                else if(AVariant==Variant::Black)     Brain.Screen.print("NorMid Top");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("NorMid Bth");
            }
            else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          Brain.Screen.print("Sniper");
                else if(AVariant==Variant::Black)     Brain.Screen.print("ZBread");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("ZBread");
            }
        }
        else if(FeildPos==StartPos::BackBlue){      //blue back
            Brain.Screen.print("Back  Blue");
            Brain.Screen.print("-");
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          Brain.Screen.print("Park");
                else if(AVariant==Variant::Black)     Brain.Screen.print("Park");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("Park");
            }
            else if(AutoProg==ProgPot::Green){
                if(AVariant==Variant::White)          Brain.Screen.print("FFlags");
                else if(AVariant==Variant::Black)     Brain.Screen.print("FFlags");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("FFlags");
            }
                else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          Brain.Screen.print("CapP");
                else if(AVariant==Variant::Black)     Brain.Screen.print("CapP");
                else if(AVariant==Variant::Purple)    Brain.Screen.print("CapP");
            }
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
    //     Brain.Screen.print(PuncherSpinToControlRunEnabled);
    //     Brain.Screen.print(" , ");
    //     Brain.Screen.print(PuncherSpinToControlEnabled);
    //     Brain.Screen.print(" , ");
    //     Brain.Screen.print(PuncherPctSetting);
    
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