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
  left_motors.move_velocity(20);
  right_motors.move_velocity(50);
  pros::delay(700);
  left_motors.move_velocity(75);
  right_motors.move_velocity(10);
  pros::delay(1300); 
  left_motors.move_velocity(10);
  right_motors.move_velocity(60);
  pros::delay(1000);
  left_motors.move_velocity(-120);
  right_motors.move_velocity(-177);
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
      right_hit_velocity = 120;
    }
    if (right_motors.get_current_draw() > 1700) {
      right_hit_velocity = 20;
      left_hit_velocity = 120;
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
  chassis.setPose((distance_sensor.get_distance() - 1700) / 25.4, 0, 0 );
  chassis.moveToPoint(0, -14, 3000, {.forwards = false});
  intake.move_velocity(0);
  chassis.turnToHeading(-45, 2000);
  chassis.moveToPoint(19, -33.2, 3000, {.forwards = false});
  chassis.turnToHeading(45, 1500);
  chassis.moveToPose(8.9, -39.9, 45, 2000, {.forwards = false}, false);
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
  chassis.moveToPoint(49, 1.4, 2000, {.maxSpeed = 80}, false);
  MatchLoader.set_value(true);
  chassis.turnToHeading(0, 1500);
  pros::delay(200);
  left_motors.move_velocity(600);
  right_motors.move_velocity(600);
  intake.move_velocity(600);

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
