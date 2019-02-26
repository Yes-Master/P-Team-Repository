//forward def's
//basic
//vision
    void VisionLedUpdate(){
        if(!PuncBall && !Feed2Ball)      Vis1.setLedColor(100,0,0);
        else if(PuncBall && !Feed2Ball)  Vis1.setLedColor(0,0,100);
        else if(PuncBall && Feed2Ball)   Vis1.setLedColor(0,100,0);
    }
//Controller
    int ComRumer(){
        ComRumerEnabled=true;
        while(ComRumerEnabled){
            if(ComRum && IntakeAutoEnabled && Intake.GetVSetting()==IntakePctStop)  Controller1.rumble(".");
            vex::task::sleep(20);
        }
        return 1;
    }
    int ComRumerFun(){
        Controller1.rumble(".");
        return 1;
    }
    void ConTogsReset(){
        L1Pressed=false;//
        L2Pressed=false;//brake toggle pressed
        R2Pressed=false;//
        R1Pressed=false;//puncher
        XPressed=false;//
        YPressed=false;//
        BPressed=false;//
        APressed=false;//auto intake toggle
        UPressed=false;//Drive Dir toggle pressed
        RPressed=false;//
        DPressed=false;//
        LPressed=false;//
    }
//ModeInit
    //Flag
        void FlagInit(){
            // Controller1.Screen.print("Flag");
            DriveMotorInverted=false;
            Clamp.SendControl=SendControl::SST; Clamp.SetTargetSetting(ClampPosUp,100);
            Lift.SendControl=SendControl::SST;  Lift.SetTargetSetting(LiftPosDown,100);
            ControlMode=ControlModes::Flag;
        }
    //Caps
        void CapsInit(){
            // Controller1.Screen.print("Caps");
            IntakeAutoEnabled=false;//turn off auto intake
            DriveMotorInverted=true;
            Clamp.SendControl=SendControl::SST; Clamp.SetTargetSetting(ClampPosUp,100);
            Lift.SendControl=SendControl::SST;  Lift.SetTargetSetting(LiftPosDown,100);
            ControlMode=ControlModes::Caps;//tog
        }
    //Debug
        void DebugInit(){
            // Controller1.Screen.print("Debug");
            ControlMode=ControlModes::Debug;//tog
        }
//Clamp
    //PosControl
        void ClampPosChanger(){
            if(Clamp.GetTargetSetting()==ClampPosIn){
                Clamp.SetVSetting(50);
                Clamp.SetTargetSetting(ClampPosUp);
            }
            else if(Clamp.GetTargetSetting()==ClampPosUp){
                Clamp.SetVSetting(50);
                Clamp.SetTargetSetting(ClampPosDown);
            }
            else if(Clamp.GetTargetSetting()==ClampPosDown){
                Clamp.SetVSetting(50);
                Clamp.SetTargetSetting(ClampPosUp);
            }
        }
//Lift
    //PosControl
        void LiftPosChanger(){
            if(Clamp.GetTargetSetting()==ClampPosIn){
                Clamp.SetVSetting(50);
                Clamp.SetTargetSetting(ClampPosUp);
            }
            Lift.SetVSetting(100);//set velocity for moves
            if(Lift.SendControl==SendControl::SMS)              Lift.SetTargetSetting(LiftPosUp);//if it was in manual control
            else if(Lift.GetTargetSetting()==LiftPosUp)         Lift.SetTargetSetting(LiftPosDown);
            else if(Lift.GetTargetSetting()==LiftPosDown){
                Lift.SetTargetSetting(LiftPosUp);
                Clamp.SetTargetSetting(ClampPosIn);
            }
            else if(Lift.GetTargetSetting()==LiftPosPunUp)      Lift.SetTargetSetting(LiftPosPunUp);//just in case of overflow
            else if(Lift.GetTargetSetting()==LiftPosPunDown)    Lift.SetTargetSetting(LiftPosPunDown);//just in case of overflow
        }
