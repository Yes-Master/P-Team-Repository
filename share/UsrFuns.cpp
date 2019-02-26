//Clamp
    //PosControl
        void ClampPosControl(){
            if(Controller1.ButtonL1.pressing() && !L1Pressed){
                L1Pressed=true;
                ClampPosChanger();//change pos setting
            }
            else if(!Controller1.ButtonL1.pressing() && L1Pressed)  L1Pressed=false;
        }
    //FlowControl
        void ClampCapsControl(){
            ClampPosControl();
        }
        void ClampExecute(){
            Clamp.SST(Clamp.GetTargetSetting(),Clamp.GetVSetting());
        }
//Lift
    //ConstControl
        void LiftParkControl(){
            if(Controller1.ButtonDown.pressing() && !DPressed){
                DPressed=true;
                if(Parked){
                    Parked=false;
					DriveMotorInverted=false;					 
                    Clamp.SetVSetting(50);
                    Clamp.SetTargetSetting(ClampPosUp);//set clamp up
                    Lift.SetTargetSetting(LiftPosDown);//set lift down
                    Lift.SetVSetting(100);
                    Lift.SendControl=SendControl::SST;//enable move
                }
                else{
                    Parked=true;
					DriveMotorInverted=false;						
                    Lift.SetTargetSetting(LiftPosUp);//set lift up
                    Lift.SetVSetting(75);
                    Lift.SendControl=SendControl::SST;//enable move
                    Clamp.SetVSetting(50);
                    Clamp.SetTargetSetting(ClampPosIn);//set clamp in
                    IntakeAutoEnabled=false;//stop auto intake
					
                }
            }
            else if(!Controller1.ButtonDown.pressing() && DPressed) DPressed=false;
        }
    //FlagControl
    //CapControl
        void LiftCapsManControl(){
            if(Controller1.ButtonR2.pressing()){
                Lift.SetVSetting(-100);
                Lift.SendControl=SendControl::SMS;
            }
            else if(Controller1.ButtonR1.pressing()){
                Lift.SetVSetting(100);
                Lift.SendControl=SendControl::SMS;
            }
            else if(Lift.SendControl==SendControl::SMS){
                Lift.SetVSetting(0);//set motor to stop
                Lift.SendControl=SendControl::NONE;
            }
        }
        void LiftCapsPosControl(){
            if(Controller1.ButtonLeft.pressing() && !LPressed){
                LPressed=true;
                LiftPosChanger();
                Lift.SendControl=SendControl::SST;//enable SST control
            }
            else if (!Controller1.ButtonLeft.pressing() && LPressed)     LPressed=false;
        }
        //FlowControl
            void LiftCapsControl(){
                LiftCapsManControl();//override
                LiftCapsPosControl();
                
                // if(Lift.Rotation()>200) DriveSlowEnabled=true;
                // else                    DriveSlowEnabled=false;
            }
    //FlowControl
        void LiftExecute(){
            if(Lift.SendControl==SendControl::SST)	Lift.SST(Lift.GetTargetSetting(),Lift.GetVSetting());
            else									Lift.SMS(Lift.GetVSetting());
        }

//Puncher
    void PuncherChargeControl(){
        if(Controller1.ButtonR1.pressing() && !R1Pressed){
            R1Pressed=true;
            IntakeAutoEnabled=true;
            DriveSetStop(vex::brakeType::hold);//set drive to 
            DoubleShotTaskEnabled=true;
            vex::task PuncherDoubleShotTask(DoubleShotTaskFun);
        }
        else if(!Controller1.ButtonR1.pressing() && R1Pressed){//de init/tog
            R1Pressed=false;//deTog
            DoubleShotTaskEnabled=false;//disable task
            DriveSetStop(vex::brakeType::coast);//set drive to hold
            Lift.SetTargetSetting(LiftPosDown);//return the lift to the ground
            Clamp.SetTargetSetting(ClampPosUp);//dont brake the clamp

        }  
    }
    //FlowControl
        void PuncherFlagControl(){
            PuncherChargeControl();
        }
        void PuncherExecute(){//exicutes movement; not in task to control flow order in usr; move into class
            PunCon.SpinTo(PunCon.TargetSetting,1,1,0,100,5);//spin motor to puncherPosSetting && set motor to spin
        }
