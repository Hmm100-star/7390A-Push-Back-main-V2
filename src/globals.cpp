#include "globals.hpp"
#include "lemlib/api.hpp"
#include "pros/optical.hpp"

//
// ===================== MOTORS =====================
//
pros::MotorGroup left_motors({-1, -2, -3}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({8, 9, 10}, pros::MotorGearset::blue);
pros::MotorGroup intake({20, -21}, pros::MotorGearset::blue);

//
// ===================== SENSORS =====================
//
pros::Imu imu(6);
pros::Optical optical_sensor(16);
pros::Rotation horizontal_sensor(5);
pros::Rotation vertical_sensor(-7);
pros::Distance distance_sensor(17);

//
// ===================== TRACKING WHEELS =====================
//
lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizontal_sensor,
    lemlib::Omniwheel::NEW_2,
    -2.4
);

lemlib::TrackingWheel vertical_tracking_wheel(
    &vertical_sensor,
    lemlib::Omniwheel::NEW_2,
    0.1
);

//
// ===================== ODOMETRY =====================
//
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,   // vertical wheel
    nullptr,                    // no second vertical wheel
    &horizontal_tracking_wheel, // horizontal wheel
    nullptr,                    // no second horizontal wheel
    &imu
);

//
// ===================== DRIVETRAIN =====================
//
lemlib::Drivetrain drivetrain(
    &left_motors,
    &right_motors,
    12.75,                     // track width (in)
    lemlib::Omniwheel::NEW_275, // wheel type
    450,                       // RPM
    2                          // horizontal drift
);

//
// ===================== PID CONTROLLERS =====================
//
lemlib::ControllerSettings lateral_controller(
    9,    // Kp
    0,      // kI
    2.3,   // kD
    3,     // anti-windup
    0.5,    // small error range
    100,   // small error timeout
    3,      // large error range
    500,    // large error timeout
    12 //slew
);

lemlib::ControllerSettings angular_controller(2.125, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              11.75, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
//
// ===================== DRIVE CURVES =====================
//
lemlib::ExpoDriveCurve throttle_curve(
    3,      // deadband
    10,     // min output
    1.019   // expo
);

lemlib::ExpoDriveCurve steer_curve(
    3,
    10,
    1.035  
);

//
// ===================== CHASSIS =====================
//
lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors,
    &throttle_curve,
    &steer_curve
);

//
// ===================== PNEUMATICS =====================
//
pros::adi::DigitalOut LongGoal('A');
pros::adi::DigitalOut MidGoal('B');
pros::adi::DigitalOut MatchLoader('C');
pros::adi::DigitalOut Descorer('D');

//
// ===================== STATE VARIABLES =====================
//
bool LongGoalFlap = false;
bool MidGoalFlap = false;
bool MatchLoaderFlap = false;
bool DescorerFlap = false;
