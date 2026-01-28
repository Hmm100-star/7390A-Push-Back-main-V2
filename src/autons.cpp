#include "globals.hpp"
#include "autons.hpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/llemu.hpp"
#include "liblvgl/lvgl.h"
#include "pros/apix.h"
#include "pros/optical.h"
#include "pros/rtos.h"
#include "selector.hpp"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Helper to set initial pose based on routine
void RedLeft() {
  // chassis.setPose(-48, -48, 90); // Example starting pose
  // Add Red Left routine here
  pros::lcd::print(0, "Running Red Left");

  intake.move_velocity(600);
  MatchLoader.set_value(true);
  bool intakeCurrentReached = false;
  while (optical_sensor.get_rgb().red > 100 || optical_sensor.get_rgb().blue > 100) {
    left_motors.move_velocity(180);
    right_motors.move_velocity(180);
    pros::delay(20);
  }
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(200);
  /*
  left_motors.move_velocity(-150);
  right_motors.move_velocity(-150);
  pros::delay(1000);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  MatchLoader.set_value(false);
  */
}

void RedRight() {
  // chassis.setPose(-48, 48, 90); // Example starting pose
  // Add Red Right routine here
  pros::lcd::print(0, "Running Red Right");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void BlueLeft() {
  // chassis.setPose(48, 48, 270); // Example starting pose
  // Add Blue Left routine here
  pros::lcd::print(0, "Running Blue Left");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void BlueRight() {
  // Add Blue Right routine here
  bool intakeCurrentReached = false;
  while (intakeCurrentReached && (intake.get_current_draw() < 2200 || intake.get_current_draw() > 2300)) {
    left_motors.move_velocity(180);
    right_motors.move_velocity(180);
    if (intake.get_current_draw() > 2200 && intake.get_current_draw() < 2350) {
      intakeCurrentReached = true;
    } else {
      intakeCurrentReached = false;
    }
    pros::delay(20);
  }
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(200);
  left_motors.move_velocity(-150);
  right_motors.move_velocity(-150);
  pros::delay(1000);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  MatchLoader.set_value(false);
}

void Skills() {
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  
  chassis.setPose(0, 0, imu.get_heading());
  Descorer.set_value(true); // moves odom up to avoid interference w/ parking
  intake.move_velocity(600);
  // robot moves forward to intake blocks
  left_motors.move_velocity(20);
  right_motors.move_velocity(57);
  pros::delay(700);
  left_motors.move_velocity(75);
  right_motors.move_velocity(10);
  pros::delay(1300); 
  left_motors.move_velocity(10);
  right_motors.move_velocity(67);
  pros::delay(1000);
  left_motors.move_velocity(-140);
  right_motors.move_velocity(-155);
  pros::delay(1500);
  //robot waits to allow current to 0
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(200);
  int left_hit_velocity = 120;
  int right_hit_velocity = 120;
  while (left_motors.get_current_draw() < 1750 && right_motors.get_current_draw() < 1750) {
    if (left_motors.get_current_draw() > 1700) {
      left_hit_velocity = 20;
    }
    if (right_motors.get_current_draw() > 1700) {
      right_hit_velocity = 20;
    }
    left_motors.move_velocity(left_hit_velocity);
    right_motors.move_velocity(right_hit_velocity);
    pros::delay(20);
  }
  //left_motors.move_velocity(35);
  //right_motors.move_velocity(35);
  //pros::delay(1700);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  Descorer.set_value(false); // lowers odom back down for position tracking
  pros::delay(200);
  double h = imu.get_heading();                 // 0..360
  double err = fmod(h + 180.0, 360.0) - 180.0;  // -> [-180, 180)

if (fabs(err) <= 2) {
  chassis.setPose(
    (distance_sensor.get_distance() - 1700) / 25.4,
    0,
    0
  );
} else {
  pros::delay(5000);
}/*else {
  if (imu.get_heading() < 180) {
  // Facing "right" side
  chassis.setPose(
    cos(imu.get_heading()) * ((distance_sensor.get_distance() - 1700) / 25.4),
    0.2,
    imu.get_heading());
} else {
  // Facing "left" side
  chassis.setPose(cos(imu.get_heading()) * ((distance_sensor.get_distance() - 1700) / 25.4),
  180, 
  0.8);
  }
}*/
pros::delay(2000);
chassis.moveToPoint(0, -14, 3000, {.forwards = false});
intake.move_velocity(0);
chassis.turnToHeading(-45, 2000);
chassis.moveToPoint(22.5, -32.5, 3000, {.forwards = false});
chassis.turnToHeading(45, 1500);
chassis.moveToPose(3.2, -39.6, 45, 2000, {.forwards = false}, false);
MidGoal.set_value(true);
intake.move_velocity(520);
pros::delay(750);
left_motors.move_velocity(5);
right_motors.move_velocity(5);
pros::delay(100);
left_motors.move_velocity(0);
right_motors.move_velocity(0);
pros::delay(1400);
intake.move_velocity(0);
MidGoal.set_value(false); 
chassis.moveToPoint(51, 1.4, 2000, {.maxSpeed = 90}, false);
MatchLoader.set_value(true);
chassis.turnToHeading(0, 1500);
pros::delay(400);
chassis.cancelAllMotions();

left_motors.move_velocity(0);
right_motors.move_velocity(0);
pros::delay(200);
MatchLoader.set_value(false);

  //chassis.moveToPoint(18, -31, 4000);
  /*
  pros::delay(650);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(1000);
  left_motors.move_velocity(-160);
  right_motors.move_velocity(-160);
  pros::delay(1200);
  left_motors.move_velocity(15);
  right_motors.move_velocity(15);
  pros::delay(700);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(500);
  Descorer.set_value(false);

  chassis.setPose(0, 0, 0);
  chassis.moveToPose(0, -14, 0, 3000, {.forwards = false});
  intake.move_velocity(0);
  chassis.turnToHeading(-45, 2000);
  chassis.moveToPoint(18, -31, 4000);
  // IMPORTANT: stop any chassis control before raw motor control (if these exist in your LemLib)
  // chassis.cancelAllMotions();
  // chassis.stop();
 */
  // Now do your “if voltage > 10,000 mV, drive backwards” behavior safely:

intake.move_velocity(600);
MatchLoader.set_value(true);
pros::delay(500);
bool intakeReached = false;
while (!intakeReached) {
  left_motors.move_velocity(100);
  right_motors.move_velocity(100);
  if (left_motors.get_current_draw() > 1750 && right_motors.get_current_draw() > 1750) {
    intakeReached = true;
  }
  pros::delay(20);
  }
  bool blockCleared = false;
  while (!blockCleared && (optical_sensor.get_rgb().red > 50 || optical_sensor.get_rgb().blue > 50)) {
    right_motors.move_velocity(0);
    left_motors.move_velocity(0);
    if (optical_sensor.get_rgb().red < 50 && optical_sensor.get_rgb().blue < 50) {
      blockCleared = true;
    }
    pros::delay(80);
  }
  
}


void DoNothing() {
  // Do nothing
  pros::lcd::print(0, "Running Do Nothing");
  chassis.setPose(0,0,0);
  chassis.moveToPose(0, 5, 0,1000);
}

void TuneChassis() {
  // Set the pose to 0, 0, 0
  if (homeScreen != NULL) {
        lv_scr_load(homeScreen); 
    }
    
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, imu.get_heading());
  Descorer.set_value(true); // moves odom up to avoid interference w/ parking
  intake.move_velocity(600);
  left_motors.move_velocity(160);
  right_motors.move_velocity(160);
  pros::delay(1000);
  MatchLoader.set_value(true);
  pros::delay(1867);
  //robot waits to allow current to 0
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(500);
  int left_hit_velocity = 120;
  int right_hit_velocity = 120;
  while (left_motors.get_current_draw() < 1850 && right_motors.get_current_draw() < 1850) {
    if (left_motors.get_current_draw() > 1800) {
      left_hit_velocity = 20;
    }
    if (right_motors.get_current_draw() > 1800) {
      right_hit_velocity = 20;
    }
    left_motors.move_velocity(-left_hit_velocity);
    right_motors.move_velocity(-right_hit_velocity);
    pros::delay(20);
  }
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(400);
  Descorer.set_value(false); // lowers odom back down for position tracking
  chassis.setPose(
    (distance_sensor.get_distance() - 67) / 25.4,
    0,
    0
  );
  pros::delay(5000);
  double h = imu.get_heading();                 // 0..360
  double err = fmod(h + 180.0, 360.0) - 180.0;  // -> [-180, 180)

if (fabs(err) <= 2.2) {
  chassis.setPose(
    (distance_sensor.get_distance() - 1700) / 25.4,
    0,
    0
  );
} else {
  pros::delay(6700); // delays for 6.7 seconds for maximum efficiency
}

  chassis.moveToPoint(0, -14, 3000, {.forwards = false});
  intake.move_velocity(0);
  chassis.turnToHeading(-45, 2000);
  chassis.moveToPoint(22.5, -32.5, 3000, {.forwards = false});
  chassis.turnToHeading(45, 1500);
  chassis.moveToPose(11.9, -39.8, 45, 2000, {.forwards = false}, false);
  MidGoal.set_value(true);
  intake.move_velocity(520);
  pros::delay(750);
  left_motors.move_velocity(5);
  right_motors.move_velocity(5);
  pros::delay(100);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(1400);
  intake.move_velocity(0);
  MidGoal.set_value(false);
  chassis.moveToPoint(51, 1.4, 2000, {.maxSpeed = 80}, false);
  MatchLoader.set_value(true);
  chassis.turnToHeading(0, 1500);
  pros::delay(400);
  chassis.cancelAllMotions();
  intake.move_velocity(600);
  bool intakeCurrentReached = false;
  while (intakeCurrentReached && (intake.get_current_draw() < 2200 || intake.get_current_draw() > 2300)) {
    left_motors.move_velocity(180);
    right_motors.move_velocity(180);
    if (intake.get_current_draw() > 2200 && intake.get_current_draw() < 2350) {
      intakeCurrentReached = true;
    } else {
      intakeCurrentReached = false;
    }
    pros::delay(20);
  }
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(200);
 //I like toes - Jesse Chu
}
