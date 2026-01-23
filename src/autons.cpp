#include "globals.hpp"
#include "autons.hpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/llemu.hpp"
#include "liblvgl/lvgl.h"
#include "pros/apix.h"
#include "selector.hpp"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Helper to set initial pose based on routine
void RedLeft() {
  // chassis.setPose(-48, -48, 90); // Example starting pose
  // Add Red Left routine here
  pros::lcd::print(0, "Running Red Left");

  // Debug: Print to controller
  pros::Controller controller(pros::E_CONTROLLER_MASTER);
  controller.print(2, 0, "Running RedLeft");

  // Debug: Move motors directly to verify connection

  chassis.setPose(0, 0, 0);
  chassis.moveToPose(-100.0f, -100.0f, 10.0f, 100000);
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
  // chassis.setPose(48, -48, 270); // Example starting pose
  // Add Blue Right routine here
  pros::lcd::print(0, "Running Blue Right");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void Skills() {
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, 0);
  Descorer.set_value(true); // moves odom up to avoid interference w/ parking
  intake.move_velocity(600);
  // robot moves forward to intake blocks
  left_motors.move_velocity(35);
  right_motors.move_velocity(35);
  pros::delay(500);
  left_motors.move_velocity(10);
  right_motors.move_velocity(16);
    pros::delay(1000);
  left_motors.move_velocity(34);
  right_motors.move_velocity(30);
  pros::delay(1600);
  left_motors.move_velocity(-200);
  right_motors.move_velocity(-200);
  pros::delay(300);

  // move forward until hitting the park zone
  int left_hit_velocity = 70;
  int right_hit_velocity = 70;
  while (left_motors.get_current_draw() < 1500 && right_motors.get_current_draw() < 1500) {
    if (left_motors.get_current_draw() > 1500) {
      left_hit_velocity = 20;
    }
    if (right_motors.get_current_draw() > 1500) {
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
  chassis.setPose((distance_sensor.get_distance() - 1700) / 25.4, 0, imu.get_heading());
  chassis.moveToPoint(0, -14, 3000, {.forwards = false});
  intake.move_velocity(0);
  chassis.turnToHeading(-45, 2000);
  chassis.moveToPoint(19.3, -31, 3000, {.forwards = false});
  chassis.turnToHeading(42.6, 1500);
  chassis.moveToPose(8.7, -39, 40.7, 2000, {.forwards = false}, false);
  MidGoal.set_value(true);
  intake.move_velocity(520);
  pros::delay(3000);
  intake.move_velocity(0);
  MidGoal.set_value(false);
  chassis.moveToPoint(50.6, 2.4, 2000);
  MatchLoader.set_value(true);
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
  i call my girlfriend mommy - Christian Tan
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
    
  chassis.setPose(0,0,0);
  chassis.moveToPoint(0,20,10000);
  chassis.setPose(0,0,0);
  pros::delay(5000);
chassis.turnToHeading(90,10000);
pros::delay(5000);
chassis.setPose(0,0,0);
  chassis.moveToPose(-5, 38, -15, 10000, {.forwards = true});
}
