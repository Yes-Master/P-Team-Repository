// #ifndef MECANUM_DRIVE_HPP
// #define MECANUM_DRIVE_HPP
// #include "okapi/api.hpp"
// class MecanumDrive{
// protected:
//   int maxRPM=200;
//   double Width;//distance between left to right wheels
//   double Length;//distance between front to back wheels
//   double WheelCir;
//
//   okapi::Motor *FrontLeft;
//   okapi::Motor *BackLeft;
//   okapi::Motor *FrontRight;
//   okapi::Motor *BackRight;
//
//   double forwardSum=0;
//   double strafeSum=0;
//   double yawSum=0;
//
//   void calcDis(double forward, double strafe, double yaw);
//   void calcVelRatio();
// public:
//   /**
//   * construct MecanumDrive object useing okapi Motors
//   *
//   * @param fl Front Left Motor
//   * @param bl Back Left Motor
//   * @param fr Front Right Motor
//   * @param br Back Right Motor
//   * @param wheelcir the distance travled for one revolution of the motor
//   * @param width the distance between the left to right wheels
//   * @param length the distance between the front and back wheels
//   */
//   MecanumDrive(const okapi::Motor &fl,const okapi::Motor &bl,const okapi::Motor &fr,const okapi::Motor &br,double wheelcir,double width,double length);
//   /**
//   * move the left side of the drive using velocity mode.
//   *
//   * @param v left side velocity
//   */
//   void left(double v);
//   /**
//   * move the right side of the drive using velocity mode.
//   *
//   * @param v right side velocity
//   */
//   void right(double v);
//   /**
//   * move the drive with tank control using velocity mode.
//   *
//   * @param leftV left side velocity
//   * @param rightV Right side velocity
//   * @param strafeV side velocity
//   */
//   void tank(double left,double right,double strafe);
//   /**
//   * move the drive with tank control using velocity mode.
//   *
//   * @param con the controller axis values to use
//   */
//   void tank(okapi::Controller con);
//   /**
//   * move the drive with arcade control using velocity mode.
//   *
//   * @param forwardV Forward velocity
//   * @param strafeV Srafeing velocity
//   * @param yawV Yaw velocity
//   */
//   void arcade(double forwardV,double strafeV,double yawV);
//   /**
//   * move the drive with arcade control using velocity mode.
//   *
//   * @param con the controller axis values to use
//   */
//   void arcade(okapi::Controller con);
//   /**
//   * set the brake mode for the drive system motors.
//   *
//   * @param m Brake Mode being set to motors
//   */
//   void set_brakeMode(okapi::AbstractMotor::brakeMode m);
//   /**
//   * set PID for drive system motors.
//   *
//   * @param kF the feed-forward constant
//   * @param kP the proportional constant
//   * @param kI the integral constant
//   * @param kD the derivative constant
//   * @param filter a constant used for filtering the profile acceleration
//   * @param limit the integral limit
//   * @param threshold the threshold for determining if a position movement has reached its goal
//   * @param loopSpeed the rate at which the PID computation is run (in ms)
//   */
//   void setPosPIDFull( double kF,
//                       double kP,
//                       double kI,
//                       double kD,
//                       double filter,
//                       double limit,
//                       double threshold,
//                       double loopSpeed);
//     /**
//     * move the drive system absolute using absolute positioning.
//     * DO NOT RESET ENCODERS
//     *
//     * @param forward the forward distance to drive
//     * @param strafe the strafe distance to drive
//     * @param yaw the turn distance to turn
//     */
//     void Absolute(double forward,double strafe,double yaw);
//     /**
//     * move the drive system Relititive using absolute positioning.
//     * DO NOT RESET ENCODERS
//     *
//     * @param forward the forward distance to drive
//     * @param strafe the strafe distance to drive
//     * @param yaw the turn distance to turn
//     */
//     void AbsolutelyRelative(double forward,double strafe,double yaw);
//     /**
//     * move the drive system Relititive using Relititive positioning.
//     *
//     * @param forward the forward distance to drive
//     * @param strafe the strafe distance to drive
//     * @param yaw the turn distance to turn
//     */
//     void Relititive(double forward,double strafe,double yaw);
//   };
//   #endif /* end of include guard: MECANUM_DRIVE_HPP */
