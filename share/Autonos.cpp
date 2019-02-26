//Double Shot
    //Funs
        void DoubleShotFrontFun(){
            if(!PuncherCharged) PuncherAut(true,0,false);//charge
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(true,0,false);//fire
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(false,0,false);//charge
                if(!DoubleShotTaskEnabled)  return;
            Lift.SetVSetting(100);
            Clamp.SetTargetSetting(ClampPosIn);
            Lift.SetTargetSetting(LiftPosPunUp);
                if(!DoubleShotTaskEnabled)  return;
            PuncherWait();//wait for puncher to finish charging
                if(!DoubleShotTaskEnabled)  return;
            while(Lift.SSTTH()){//wait for lift to stop moving
                EndTimeSlice(5);
            }
            EndTimeSlice(50);
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(true,0,false);//fire
                if(!DoubleShotTaskEnabled)  return;
            Lift.SetTargetSetting(LiftPosDown);//return lift to ground
            Clamp.SetTargetSetting(ClampPosUp);
        }
        void DoubleShotBackFun(){
            Lift.SetVSetting(50);//75
            Lift.SetTargetSetting(LiftPosPunUp);
                if(!DoubleShotTaskEnabled)  return;
            PuncherWait();//wait for puncher to finish charging
                if(!DoubleShotTaskEnabled)  return;
            while(Lift.SSTTH()){//wait for lift to stop moving
                EndTimeSlice(5);
            }
                if(!DoubleShotTaskEnabled)  return;
            if(!PuncherCharged) PuncherAut(true,0,false);//charge
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(true,0,false);//fire
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(false,0,false);//charge
                if(!DoubleShotTaskEnabled)  return;
            Lift.SetVSetting(50);
            Lift.SetTargetSetting(LiftPosPunDown);
                if(!DoubleShotTaskEnabled)  return;
            PuncherWait();//wait for puncher to finish charging
                if(!DoubleShotTaskEnabled)  return;
            while(Lift.SSTTH()){//wait for lift to stop moving
                EndTimeSlice(5);
            }
                if(!DoubleShotTaskEnabled)  return;
            PuncherAut(true,0,false);//fire
                if(!DoubleShotTaskEnabled)  return;
            Lift.SetTargetSetting(LiftPosDown);//return lift to ground
        }
    //Usr
        int DoubleShotTaskFun(){
            IntakeAutoEnabled=true;
            Lift.SendControl=SendControl::SST;//set lift to spin to control
            Lift.SetVSetting(50);
            DriveSetStop(vex::brakeType::hold);//set drive to hold
            if(Lift.GetTargetSetting()==LiftPosDown)    DoubleShotFrontFun();
            else                                        DoubleShotBackFun();
            return 0;
        }
    //Auton
        void DoubleShotFrontAuton(){
            Lift.SetTargetSetting(LiftPosDown);
            Lift.SendControl=SendControl::SST;//set lift to spin to control

            if(!PuncherCharged) PuncherAut(true);//charge
            PuncherAut(true);//fire
            PuncherAut(false);//charge
            Lift.SetVSetting(100);
            Lift.SetTargetSetting(LiftPosPunUp);

            Clamp.SetTargetSetting(ClampPosIn);
            PuncherWait();//wait for puncher to finish charging
            while(Lift.SSTTH()){//wait for lift to stop moving
                EndTimeSlice(5);
            }
            PuncherAut(true);//fire
            PuncherWait();
            Clamp.SetVSetting(50);
            Clamp.SetTargetSetting(ClampPosUp);
            Lift.SetVSetting(50);
            Lift.SetTargetSetting(LiftPosDown);//return lift to ground
        }
        void DoubleShotBackAuton(bool clampLetGo=true){
            if(clampLetGo)  Clamp.SetTargetSetting(ClampPosUp,75);
            Lift.SetTargetSetting(225,100);
            if(!PuncherCharged) PuncherAut(true);//charge

            Lift.Wait(0);

            PuncherAut(true);//fire
            PuncherAut(false);//charge

            Lift.SetTargetSetting(500,100);
            
            Lift.Wait(0);
            PuncherWait();//wait for puncher to finish charging
            EndTimeSlice(500);//wait for ball
            PuncherAut(true);//fire
            PuncherWait();
            Lift.SetTargetSetting(LiftPosDown);//return lift to ground
        }