//Puncher
    //PosControl
        void PuncherPosFun(){
            ComRumerFun();
            if(!PuncherCharged){//Charging
                PunCon.TargetSetting+=PunPosFromReleasedToCharged;
                PunCon.SpinToRunEnabled=true;//enable puncherspinto
                PuncherCharged=true;
            }
            else if(PuncherCharged){//Fireing
                PunCon.TargetSetting+=PunPosFromChargedToReleased;
                PunCon.SpinToRunEnabled=true;//enable puncherspinto
                PuncherCharged=false;
            }
        }
    //Auton
        void PuncherWait(){
            while(PunCon.SpinToControlEnabled){
                EndTimeSlice(5);
            }       
        }
        int PuncherSpinToAutFun(){
            PunCon.SpinToControlEnabled=true;//init
            PunCon.SpinToRunEnabled=true;//enable spin to contorol to run
            while(PunCon.SpinToControlEnabled){//while spining to target
                PunCon.SpinTo(PunCon.TargetSetting,1,1,0,100,5);//spin motor to puncherPosSetting && set motor to spin
                EndTimeSlice(5);
            }
            return 1;
        }
        void PuncherAut(bool Wait=true,int EndWait=0,bool task=true){//Tar is 80 || 280 || 360;Tar PunPosFromChargedToReleased || PunPosFromReleasedToCharged || 360
            PuncherPosFun();
            if(task) vex::task PuncherSpinToAutTask(PuncherSpinToAutFun);
            if(Wait){
                PunCon.SpinToControlEnabled=true;
                PuncherWait();
            }
            EndTimeSlice(EndWait);
        }
//Intake
    //AutoIntake
        void IntakeAutoUpDate(){//UpDate Sensors Code
            //Puncher UpDate
            if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){//if there is pysicaly a ball
                IntakeTimer=0;//reset timer
                PuncBall=PuncBallActual=true;
                ComRum=false;
            }
            else{//if ball not present
                PuncBallActual=false;
                if(PunCon.SpinToRunEnabled)  PuncBall=false;//if the punc in running and there is not a ball physicaly present
                else{//delay for posible ball return
                    if(IntakeTimer>PuncBallTimeWait)   PuncBall=false;
                    else if(IntakeTimer>ComRumTime)    ComRum=true;
                    IntakeTimer=IntakeTimer+1;//add one to timer
                }
                
            }
            //FeedBall UpDate
            if(OverSen.value(vex::analogUnits::pct)<OverBallTal)    OverBall=true;
            else                                                    OverBall=false;

            if(FeedSen1.value(vex::analogUnits::pct)<Feed1BallTal)  Feed1Ball=true;
            else                                                    Feed1Ball=false;

            if(FeedSen2.value(vex::analogUnits::pct)<Feed2BallTal)  Feed2Ball=true;
            else                                                    Feed2Ball=false;
        }
        int IntakeStateUpDate(){//Task to UpDate IntakeAutoUpDate every second in the background
            while(1){
                IntakeAutoUpDate();
                EndTimeSlice(5);
            }
        }
        void IntakeAuto(){//Autonomous Logic Control
            if(IntakeAutoEnabled){
                IntakeAutoEnabledWas=true;

                if(IntakeOverMode){
                    Intake.SetVSetting(-50);
                    if(OverBall){
                        IntakeOverModeTimer=0;
                    }
                    else{
                        if(Feed1Ball || Feed2Ball || IntakeOverModeTimer>100)  IntakeOverMode=false;
                        IntakeOverModeTimer++;
                    }
                }
                else{
                    if(!PuncBall)           Intake.SetVSetting(IntakePctIn);
                    else{//if punball 
                        if(OverBall){
                            IntakeOverMode=true;
                            Intake.SetVSetting(-50);
                        }
                        else{//!overflow
                            if(!Feed2Ball){
                                if(!Feed1Ball)  Intake.SetVSetting(IntakePctIn*3/4);
                                else            Intake.SetVSetting(IntakePctIn/4);
                            }
                            else                Intake.SetVSetting(IntakePctStop);//if punball && !Overball && feed2ball
                        }
                    }
                }                
            }
            else if(IntakeAutoEnabledWas){//first loop disabled
                Intake.SetVSetting(IntakePctStop);
                IntakeAutoEnabledWas=false;
            }
        }
    //auton
        int IntakeAuton(){//handles intake in the backbround
            IntakeAutonEnabled=true;
            IntakeAutoEnabled=true;//for intakeauto void
            while(IntakeAutonEnabled){
                IntakeAutoUpDate();
                IntakeAuto();
                Intake.SMS(Intake.GetVSetting());
                EndTimeSlice(20);
            }
            return 1;
            }
