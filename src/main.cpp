/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Project:      241E Codebase (Change Me)                                 */
/*    Author(s):    (Change Me)                                               */
/*    Created:      Nov. 1st 2024                                             */
/*    Modified:     Nov. 1st 2024 (Keep updated)                              */
/*    Description:  000a's program for (Game Name) (Year) Season              */
/*                                                                            */
/*    Codebase Disclaimer: V1.0 of 241E Codebase, written by team 241E        */
/*                            from Pinkerton Academy, Please do not remove    */
/*                            this disclaimer                                 */
/*----------------------------------------------------------------------------*/



#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Controller = controller(primary);

motor driveFR = motor(PORT21, ratio18_1, false); //you may need to change the bool to a true or false depending on the orientation of the motor
motor driveBR = motor(PORT21, ratio18_1, false);
// motor driveTR = motor(PORT21, ratio18_1, false); //only for 6 motor drive
motor driveFL = motor(PORT21, ratio18_1, false);
motor driveBL = motor(PORT21, ratio18_1, false);
// motor driveTL = motor(PORT21, ratio18_1, false); //only for 6 motor drive

motor_group driveRight = motor_group(driveFR, driveBR); //add drive TR if needed 
motor_group driveLeft  = motor_group(driveFL, driveBL); //add drive TL if needed
motor_group drive = motor_group(driveFR, driveBR, driveFL, driveBL); //add drive Top Left and top Right as needed

inertial IMU = inertial(PORT7);
//theese values very depending on the robot, change as needed to your robot
double wheelTravel = 320; //depedend on wheel size (4 in is 320mm and 3.25 in is 260) 
double trackWidth = 320; //width in mm between the center of left and right wheels
double wheelBase = 40; //length in mm between 
double WheelC = 259.339; //319.186 for 4 in 259.339 for 3.25in 
double gearRatio = (48/60); //motor->wheel (36/84 for 257) (36/60 for 292) (48/60 for 480) 
smartdrive Drivetrain = smartdrive(driveLeft, driveRight, IMU, wheelTravel, trackWidth, wheelBase, mm, gearRatio);


motor motor1 = motor(PORT21, ratio6_1, false); // Smartwire port: PORT##, ratio6_1: blue, ratio 18_1: green, ratio 36_1 red
motor motor2 = motor(PORT11, ratio18_1, false); //define 5.5W motors as 18_1 motors

 
pneumatics piston = pneumatics(Brain.ThreeWirePort.H); //A-H



bool driveRightBool = true;
bool driveLeftBool = true;
bool MotorBool = true; //you need a motor bool for every motor/motor group to utilize my efficent smart controllers defined as true by default
bool Motor2Toggle = false; //toggle bools are defined as false by default



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // IMU CALIBRATION
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  IMU.calibrate(0);

  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (IMU.isCalibrating()) {
    wait(25, msec);
  }
  Brain.Screen.print("Inertial Calibration Complete");

  //O ther PreAuto functions IE: Setting Velocity values, clearing encoder, etc





}

/*---------------------------------------------------------------------------*/
/*                          Autonomous Functions                             */
/*                                                                           */
/*  Use This space to define functions to be used in autonomous,             */
/*  This includes control loops like PID, or Odomtry                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// ..........................................................................

// ..........................................................................

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................

      // Arcade Sticks
      int drivetrainRightSideSpeed = Controller.Axis3.position() - Controller.Axis1.position(); 
      int drivetrainLeftSideSpeed = Controller.Axis3.position() + Controller.Axis1.position();


      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) { //5 and -5 are deadzones from center, if the controller is old it may need a higher deadzone
        if (driveLeftBool) {
          driveLeft.stop();
          driveLeftBool = false;
        }
      } else {
        driveLeftBool = true;
      }
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        if (driveRightBool) {
          driveRight.stop();
          driveRightBool = false;
        }
      } else {
        driveRightBool = true;
      }

      if (driveLeftBool) {
        driveLeft.setVelocity(drivetrainLeftSideSpeed, percent);
        driveLeft.spin(forward);
      }

      if (driveRightBool) {
        driveRight.setVelocity(drivetrainRightSideSpeed, percent);
        driveRight.spin(forward);
      }

      if (Controller.ButtonR1.pressing()) {
        motor1.spin(reverse);
        MotorBool = false;
      } else if (Controller.ButtonR2.pressing()) {
        motor1.spin(fwd);
        MotorBool = false;
      } else if (!MotorBool) {
        motor1.stop();
        MotorBool = true;
      }


      //Basic Toggle Example
        if (Controller.ButtonL2.pressing()) {
            Motor2Toggle = !Motor2Toggle;
            while (Controller.ButtonL2.pressing()){}
            if (Motor2Toggle) {
                motor2.spin(fwd);
            } else {
                motor2.stop();
            }
        }



    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//



int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