//Autonos
    //FrontRed
        //Normal
            void AutFunFRNormal(){
                DriveRecon(-25,250);
                Drive(29,100,-1);
                Drive(3,50,1);
                Drive(-28,100,0);
                TurnEnc(-90,100,0);
                DriveReconS(-100,500);

                PuncherAut(false);//charge the puncher dont wait
                DriveS(8.5,50,1);
                
                Drive(1.5,50);
                PuncherAut(true);
                PuncherAut(false);//charge the puncher dont wait
                Drive(18,50,1);
                PuncherAut(true);//fire
                DriveS(-0.5,100,1);//slight side to miss pole

                // IntakeAutoEnabled=false;
                Drive(10,100,0);//drive into flag
                Drive(-2,100,1);
                TurnEnc(-25,100,1);//45deg turn get cap
                Drive(-15,75,1);
                // PuncherAut(false);
                TurnEnc(75,100,1);
                Drive(-2,50,0);
                // PuncherAut();
            }
        //NorMid
            void AutFunFRNorMid(int flags=2){//0=bottom,1=top,2=both
                Drive(29,100,-1);
                Drive(3,50,1);

                Drive(-26,100,1);
                TurnEnc(-87,50,1);

                PuncherAut(false);//charge the puncher dont wait
                Drive(2,25,50);

                DoubleShotFrontAuton();

                TurnEnc(-2,50,1);

                Drive(36,100,0);//drive into flag
                Drive(-4,50,1);
                TurnEnc(-45,50,1);//45deg turn get cap
                Drive(-6,100,0);

                    Lift.SetVSetting(100);
                    Lift.SetTargetSetting(LiftPosPunUp);
                    // Lift.SendControl=SendControl::SST;

                Drive(-7,100,1);

                switch (flags)
                {
                    case 0:
                        PuncherAut(false);
                        TurnEnc(84,100,1);

                        PuncherAut();
                        Lift.SetVSetting(50);
                        Lift.SetTargetSetting(LiftPosDown);
                        break;
                    case 1:
                        PuncherAut(false);
                        
                        Lift.SetVSetting(50);
                        Lift.SetTargetSetting(LiftPosDown);

                        TurnEnc(84,100,1);

                        while(Lift.Spinning()){
                            EndTimeSlice(5);
                        }

                        PuncherAut();
                        break;
                    case 2:
                        Lift.SetVSetting(100);
                        Lift.SetTargetSetting(LiftPosDown);

                        PuncherAut(false);
                        TurnEnc(84,100,1);

                        // Drive(-1.25,25,0);
                        DoubleShotFrontAuton();  
                        break;
                    default:
                        TurnEnc(84,100,1);
                        break;
                }
            }
        //ZBread
            void AutFunFRZBread(){
                // Drive(29,100,-1); Drive(3,50,750);//get ball
                // Drive(-12,50,-1); Drive(-3,25,500);//back up safely
                // Turn(-5.6);//line up to pole
                // PuncherAut(false);//charge
                // Drive(5);
                // // Flip(FliperPosDown,false);
                // PuncherAut(); PuncherAut(false);//fire && Charge
                // Turn(-0.2);
                // Drive(18);
                // PuncherAut();//fire
                //             // // Drive();
                //             // Turn(4);
                //             // EndTimeSlice(1500);
                //             // Drive(-8);
                //             // Flip(FliperPosUpMid);
                //             // Drive(5);
                //             // Flip(FliperPosIn,false);
                // Turn(-2.4);//line up to park
                // Drive(-56,100);//park
            }
        //MidFar
    //FrontBlue
        //Normal
            void AutFunFBNormal(){
                DriveRecon(-25,250);
                Drive(29,100,-1);
                Drive(3,50,1);
                Drive(-28,100,0);
                TurnEnc(90,100,0);
                DriveReconS(100,500);

                PuncherAut(false);//charge the puncher dont wait
                DriveS(-5,50,1);
                
                PuncherAut(true,10);
                PuncherAut(false);//charge the puncher dont wait
                Drive(18,50,1);
                PuncherAut(true,10);//fire
                // DriveS(.5,100,1);//slight side to miss pole

                // IntakeAutoEnabled=false;
                Drive(10,100,0);//drive into flag
                Drive(-2,100,1);
                TurnEnc(25,100,1);//45deg turn get cap
                Drive(-15,75,1);
                // PuncherAut(false);
                TurnEnc(-75,100,1);
                Drive(-2,50,0);
                // PuncherAut();
            }
        //NorMid
           void AutFunFBNorMid(int flags=2){
                Drive(29,100,-1);
                Drive(3,50,1);

                Drive(-26.5,100,1);
                TurnEnc(85,50,1);

                PuncherAut(false);//charge the puncher dont wait
                Drive(1,50,0);

                DoubleShotFrontAuton();

                TurnEnc(1.5,50,1);

                Drive(35,100,0);//drive into flag
                DriveS(1,50,0);
                Drive(-4,50,1);
                TurnEnc(40,50,1);//45deg turn get cap
                Drive(-6,100,0);

                    Lift.SetVSetting(100);
                    Lift.SetTargetSetting(LiftPosPunUp);
                    // Lift.SendControl=SendControl::SST;

                Drive(-6,100,1);

                switch (flags)
                {
                    case 0:
                        PuncherAut(false);
                        TurnEnc(-87,100,1);

                        PuncherAut();
                        Lift.SetVSetting(50);
                        Lift.SetTargetSetting(LiftPosDown);
                        break;
                    case 1:
                        PuncherAut(false);
                        
                        Lift.SetVSetting(50);
                        Lift.SetTargetSetting(LiftPosDown);

                        TurnEnc(-87,100,1);

                        while(Lift.Spinning()){
                            EndTimeSlice(5);
                        }

                        PuncherAut();
                        break;
                    case 2:
                        Lift.SetVSetting(100);
                        Lift.SetTargetSetting(LiftPosDown);

                        PuncherAut(false);
                        TurnEnc(-87,100,1);

                        // Drive(-1,50,0);
                        DoubleShotFrontAuton();  
                        break;
                    default:
                        TurnEnc(-87,100,1);
                        break;
                }
            }
        //ZBread
            void AutFunFBZBread(){
                // Drive(29,100,-1); Drive(3,50,500);//get ball
                // Drive(-12,50,-1); Drive(3,25,250);//back up safely
                // Turn(6.5);//line up to pole
                // PuncherAut(false);//charge
                // Drive(5);
                // Flip(FliperPosDown,false);
                // PuncherAut(); PuncherAut(false);//fire && Charge
                // Drive(18);
                // PuncherAut();//fire
                // // Drive();
                // Turn(-4);
                // EndTimeSlice(1750);
                // Drive(-10);
                // Flip(FliperPosUpMid);
                // Drive(5);
                // Flip(FliperPosIn,false);
                // Turn(6.7);//line up to park
                // Drive(-43,100);//park
            }
        //MidFar
    //BackRed
        //CapP
            void AutFunBRCaps(bool park=true){
                Drive(27,100,0);
                Drive(3,50,1);

                Drive(-3,50,1);
                
                TurnEnc(-180,50,1);

                Drive(-9,50,0);
                
                Clamp.SetTargetSetting(ClampPosDown,100);
                Clamp.Wait(0);
                Lift.SetTargetSetting(450,100);

                TurnEnc(128,50,1);

                Lift.SetTargetSetting(850,100);
                Drive(-28);

                // DriveS(2,25,1);

                Lift.SetTargetSetting(635,75);
                Lift.Wait(100);
                Clamp.SetTargetSetting(ClampPosUp,75);
                Clamp.Wait(0);

                Lift.SetTargetSetting(LiftPosUp,50);
                Drive(5,50,1);

                TurnEnc(148,50,1);

                Drive(-8,100,0);
                Drive(-5,10,1);

                Drive(5,50,0);
                Drive(-25,100,1);

                Lift.SetTargetSetting(LiftPosDown,25);
            }

        //FFlP
            void AutFunBRFarFlags(){
                Drive(30,100,-1);
                Drive(3,50,100);

                DriveS(1,50,1);
                
                TurnEnc(-63,25,1);

                Drive(-10,50,1);
                
                DoubleShotBackAuton();

                // Drive(-10,50,1);
                Lift.SetTargetSetting(LiftPosUp,50);
                TurnEnc(150,50,1);

                Drive(-6,100,0);
                Drive(-5,25,0);

                Drive(5,25,0);
                Drive(-25,100,1);

                Lift.SetTargetSetting(LiftPosDown,50);
            }
        //Park
            void AutFunBRPark(bool Park=true){
                // Drive(22,100,-1);
                // Drive(3,50,250);
                // Turn(-11);
                // Flip(FliperPosDown);
                // Drive(-9);
                // Flip(FliperPosIn);
                // Turn(18);
                // if(Park){
                //     IntakeAutoEnabled=false;
                //     Drive(-48,100);//get on platform
                // }
                // else{//!Park
                //     Drive(-10);//dont touch cap
                // }
            }
        //Flags
            void AutFunBRFlags(){
                Drive(29,100,-1);
                Drive(3,50,1);
                Drive(-28,100,0);
                TurnEnc(-90,100,0);
                Drive(5,25,1);
                DriveReconS(-100,500);
                DriveReconS(-25,200);

                DriveS(6.7,50,1);
                // Turn(1,25,1);
                Drive(35,100,1);//drive to front flag pos
                PuncherAut(false);
                // Turn(1,25,1);
                PuncherAut(true);
                PuncherAut(false);//charge the puncher dont wait
                Drive(19,50,0);
                PuncherAut(true);//fire
                // DriveS(0.5,100,1);//slight side to miss pole
                DriveS(-1.5,25,1);
                // IntakeAutoEnabled=false;
                Drive(10,100,0);//drive into flag
                Drive(-20,100,1);
                // TurnEnc(-25,100,1);//45deg turn get cap
                // Drive(-15,75,1);
                // PuncherAut(false);
                // TurnEnc(78,100,1);
                // Drive(-2,50,0);
                // PuncherAut();
            }
    //BackBlue
        //Cap
            void AutFunBBCaps(bool park=true){
                Drive(26,100,-1);
                Drive(3,50,1);

                Drive(-3,50,1);
                
                TurnEnc(180,50,1);

                Drive(-8,50,0);
                
                Clamp.SetTargetSetting(ClampPosDown,100);
                Clamp.Wait(0);
                Lift.SetTargetSetting(450,100);

                TurnEnc(-135,50,1);//turn to pole

                Lift.SetTargetSetting(850,100);
                Drive(-29);

                // DriveS(2,25,1);

                Lift.SetTargetSetting(650,100);
                Lift.Wait(0);
                Clamp.SetTargetSetting(ClampPosUp,100);
                Clamp.Wait(0);
                
                            // EndTimeSlice(50);//clampwait
                            // while(Clamp.SSTTH()){//wait for lift to stop moving
                            //     EndTimeSlice(5);
                            // }

                Lift.SetTargetSetting(LiftPosDown,50);
                Drive(5,75,1);

                // TurnEnc(-150,50,1);

                // Drive(-10,100,0);
                // Drive(-5,25,0);

                // Drive(5,25,0);
                // Drive(-25,100,1);

                // Lift.SetTargetSetting(LiftPosDown,50);
            }
        //FarFlags
            void AutFunBBFarFlags(){
                Drive(30,100,-1);
                Drive(3,50,100);

                DriveS(-1,50,1);
                
                TurnEnc(59,25,1);

                Drive(-7.75,50,1);
                
                DoubleShotBackAuton();

                // Drive(-10,50,1);
                Lift.SetTargetSetting(LiftPosUp,50);
                TurnEnc(-150,50,1);

                Drive(-6,100,0);
                Drive(-5,25,0);

                Drive(5,25,0);
                Drive(-25,100,1);

                Lift.SetTargetSetting(LiftPosDown,25);
            }
        //Park
            void AutFunBBPark(bool Park=true){
                // if(Park){
                //     EndTimeSlice(5000);
                //     IntakeAutoEnabled=false;
                //     Drive(-26,100,1);//get on platform

                //     Lift.SetTargetSetting(LiftPosDown);//set lift up
                //     Lift.SetVSetting(75);
                //     Lift.SendControl=SendControl::SST;//enable move
                //     Clamp.SetVSetting(50);
                //     Clamp.SetTargetSetting(ClampPosUp);//set clamp in
                //     IntakeAutoEnabled=false;//stop auto intake
                // }
                // else{//!Park
                //     // Drive(-10);//dont touch cap
                // }
            }

        //Flags
            void AutFunBBFlags(){
                Drive(28,100,-1);
                Drive(3,50,500);
                Drive(-28.5,100);

                TurnEnc(90,100,50);

                DriveReconS(25,500);
                DriveS(-9,50);

                Drive(50);//drive to front flag pos
                DriveReconS(50,750,0);
                PuncherAut(false);//charge the puncher dont wait
                DriveS(-9,50);

                PuncherAut();   PuncherAut(false);//charge the puncher dont wait
                
                Drive(7,100);
                PuncherAut();//fire
                DriveS(1);//miss pole
                // IntakeAutoEnabled=false;
                Drive(5,100);//drive into flag
                Drive(-10,100);//backup from flags
            }
    //Special
        void Sniper(){
            PuncherAut(false);
            PuncherAut();
        }
        void TestingFront(){
        }
        void TestingBack(){
        }

    //Skills
        void FrontSkills(){
            //     Drive(29,100,-1);
            //     Drive(3,50,500);
            //     Drive(-29.5,100,-1);
            //     DriveRecon(-25,500);

            //     Drive(10,25);
            //     PuncherAut(false);//charge the puncher dont wait
            //     Turn(-9.2);

            // Drive(1,25);
            // PuncherAut();//fire
            // PuncherAut(false);//charge the puncher dont wait
            // Drive(7,100);
            // EndTimeSlice(500);//time
            // PuncherAut();//fire
            // EndTimeSlice(100);//time
            // //Drive(2,50);//drive up to pole
            // Turn(-.6);//slight turn to miss pole
            // // IntakeAutoEnabled=false;
            // Drive(6,100);//drive into flag

            // Turn(-3.4);//45deg turn get cap
            // Flip(FliperPosDown);
            // Drive(-4,100,-1);
            // Drive(-15,25,100);
            // Flip(FliperPosIn);
            // //=======================================
            // Turn(-4.6);//turn to wall
            // // Flip(FliperPosIn);
            // Drive(23,50);//drive to wall
            // IntakeAutoEnabled=false;
            // DriveRecon(25,500);//recon
            // IntakeAutoEnabled=true;
            // Drive(-5,50);//drive away form wall
            // Turn(-9.5);//tsurn perallel to wall
            // Drive(42,50);//drive perallel to wall && line up to park
            // Turn(9.5);//turn to park
            // Drive(7,50);//drive to wall
            // IntakeAutoEnabled=false;
            // DriveRecon(25,500);//recon
            // Drive(-80,100);//drive on park
        }
        void BackSkills(){
            Drive(29,100,-1);
            Drive(3,50,1);

            Drive(-27,50,1);
            TurnEnc(-92,50,1);

            Drive(45,75,1);

            DriveS(-5,75,0);
            DriveReconS(-25,1000,25);
            DriveS(7,50,1);

            PuncherAut(false);//charge the puncher dont wait
            // Drive(10,100,1);

            DoubleShotFrontAuton();

            DriveS(-3,50,0);//slight side to miss pole
                // Drive(18,50,0);

            // IntakeAutoEnabled=false;
            Drive(45,100,0);//drive into flag

            DriveReconS(50,350,0);
            DriveS(1,10,0);
            DriveRecon(50,350,0);

            Drive(-40,75,0);//Drive back to get next ball
            
            TurnEnc(90,25,1);

            Drive(41,75,1);//Drive into ball
            DriveReconS(50,500,0);

            DriveS(-6,25,1);

            TurnEnc(-90,25,1);
            DoubleShotFrontAuton();

            DriveS(-1,25,1);
            Drive(37,75,1);

            // DriveReconS(50,250,0);
            // DriveS(-2,25,1);
            DriveRecon(25,250,0);

            Drive(-20,50,1);

            TurnEnc(90,25,1);

            Drive(-20,50,0);
            Lift.SetTargetSetting(LiftPosUp,100);
            Drive(-5,75,1);

            TurnEnc(-93,25,1);

            Drive(-45,50,1);

            TurnEnc(-90,50,0);
            // DriveRecon(50,250,0);
            Lift.SetTargetSetting(LiftPosUp);
            Drive(-55,100,0);
            Lift.SetTargetSetting(LiftPosDown);
            }