//Drive
    void DriveSMS(int v1,int v2,int v3,int v4){
        FLDrive.SMS(v1);
        FRDrive.SMS(v2);
        BLDrive.SMS(v3);
        BRDrive.SMS(v4);
    }
    void DriveTankSMS(int j1,int j2,int j3=0,int j4=0){//left,right,side1,side2
        int LF=j1;//left
        int RF=j2;//right
        int SD=(j3+j4)/2;//average
        if(std::abs(j3)>std::abs(j4))   SD=j3;
        else                            SD=j4;

        FLDriveVSetting=LF+SD;
        BLDriveVSetting=LF-SD;
        FRDriveVSetting=RF-SD;
        BRDriveVSetting=RF+SD;
        DriveSMS(//left go apart && right go into when going right
            FLDriveVSetting,
            FRDriveVSetting,
            BLDriveVSetting,
            BRDriveVSetting);
    }
    void DriveArcadeSMS(int J1=0,int J2=0,int J3=0){//forward,side,rotation
        int LF=J1+J3;//left
        int RF=J1-J3;//right
        int SD=J2;//side
        FLDriveVSetting=LF+SD;
        BLDriveVSetting=LF-SD;
        FRDriveVSetting=RF-SD;
        BRDriveVSetting=RF+SD;
        DriveSMS(//left go apart && right go into when going right
            FLDriveVSetting,
            FRDriveVSetting,
            BLDriveVSetting,
            BRDriveVSetting);
    }

    void DriveSetStop(vex::brakeType s){
        FLDrive.SetStop(s);
        FRDrive.SetStop(s);
        BLDrive.SetStop(s);
        BRDrive.SetStop(s);
    }
    bool DriveSpinning(){
        if(FLDrive.Spinning())      return true;
        else if(FRDrive.Spinning()) return true;
        else if(BLDrive.Spinning()) return true;
        else if(BRDrive.Spinning()) return true;
        else                        return false;
    }
    bool DriveDeltaGood(int tal=10/360){
        if(std::abs(FLDrive.Rotation()-FLDrive.GetTarget())>tal)        return false;
        else if(std::abs(FRDrive.Rotation()-FRDrive.GetTarget())>tal)   return false;
        else if(std::abs(BLDrive.Rotation()-BLDrive.GetTarget())>tal)   return false;
        else if(std::abs(BRDrive.Rotation()-BRDrive.GetTarget())>tal)   return false;
        else                                                            return true;        
    }
    vex::brakeType DriveGetStop(){
        return FLDrive.GetStop();
    }
    //Auton bad
        int DriveRamping(){//sets drive motors to spin
            Left.Enabled=true;
            while(Left.Enabled){
                Left.Run();
                Right.Run();
                LeftS.Run();
                RightS.Run();
                if(DriveSide){DriveTankSMS(0,0,LeftS.Output(),RightS.Output());}
                else         {DriveTankSMS(Left.Output(),Right.Output(),0,0);}
                vex::task::sleep(4);
            }
            return 1;
        }
        void DR(int L,int R){//update the drive ramping requested values
            Left.Request(L);
            Right.Request(R);
        }
        void DI(int L,int R){//drive instentaniouly
            Left.Instant(L);
            Right.Instant(R);
            DriveTankSMS(Left.Output(),Right.Output(),0,0);
        }
        void DRS(int L,int R){//update the drive ramping requested values
            LeftS.Request(L);
            RightS.Request(R);
        }
        void DIS(int L,int R){//drive instentaniouly
            LeftS.Instant(L);
            RightS.Instant(R);
            DriveTankSMS(0,0,Left.Output(),Right.Output());
        }
        void Drive(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=1){
            DriveSide=false;
            double Dir=SGN(Dis);
            double Rev=std::abs(Dis)/WheelCir;
            int Pct1=0;
            int Pct2=0;
            FLDrive.ResetRotation();
            FRDrive.ResetRotation();
            BLDrive.ResetRotation();
            BRDrive.ResetRotation();

            while(std::abs(FLDrive.Rotation())<std::abs(Rev)){
                double Input1=FLDrive.Rotation();
                double Input2=FRDrive.Rotation();
                if(std::abs(Input1)>std::abs(Input2)){
                    Pct1=Pct-Correction;
                    Pct2=Pct;
                }
                else if(std::abs(Input1)<std::abs(Input2)){
                    Pct1=Pct;
                    Pct2=Pct-Correction;
                }
                else if(std::abs(Input1)==std::abs(Input2)){
                    Pct1=Pct;
                    Pct2=Pct;
                }
                Pct1=Pct1*Dir;
                Pct2=Pct2*Dir;
                DR(Pct1,Pct2);
                EndTimeSlice(4);
            }
            Controller1.Screen.clearLine();
            Controller1.Screen.print("Drived");
            if(EndWait==-1){//                                                          Junction
                //only use if another drive command fallows
            }
            else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
                //QDRS();//quick drive ramp stop
                DR(0,0);
                while(DriveSpinning()){EndTimeSlice(4);}
                EndTimeSlice(EndWait);
            }
            else{//>=0,!=-1; set stop dont wait;                                        Stop
                DR(0,0);
            }
            Controller1.Screen.clearLine();
            Controller1.Screen.print("Drove");

        }
        void DriveRecon(int Pct,int Wait,int EndWait=250){
            DriveSide=false;
            DR(Pct,Pct);
            vex::task::sleep(Wait);
            if(EndWait>0){
                DR(0,0);
                while(DriveSpinning()){EndTimeSlice(4);}
                Controller1.Screen.clearLine();
                Controller1.Screen.print("RECONED");
            }
            else if(EndWait==0){
                Controller1.Screen.clearLine();
                Controller1.Screen.print("RECONED!END");
            }
        }
        void DriveS(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=1){
            DriveSide=true;
            double Dir=SGN(Dis);
            double Rev=std::abs(Dis)/WheelCir;
            int Pct1=0;
            int Pct2=0;
    FLDrive.ResetRotation();
    FRDrive.ResetRotation();
    BLDrive.ResetRotation();
    BRDrive.ResetRotation();
            while(std::abs(FRDrive.Rotation())<std::abs(Rev)){
                double Input1=FRDrive.Rotation();
                double Input2=BRDrive.Rotation();
                if(std::abs(Input1)>std::abs(Input2)){
                    Pct1=Pct-Correction;
                    Pct2=Pct;
                }
                else if(std::abs(Input1)<std::abs(Input2)){
                    Pct1=Pct;
                    Pct2=Pct-Correction;
                }
                else if(std::abs(Input1)==std::abs(Input2)){
                    Pct1=Pct;
                    Pct2=Pct;
                }
                Pct1=Pct1*Dir;
                Pct2=Pct2*Dir;
                DRS(Pct1,Pct2);
                EndTimeSlice(4);
            }
            Controller1.Screen.clearLine();
            Controller1.Screen.print("Drivedside01");
            if(EndWait==-1){//                                                          Junction
                //only use if another drive command fallows
            }
            else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
                //QDRS();//quick drive ramp stop
                DRS(0,0);
                while(DriveSpinning()){EndTimeSlice(4);}
                EndTimeSlice(EndWait);
            }
            else{//>=0,!=-1; set stop dont wait;                                        Stop
                DRS(0,0);
            }
            DriveSide=false;
            // Controller1.Screen.clearLine();
            Controller1.Screen.print("Drove");

        }
        void DriveReconS(int Pct,int Wait,int EndWait=DriveEndWait){
            DriveSide=true;
            DRS(Pct,Pct);
            vex::task::sleep(Wait);
            if(EndWait>0){
                DRS(0,0);
                while(DriveSpinning()){EndTimeSlice(4);}
                Controller1.Screen.clearLine();
                Controller1.Screen.print("RECONED");
            }
            else if(EndWait==0){
                Controller1.Screen.clearLine();
                Controller1.Screen.print("RECONED!END");
            }
            DriveSide=false;
        }
        void TurnEnc(double deg,int v,int endwait){
            DriveSide=false;
            int Dir=SGN(deg);
            int LPct=v*Dir;
            int RPct=v*Dir;
            
            FLDrive.ResetRotation();
            FRDrive.ResetRotation();
            BLDrive.ResetRotation();
            BRDrive.ResetRotation();

            double ZActual=(-FLDrive.Rotation()+FRDrive.Rotation()-BLDrive.Rotation()+BRDrive.Rotation())*(WheelCir/40)*180/M_PI; //what the robots currant z is
            while(std::abs(ZActual)<std::abs(deg)){
                DI(LPct,-RPct);
                vex::task::sleep(4);
                ZActual=(-FLDrive.Rotation()+FRDrive.Rotation()-BLDrive.Rotation()+BRDrive.Rotation())*(WheelCir/40)*180/M_PI; //what the robots currant z is
            }
            DI(0,0);
            Controller1.Screen.clearLine();
            Controller1.Screen.print("Turned_Enc");
            vex::task::sleep(endwait);
        }
