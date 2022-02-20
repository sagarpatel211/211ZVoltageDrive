# 211ZVoltageDrive
This repository is used for controlling the robot using voltage value instead of percentages and driving with adjustable turning intensity! This allows more freedom for the driver so they can select their preferred setting.


## Table of Contents
* [Dependencies](#dependencies)
* [Installation](#installation)
* [Features](#features)
* [Contributors](#contributors)
* [Contact](#contact)


## Dependencies
[VexCode Pro V5 Text 2.0.0 or later](https://www.vexrobotics.com/vexcode-download)


## Installation
* Make sure all the dependencies are installed
* Download the files
  * Option 1: 🍴 Fork this repository!
  * Option 2: 🧪 Clone the repository to your local machine using https://github.com/sagarpatel211/211ZVoltageDrive.git!
* Open *211Z_Voltage_Driver.v5code* in VexCode to open the program
* Download the program to the brain by connecting the V5 Brain or controller to the device via micro-USB and select *download*. In both options, the V5 Brain must be on!
* Run the program by selecting it from the V5 Brain or pressing the *play* button in VexCode **if** the V5 Brain or controller is attached to the device via micro-USB.


## Features
* Drive base control with voltage
```
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
```
* Example motors controlled by voltage
```
if (Controller1.ButtonR1.pressing()) { //controller input
  ExampleMotor.spin(forward, 12.0, voltageUnits::volt); //Motor is given 12V of power(motor forwards)
}
else if (Controller1.ButtonR2.pressing()) { //controller input
  ExampleMotor.spin(forward, -12.0, voltageUnits::volt); //Motor is given -12V of power(motor reverses)
}
else { //no input
  ExampleMotor.spin(forward, 0, voltageUnits::volt); //Motor is not given power
}
```


## Contributors
| <a href="https://github.com/sagarpatel211" target="_blank">**Sagar Patel**</a> |
| :---: |
| [![Sagar Patel](https://avatars1.githubusercontent.com/u/34544263?s=200)](https://github.com/sagarpatel211)    |
| <a href="https://github.com/sagarpatel211" target="_blank">`github.com/sagarpatel211`</a> |


## Contact
[Email](mailto:sa24pate@uwaterloo.ca) | [Website](https://sagarpatel211.github.io/)