//FlowControl
    void AutoSelRunFuns(){//runs selected auton
        if(FeildPos==StartPos::BackRed){//back red
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          AutFunBRPark();// 
                else if(AVariant==Variant::Black)     AutFunBRPark();//
                else if(AVariant==Variant::Purple)    AutFunBRPark();//
            }
            else if(AutoProg==ProgPot::Green){//green
                if(AVariant==Variant::White)          AutFunBRFarFlags();// 
                else if(AVariant==Variant::Black)     AutFunBRFarFlags();//
                else if(AVariant==Variant::Purple)    AutFunBRFarFlags();//
            }
            else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          AutFunBRCaps();//
                else if(AVariant==Variant::Black)     AutFunBRCaps();//
                else if(AVariant==Variant::Purple)    AutFunBRCaps();//
            }
        }
        else if(FeildPos==StartPos::FrontRed){//front red
            if(AutoProg==ProgPot::Pink){//normal
                if(AVariant==Variant::White)          AutFunFRNormal();//
                else if(AVariant==Variant::Black)     AutFunFRNormal();//
                else if(AVariant==Variant::Purple)    AutFunFRNormal();//
            }
            else if(AutoProg==ProgPot::Green){//normid
                if(AVariant==Variant::White)          AutFunFRNorMid(0);//
                else if(AVariant==Variant::Black)     AutFunFRNorMid(1);//
                else if(AVariant==Variant::Purple)    AutFunFRNorMid(2);//
            }
            else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          AutFunFRZBread();// 
                else if(AVariant==Variant::Black)     BackSkills();//
                else if(AVariant==Variant::Purple)    AutFunFRZBread();//
            }
        }
        else if(FeildPos==StartPos::FrontBlue){//front blue
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          AutFunFBNormal();// 
                else if(AVariant==Variant::Black)     AutFunFBNormal();//
                else if(AVariant==Variant::Purple)    AutFunFBNormal();//
            }
            else if(AutoProg==ProgPot::Green){//green
                if(AVariant==Variant::White)          AutFunFBNorMid(0);// 
                else if(AVariant==Variant::Black)     AutFunFBNorMid(1);//
                else if(AVariant==Variant::Purple)    AutFunFBNorMid(2);//
            }
            else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          Sniper();// 
                else if(AVariant==Variant::Black)     AutFunFBZBread();//
                else if(AVariant==Variant::Purple)    AutFunFBZBread();//
            }
        }
        else if(FeildPos==StartPos::BackBlue){//back blue
            if(AutoProg==ProgPot::Pink){
                if(AVariant==Variant::White)          AutFunBBPark();// 
                else if(AVariant==Variant::Black)     AutFunBBPark();//
                else if(AVariant==Variant::Purple)    AutFunBBPark();//
            }
            else if(AutoProg==ProgPot::Green){//green
                if(AVariant==Variant::White)          AutFunBBFarFlags();// 
                else if(AVariant==Variant::Black)     AutFunBBFarFlags();//
                else if(AVariant==Variant::Purple)    AutFunBBFarFlags();//
            }
            else if(AutoProg==ProgPot::Yellow){
                if(AVariant==Variant::White)          AutFunBBCaps();//
                else if(AVariant==Variant::Black)     AutFunBBCaps();//
                else if(AVariant==Variant::Purple)    AutFunBBCaps();//
            }
        }
    }