//Flow control
    void AllMotorsResetRotation(){
        Clamp.ResetRotation();
        Lift.ResetRotation();
        Puncher.ResetRotation();
        Intake.ResetRotation();
        FLDrive.ResetRotation();
        FRDrive.ResetRotation();
        BLDrive.ResetRotation();
        BRDrive.ResetRotation();
    }
    //bad
                    // void DriveWait(bool stop){
                    //     if(stop)    DR(0,0);
                    //     while(DriveSpinning()){EndTimeSlice(DRL.ChangeMsec);}
                    // }
                //Auton
                    // double DriveMaxTargetDelta(){
                    //     return MAX(MAX(MAX(std::abs(FLDrive.GetTargetSetting()-FLDrive.Rotation())
                    //                       ,std::abs(FRDrive.GetTargetSetting()-FRDrive.Rotation()))
                    //                       ,std::abs(BLDrive.GetTargetSetting()-BLDrive.Rotation()))
                    //                       ,std::abs(BRDrive.GetTargetSetting()-BRDrive.Rotation()));//calc max
                    // }
                    
                    // void DriveRatioUpdate(){
                    //     if(FLDrive.GetTargetSettingDelta()==DriveMaxTargetDelta())  FLDrive.SetVRatio(1);//in case 0/0
                    //     else                                                        FLDrive.SetVRatio(std::abs((FLDrive.GetTargetSettingDelta())/DriveMaxTargetDelta()));
                    //     if(FRDrive.GetTargetSettingDelta()==DriveMaxTargetDelta())  FRDrive.SetVRatio(1);
                    //     else                                                        FRDrive.SetVRatio(std::abs((FRDrive.GetTargetSettingDelta())/DriveMaxTargetDelta()));
                    //     if(BLDrive.GetTargetSettingDelta()==DriveMaxTargetDelta())  BLDrive.SetVRatio(1);
                    //     else                                                        BLDrive.SetVRatio(std::abs((BLDrive.GetTargetSettingDelta())/DriveMaxTargetDelta()));
                    //     if(BRDrive.GetTargetSettingDelta()==DriveMaxTargetDelta())  BRDrive.SetVRatio(1);
                    //     else                                                        BRDrive.SetVRatio(std::abs((BRDrive.GetTargetSettingDelta())/DriveMaxTargetDelta()));
                    // }
            
                    // //old
                    //     // void Drive(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=1){
                    //     //     DriveSide=false;
                    //     //     double Dir=SGN(Dis);
                    //     //     double Rev=std::abs(Dis)/WheelCir;
                    //     //     int Pct1=0;
                    //     //     int Pct2=0;
                    //     //     FLDrive.ResetRotation();
                    //     //     FRDrive.ResetRotation();
                    //     //     while(std::abs(FLDrive.Rotation())<std::abs(Rev)){
                    //     //         double Input1=FLDrive.Rotation();
                    //     //         double Input2=FLDrive.Rotation();
                    //     //         if(std::abs(Input1)>std::abs(Input2)){
                    //     //             Pct1=Pct-Correction;
                    //     //             Pct2=Pct;
                    //     //         }
                    //     //         else if(std::abs(Input1)<std::abs(Input2)){
                    //     //             Pct1=Pct;
                    //     //             Pct2=Pct-Correction;
                    //     //         }
                    //     //         else if(std::abs(Input1)==std::abs(Input2)){
                    //     //             Pct1=Pct;
                    //     //             Pct2=Pct;
                    //     //         }
                    //     //         Pct1=Pct1*Dir;
                    //     //         Pct2=Pct2*Dir;
                    //     //         DR(Pct1,Pct2);
                    //     //         EndTimeSlice(4);
                    //     //     }
                    //     //     Controller1.Screen.clearLine();
                    //     //     Controller1.Screen.print("Drived");
                    //     //     if(EndWait==-1){//                                                          Junction
                    //     //         //only use if another drive command fallows
                    //     //     }
                    //     //     else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
                    //     //         //QDRS();//quick drive ramp stop
                    //     //         DR(0,0);
                    //     //         while(DriveSpinning()){EndTimeSlice(4);}
                    //     //         EndTimeSlice(EndWait);
                    //     //     }
                    //     //     else{//>=0,!=-1; set stop dont wait;                                        Stop
                    //     //         DR(0,0);
                    //     //     }
                    //     //     Controller1.Screen.clearLine();
                    //     //     Controller1.Screen.print("Drove");

                    //     // }
                    //     // void DriveRecon(int Pct,int Wait,int EndWait=250){
                    //     //     DriveSide=false;
                    //     //     DR(Pct,Pct);
                    //     //     vex::task::sleep(Wait);
                    //     //     if(EndWait>0){
                    //     //         DR(0,0);
                    //     //         while(DriveSpinning()){EndTimeSlice(DRL.ChangeMsec);}
                    //     //         Controller1.Screen.clearLine();
                    //     //         Controller1.Screen.print("RECONED");
                    //     //     }
                    //     //     else if(EndWait==0){
                    //     //         Controller1.Screen.clearLine();
                    //     //         Controller1.Screen.print("RECONED!END");
                    //     //     }
                    //     // }
                    //     // void DriveS(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=1){
                    //     //     DriveSide=true;
                    //     //     double Dir=SGN(Dis);
                    //     //     double Rev=std::abs(Dis)/WheelCir;
                    //     //     int Pct1=0;
                    //     //     int Pct2=0;
                    //     //     FLDrive.ResetRotation();
                    //     //     FRDrive.ResetRotation();
                    //     //     while(std::abs(FLDrive.Rotation())<std::abs(Rev)){
                    //     //         double Input1=FLDrive.Rotation();
                    //     //         double Input2=FLDrive.Rotation();
                    //     //         if(std::abs(Input1)>std::abs(Input2)){
                    //     //             Pct1=Pct-Correction;
                    //     //             Pct2=Pct;
                    //     //         }
                    //     //         else if(std::abs(Input1)<std::abs(Input2)){
                    //     //             Pct1=Pct;
                    //     //             Pct2=Pct-Correction;
                    //     //         }
                    //     //         else if(std::abs(Input1)==std::abs(Input2)){
                    //     //             Pct1=Pct;
                    //     //             Pct2=Pct;
                    //     //         }
                    //     //         Pct1=Pct1*Dir;
                    //     //         Pct2=Pct2*Dir;
                    //     //         DR(Pct1,Pct2);
                    //     //         EndTimeSlice(4);
                    //     //     }
                    //     //     Controller1.Screen.clearLine();
                    //     //     Controller1.Screen.print("Drivedside01");
                    //     //     if(EndWait==-1){//                                                          Junction
                    //     //         //only use if another drive command fallows
                    //     //     }
                    //     //     else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
                    //     //         //QDRS();//quick drive ramp stop
                    //     //         DR(0,0);
                    //     //         while(DriveSpinning()){EndTimeSlice(4);}
                    //     //         EndTimeSlice(EndWait);
                    //     //     }
                    //     //     else{//>=0,!=-1; set stop dont wait;                                        Stop
                    //     //         DR(0,0);
                    //     //     }
                    //     //     DriveSide=false;
                    //     //     // Controller1.Screen.clearLine();
                    //     //     Controller1.Screen.print("Drove");
                    //     // }
                    //     // void DriveReconS(int Pct,int Wait,int EndWait=DriveEndWait){
                    //     //     DriveSide=true;
                    //     //     DR(Pct,Pct);
                    //     //     vex::task::sleep(Wait);
                    //     //     if(EndWait>0){
                    //     //         DR(0,0);
                    //     //         while(DriveSpinning()){EndTimeSlice(DRL.ChangeMsec);}
                    //     //         Controller1.Screen.clearLine();
                    //     //         Controller1.Screen.print("RECONED");
                    //     //     }
                    //     //     else if(EndWait==0){
                    //     //         Controller1.Screen.clearLine();
                    //     //         Controller1.Screen.print("RECONED!END");
                    //     //     }
                    //     //     DriveSide=false;
                    //     // }
                    //     // void DriveWait(bool stop){
                    //     //     if(stop)    DAR.Request(0);
                    //     //     while(DriveSpinning()){EndTimeSlice(DAR.ChangeMsec);}
                    //     // }
                    //     // bool DriveSSTTH(){
                    //     //     if(FLDrive.SSTTH() || FRDrive.SSTTH() || BLDrive.SSTTH() || BRDrive.SSTTH())    return true;
                    //     //     else                                                                            return false;            
                    //     // }
                    double YActual(){
                        return ( FLDrive.Rotation()+FRDrive.Rotation()+BLDrive.Rotation()+BRDrive.Rotation())*WheelCir/4;
                    }
                    double XActual(){
                        return (-FLDrive.Rotation()+FRDrive.Rotation()+BLDrive.Rotation()-BRDrive.Rotation())*WheelCir/4;
                    }
                    double ZActual(){
                        return (-FLDrive.Rotation()+FRDrive.Rotation()-BLDrive.Rotation()+BRDrive.Rotation())*(WheelCir/40)*180/M_PI;
                    }
                    // int DriveRampTaskFun(){
                    //     DAR.Enabled=true;
                    //     while(DAR.Enabled){
                    //         DAR.Run();
                    //         EndTimeSlice(DAR.ChangeMsec);
                    //     }
                    //     return 0;

                    // }
                    // int DrivePIDTaskFun(){
                    //     DrivePIDTAskEnabled=true;

                    //     while(DrivePIDTAskEnabled){
                    //         DriveRatioUpdate();//update ratios to get to target at the same time
                    //         //QuadRamp
                                

                    //         FLDrive.SMS(FLPID.GetOutput());//output pid relitive to largest target
                    //         FRDrive.SMS(FRPID.GetOutput());//output pid relitive to largest target
                    //         BLDrive.SMS(BLPID.GetOutput());//output pid relitive to largest target
                    //         BRDrive.SMS(BRPID.GetOutput());//output pid relitive to largest target
                    //         // FLDrive.SMS(FLPID.Output(FLDrive.GetTargetSetting(),FLDrive.Rotation()));//output pid relitive to largest target
                    //         // FRDrive.SMS(FRPID.Output(FRDrive.GetTargetSetting(),FRDrive.Rotation()));//output pid relitive to largest target
                    //         // BLDrive.SMS(BLPID.Output(BLDrive.GetTargetSetting(),BLDrive.Rotation()));//output pid relitive to largest target
                    //         // BRDrive.SMS(BRPID.Output(BRDrive.GetTargetSetting(),BRDrive.Rotation()));//output pid relitive to largest target
                    //     Controller1.Screen.print(ZActual());

                    //         EndTimeSlice(20);
                    //       }
                    //     return 0;
                    // }
                    // void DriveSetTargets(double y,double x,double z,bool rel=true,bool degin=true){//in,in,deg
                    //     if(degin)   z*=M_PI/180;

                    //     if(rel){
                    //         FLDrive.AddTargetSetting((y+x-10*z)/WheelCir);
                    //         FRDrive.AddTargetSetting((y-x+10*z)/WheelCir);
                    //         BLDrive.AddTargetSetting((y-x-10*z)/WheelCir);
                    //         BRDrive.AddTargetSetting((y+x+10*z)/WheelCir);
                    //     }
                    //     else{
                    //         FLDrive.SetTargetSetting((y+x-10*z)/WheelCir);//need to add last rotsetting
                    //         FRDrive.SetTargetSetting((y-x+10*z)/WheelCir);
                    //         BLDrive.SetTargetSetting((y-x-10*z)/WheelCir);
                    //         BRDrive.SetTargetSetting((y+x+10*z)/WheelCir);
                    //     }
                        
                    //     //need to set ratio
                    // }
                //old
                    // void DriveSST(){
                    //     FLDrive.SST(FLDrive.GetTargetSetting(),FLDrive.GetVSetting());
                    //     FRDrive.SST(FRDrive.GetTargetSetting(),FRDrive.GetVSetting());
                    //     BLDrive.SST(BLDrive.GetTargetSetting(),BLDrive.GetVSetting());
                    //     BRDrive.SST(BRDrive.GetTargetSetting(),BRDrive.GetVSetting());
                    // }
                    // void DriveRelVSetting(int vmax){
                    //     double DRMax = MAX(MAX(MAX(std::abs(FLDrive.GetTargetSetting())
                    //                               ,std::abs(BLDrive.GetTargetSetting()))
                    //                               ,std::abs(FRDrive.GetTargetSetting()))
                    //                               ,std::abs(BRDrive.GetTargetSetting()));//calc max
                    //     //Set v setting
                    //         FLDrive.SetVSetting(FLDrive.GetTargetSetting()*vmax/DRMax);
                    //         FRDrive.SetVSetting(FRDrive.GetTargetSetting()*vmax/DRMax);
                    //         BLDrive.SetVSetting(BLDrive.GetTargetSetting()*vmax/DRMax);
                    //         BRDrive.SetVSetting(BRDrive.GetTargetSetting()*vmax/DRMax);
                    // }

        
        //need forward def
        // old
                    //Ramping Tasks; vex made me
                        // int LRTaskRun(){//lift ramping task
                        //     LR.Enabled=true;
                        //     while(LR.Enabled){
                        //         LR.Run();
                        //         Lift.SMS(LR.Output());
                        //         EndTimeSlice(LR.ChangeMsec);
                        //     }
                        //     Lift.SMS(0);//stop the motor when exiting ramping
                        //     return 0;
                        // }
                        // int DRTaskRun(){//drive ramping task
                        //     DAR.Enabled=true;
                        //     while(DAR.Enabled){
                        //         DAR.Run();
                        //             FLDrive.SetVSetting(FLDrive.GetTargetSetting()*DAR.Output()/DRMax);
                        //             FRDrive.SetVSetting(FRDrive.GetTargetSetting()*DAR.Output()/DRMax);
                        //             BLDrive.SetVSetting(BLDrive.GetTargetSetting()*DAR.Output()/DRMax);
                        //             BRDrive.SetVSetting(BRDrive.GetTargetSetting()*DAR.Output()/DRMax);
                        //         DriveSMS(FLDrive.GetVSetting(),FRDrive.GetVSetting(),BLDrive.GetVSetting(),BRDrive.GetVSetting());
                        //         EndTimeSlice(DAR.ChangeMsec);
                        //     }
                        //     DriveSMS(0,0,0,0);//stop motors when exiting ramping
                        //     return 0;
                        // }
                    // void DriveVSetting(int v){
                    //     FLDrive.SetVSetting(v);
                    //     FRDrive.SetVSetting(v);
                    //     BLDrive.SetVSetting(v);
                    //     BRDrive.SetVSetting(v);
                    // }
                    // int DriveRamping(){//sets drive motors to spin
                    //     DAR.Enabled=true;
                    //     while(DAR.Enabled){
                    //         DAR.Run();
                    //         DriveRelVSetting(DAR.Output());
                    //         DriveSST();
                    //         vex::task::sleep(DAR.ChangeMsec);
                    //     }
                    //     return 1;
                    // }

void AutonSelFun(){
    if(AutSel[0].value(vex::analogUnits::pct)>80)         FeildPos=StartPos::BackRed;
    else if(AutSel[0].value(vex::analogUnits::pct)>50)    FeildPos=StartPos::FrontRed;
    else if(AutSel[0].value(vex::analogUnits::pct)>17)    FeildPos=StartPos::FrontBlue;
    else                                                FeildPos=StartPos::BackBlue;

    if(AutSel[1].value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
    else if(AutSel[1].value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
    else                                                AutoProg = ProgPot::Pink;

    if(AutSel[2].value(vex::percentUnits::pct)>70)        AVariant = Variant::White;
    else if(AutSel[2].value(vex::percentUnits::pct)>25)   AVariant = Variant::Black;
    else                                                AVariant = Variant::Purple;

}