//Intake
    //ConstControl
        //ManualIntake
            void IntakeManualControl(){//Controller Manual OverRide
                if(Controller1.ButtonX.pressing()){//Pressing
                    IntakeManualControlEnabled=true;//halt auto intake function from running
                    Intake.SetVSetting(IntakePctIn);//set to IntakeIn
                    if(!XPressed){//Tog
                        IntakeAutoEnabled=false;//intake balls auto after manual overide
                    }
                }
                else if(Controller1.ButtonY.pressing()){//btnR1->btnY;
                    IntakeManualControlEnabled=true;   
                    Intake.SetVSetting(IntakePctOut);//set to intakeout
                    if(!YPressed){//Tog
                        IntakeAutoEnabled=false;
                    }
                }
                else if(IntakeManualControlEnabled){//first loop not manualy controlled
                    IntakeManualControlEnabled=false;
                    if(!IntakeAutoEnabled)  Intake.SetVSetting(IntakePctStop);//if not auto controlled stop intakeing
                }

                if(!Controller1.ButtonX.pressing() && XPressed)  XPressed=false;//detog
                if(!Controller1.ButtonY.pressing() && YPressed)  YPressed=false;//detog
            }
        //AutoControl
            void IntakeAutoControl(){//Controller Input To control Autonomous Logic Control
                if(Controller1.ButtonA.pressing() && !APressed){
                    APressed=true;
                    if(ControlMode==ControlModes::Flag)     IntakeAutoEnabled=!IntakeAutoEnabled;//toggle intake auto enable
                    else{
                        FlagInit();
                        IntakeAutoEnabled=true;
                    }
                }
                else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;

                IntakeAuto();
            }
        //FLowControl
            void IntakeControl(){
                IntakeManualControl();
                if(!IntakeManualControlEnabled) IntakeAutoControl();
            }
            void IntakeExecute(){
                Intake.SMS(Intake.GetVSetting());
            }
    //FlagControl
        //tog
            void InatakeFlagTogOutControl(){
                if(Controller1.ButtonR2.pressing()){
                    if(!R2Pressed)  R2Pressed=true;//Tog
                    if(IntakeFlagTimer>10){
                        IntakeManualControlEnabled=true;
                        Intake.SetVSetting(IntakePctOut);
                    }

                    IntakeFlagTimer++;//count loops
                }
                else if(!Controller1.ButtonR2.pressing() && R2Pressed){
                    R2Pressed=false;//deTog
                    
                    IntakeManualControlEnabled=false;
                    if(IntakeFlagTimer<=10) IntakeAutoEnabled=!IntakeAutoEnabled;  
                    else                    IntakeAutoEnabled=false;
                    Controller1.Screen.clearLine();
                    Controller1.Screen.print(IntakeFlagTimer);
                    IntakeFlagTimer=0;//reset timer
                }
            }
        //FlowControl
            void IntakeFlagControl(){
                IntakeManualControl();
                if(!IntakeManualControlEnabled) InatakeFlagTogOutControl();
                if(!IntakeManualControlEnabled) IntakeAutoControl();
            }
    //CapControl
//Drive
    //ManualControl
        void DriveManualControl(){
            LHJoy=Controller1.Axis4.value();
            LVJoy=Controller1.Axis3.value();
            RVJoy=Controller1.Axis2.value();
            RHJoy=Controller1.Axis1.value();

            if(std::abs(LVJoy)<5)    LVJoy=0;
            if(std::abs(RVJoy)<5)    RVJoy=0;
            if(std::abs(LHJoy)<5)    LHJoy=0;
            if(std::abs(RHJoy)<5)    RHJoy=0;

            // if(DriveSlowEnabled){
            //     LVJoy/=2;
            //     RVJoy/=2;
            //     LHJoy/=2;
            //     RHJoy/=2;
            // }

            if(LVJoy!=0 || RVJoy!=0 || LHJoy!=0 || RHJoy!=0){
                DriveManualControlEnabled=true;
                DriveTankSMS(
                    DriveMotorInverted ?  -RVJoy : LVJoy,
                    DriveMotorInverted ?  -LVJoy : RVJoy,
                    DriveMotorInverted ?  -RHJoy : LHJoy,
                    DriveMotorInverted ?  -LHJoy : RHJoy);
            }
            else{
                if(DriveManualControlEnabled)  DriveTankSMS(0,0,0,0);//Last loop before disableing; used to release drivemanualcontrol
                    DriveManualControlEnabled=false;
            }
        }
    //Togs
        void DriveHoldTog(){
            if(Controller1.ButtonL2.pressing() && !L2Pressed){
                L2Pressed=true;
                if(DriveGetStop()==vex::brakeType::coast)       DriveSetStop(vex::brakeType::hold);
                else if(DriveGetStop()==vex::brakeType::hold)   DriveSetStop(vex::brakeType::coast);
                DriveSMS(1,1,1,1);//flash the motors to update the stop
                DriveSMS(0,0,0,0);//flass the motors to update the stop
            }
            else if(!Controller1.ButtonL2.pressing() && L2Pressed)   L2Pressed=false;
        }
        // void DriveDirTog(){
        //     if(Controller1.ButtonL1.pressing() && !L1Pressed){
        //         L1Pressed=true;
        //         DriveMotorInverted=!DriveMotorInverted;
        //         if(DriveMotorInverted==true)    IntakeAutoEnabled=false;//disable intake auto when switching to cap drive dir
        //     }
        //     else if(!Controller1.ButtonL1.pressing() && L1Pressed)  L1Pressed=false;
        // }
    //FlowControl
        void DriveControl(){
            DriveManualControl();
            DriveHoldTog();
        }
//FlowControl

    void ConModeTog(){//flag || caps
        if(Controller1.ButtonUp.pressing() && !ConModeTogBtnPressed){
            ConModeTogBtnPressed=true;
            if(ControlMode==ControlModes::Flag){
                Controller1.Screen.print("Caps");
                ConTogsReset();//reset all controller btn toggles
                CapsInit();
            }
            else if(ControlMode==ControlModes::Caps){
                Controller1.Screen.print("Flag");
                ConTogsReset();//reset all controller btn toggles
                FlagInit();
            }
        }
        else if(!Controller1.ButtonUp.pressing() && ConModeTogBtnPressed)  ConModeTogBtnPressed=false;
    }
    void ConModeL1Tog(){
        if(Controller1.ButtonL1.pressing() /*&& !ConModeTogBtnL1Pressed*/){//tog bool not needed as controlmode acts as tog
            // ConModeTogBtnL1Pressed=true;
            CapsInit();
            L1Pressed=true;
        }
        // else if(!Controller1.ButtonL1.pressing() && ConModeTogBtnL1Pressed) ConModeTogBtnL1Pressed=false;

    }