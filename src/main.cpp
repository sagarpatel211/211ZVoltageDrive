/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                  */
/*    Author:       sagarpatel                                                */
/*    Created:      April 26, 2020                                            */
/*    Description:  Driver control with motors controlled with voltage        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontMotor       motor         20              
// RightFrontMotor      motor         18              
// LeftBackMotor        motor         14              
// RightBackMotor       motor         17              
// ExampleMotor         motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
using namespace vex;
vex::competition Competition; // A global instance of competition
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  vexcodeInit(); //Initializing Robot Configuration - Required!!!
  Brain.resetTimer(); //Resets The Brain Timer
}
/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/
void autonomous( void ) {
  //Autonomous Goes Here
}
/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/
void usercontrol(void) {
  double TurningImportance = 0.1; //Adjust this value for turning importance
  while (1) {
    double TurningVolts = (Controller1.Axis4.position(percent) * 0.12); //Converts controller % into motor voltage
    double ForwardVolts = Controller1.Axis3.position(percent) * 0.12 * (1 - (std::abs(TurningVolts)/12.0) * TurningImportance);
    //Multiplied by 0.12 since motor voltage can only range from 12 to -12, so multiplying it by 0.12 allows this
    //For example, if the controller Axis 1 is 100 percent, multiplying it by 0.12 will allow it to achieve max voltage!
    LeftFrontMotor.spin(forward, ForwardVolts + TurningVolts, voltageUnits::volt); //Motion
    LeftBackMotor.spin(forward, ForwardVolts + TurningVolts, voltageUnits::volt);  //Motion
    RightFrontMotor.spin(forward, ForwardVolts - TurningVolts, voltageUnits::volt);//Motion
    RightBackMotor.spin(forward, ForwardVolts - TurningVolts, voltageUnits::volt); //Motion

    //This is an example motor where voltage is used other than the drive base
    if (Controller1.ButtonR1.pressing()) { //controller input
      ExampleMotor.spin(forward, 12.0, voltageUnits::volt); //Motor is given 12V of power(motor forwards)
    }
    else if (Controller1.ButtonR2.pressing()) { //controller input
      ExampleMotor.spin(forward, -12.0, voltageUnits::volt); //Motor is given -12V of power(motor reverses)
    }
    else { //no input
      ExampleMotor.spin(forward, 0, voltageUnits::volt); //Motor is not given power
    }
    vex::task::sleep(20); //Slight delay so the Brain doesn't overprocess
  }
}
int main() { //main function of program
  pre_auton(); // Run the pre-autonomous function
  Competition.autonomous(autonomous);   // Set up callbacks for autonomous control period
  Competition.drivercontrol(usercontrol);   // Set up callbacks for driver control period
  // Prevent main from exiting with an infinite loop
  while (1) { //Loop forever
    vex::task::sleep(25); //Slight delay so the Brain doesn't overprocess
  }
}