#include "globals.hpp"
#include "autons.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/error.h"
#include "pros/misc.h"
#include "pros/llemu.hpp"
#include "liblvgl/lvgl.h"
#include "pros/apix.h"
#include "pros/motors.h"
#include "pros/optical.h"
#include "pros/rtos.h"
#include "selector.hpp"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Helper to set initial pose based on routine
void RedLeft() {
    if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, 0);
  intake.move_velocity(600);
  chassis.moveToPoint(0,24, 1200, {.maxSpeed = 99});
  pros::delay(400);
  MatchLoader.set_value(true);
  chassis.turnToHeading(-120, 770, {}, false);
  intake.move_velocity(0);
  chassis.moveToPoint(-30.8,5.6, 1500, {.maxSpeed = 80});
  chassis.turnToHeading(-170, 900);
  chassis.moveToPoint(-33.6, -2.9, 1300, {.maxSpeed = 60}, false);
  intake.move_velocity(600);
  chassis.cancelAllMotions();
  left_motors.move_velocity(40);
  right_motors.move_velocity(40); 
  pros::delay(500);
  left_motors.move_velocity(15);
  right_motors.move_velocity(15);
  pros::delay(800);
  intake.move_velocity(0);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  chassis.moveToPoint(-28.3, 26.8, 1500, {.forwards = false});
  LongGoal.set_value(true);
  pros::delay(267);
  intake.move_velocity(600);
  pros::delay(3300);
  LongGoal.set_value(false);
  intake.move_velocity(0);
  chassis.moveToPoint(-31.6, 8.5, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(-27.6, 31.2, 1800, {.forwards = false});
  
}

void RedRight() {
  
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, 0);
  intake.move_velocity(600);
  chassis.moveToPoint(0,24, 1250, {.maxSpeed = 99});
  pros::delay(400);
  MatchLoader.set_value(true);
  chassis.turnToHeading(120, 800, {}, false);
  intake.move_velocity(0);
  chassis.moveToPoint(30, 8.5, 1800, {.maxSpeed = 80});
  chassis.turnToHeading(170, 700);
  chassis.moveToPoint(33.9, -2.7, 1600, {.maxSpeed = 60}, false);
  intake.move_velocity(600);
  chassis.cancelAllMotions();
  left_motors.move_velocity(40);
  right_motors.move_velocity(40); 
  pros::delay(500);
  left_motors.move_velocity(15);
  right_motors.move_velocity(15);
  pros::delay(800);
  intake.move_velocity(0);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  chassis.moveToPoint(29, 28.4, 1500, {.forwards = false, .maxSpeed = 90});
  LongGoal.set_value(true);
  pros::delay(267);
  intake.move_velocity(600);
  pros::delay(3300);
  LongGoal.set_value(false);
  intake.move_velocity(0);
  chassis.moveToPoint(31.9, 5.2, 1500, {}, false);
  pros::delay(670);
  chassis.moveToPoint(29, 28.4, 1500, {.forwards = false});
}

void BlueLeft() {
  // chassis.setPose(48, 48, 270); // Example starting pose
  // Add Blue Left routine here
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, 0);
  //grabs 3 balls in front
  intake.move_velocity(600);
  chassis.moveToPoint(0,24, 1200, {.maxSpeed = 99});
  pros::delay(400);
  MatchLoader.set_value(true);
  // preps to matchload
  chassis.turnToHeading(-120, 770, {}, false);
  intake.move_velocity(0);
  chassis.moveToPoint(-30.8,5.6, 1500, {.maxSpeed = 80});
  chassis.turnToHeading(-170, 900);
  chassis.moveToPoint(-33.6, -2.9, 1300, {.maxSpeed = 60}, false);
  intake.move_velocity(600);
  chassis.cancelAllMotions();
  // matchloads the blocks
  left_motors.move_velocity(40);
  right_motors.move_velocity(40); 
  pros::delay(500);
  left_motors.move_velocity(15);
  right_motors.move_velocity(15);
  pros::delay(800);
  intake.move_velocity(0);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  // scores long goal
  chassis.moveToPoint(-28.3, 26.8, 1500, {.forwards = false});
  LongGoal.set_value(true);
  pros::delay(267);
  intake.move_velocity(600);
  pros::delay(3300);
  LongGoal.set_value(false);
  intake.move_velocity(0);
  // backs up and rams forward to ensure control zone
  chassis.moveToPoint(-31.6, 8.5, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(-27.6, 31.2, 1800, {.forwards = false});
  
}

void BlueRight() {
  // Add Blue Right routine here
  if (homeScreen != NULL) {
    lv_scr_load(homeScreen);
  }
  chassis.setPose(0, 0, 0);
  intake.move_velocity(600);
  chassis.moveToPoint(0,24, 1250, {.maxSpeed = 99});
  pros::delay(400);
  MatchLoader.set_value(true);
  chassis.turnToHeading(120, 800, {}, false);
  intake.move_velocity(0);
  chassis.moveToPoint(30, 8.5, 1800, {.maxSpeed = 80});
  chassis.turnToHeading(170, 700);
  chassis.moveToPoint(33.9, -2.7, 1600, {.maxSpeed = 60}, false);
  intake.move_velocity(600);
  chassis.cancelAllMotions();
  left_motors.move_velocity(40);
  right_motors.move_velocity(40); 
  pros::delay(500);
  left_motors.move_velocity(15);
  right_motors.move_velocity(15);
  pros::delay(800);
  intake.move_velocity(0);
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  chassis.moveToPoint(29, 28.4, 1500, {.forwards = false, .maxSpeed = 90});
  LongGoal.set_value(true);
  pros::delay(267);
  intake.move_velocity(600);
  pros::delay(3300);
  LongGoal.set_value(false);
  intake.move_velocity(0);
  chassis.moveToPoint(31.9, 5.2, 1500, {}, false);
  pros::delay(670);
  chassis.moveToPoint(29, 28.4, 1500, {.forwards = false});
}

void Skills() {
  // Homescreen setup
  if (homeScreen != NULL) {
        lv_scr_load(homeScreen); 
    }
    

  // Parking Zone routine
  chassis.setPose(0, 0, imu.get_heading());
  Descorer.set_value(true); // moves odom up to avoid interference w/ parking
  intake.move_velocity(600);
  left_motors.move_velocity(160);
  right_motors.move_velocity(160);
  pros::delay(2867);
  //robot waits to allow current to 0
  left_motors.move_velocity(0);
  right_motors.move_velocity(0);
  pros::delay(500);
  // bot reverses to touch parking zone for accurate Position tracking
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
  intake.move_velocity(0);
  pros::delay(400);
  Descorer.set_value(false); // lowers odom back down for position tracking
  // Sets bot pose aftrer exiting parking zone
  chassis.setPose(
    (distance_sensor.get_distance() - 67) / 25.4,
    0,
    0
  );

// Align to midgoal
chassis.swingToPoint(10 , 16, lemlib::DriveSide::RIGHT, 1000, {}, false);
chassis.turnToHeading(90, 1500);
intake.move_velocity(600);
chassis.moveToPoint(38, 8.55, 3000, {.maxSpeed = 70});
chassis.turnToHeading(-45, 900, {.maxSpeed = 60});
chassis.moveToPoint(57.3, -10, 2000, {.forwards = false, .maxSpeed = 55}, false);

// Midgoal scoring
MidGoal.set_value(true);
intake.move_velocity(500);
pros::delay(200);
chassis.moveToPoint(chassis.getPose().x - 1.2, chassis.getPose().y + 1.2, 1000, {.forwards= true, .maxSpeed = 100}, true);
pros::delay(1620);
intake.move_velocity(400);
pros::delay(1200);
intake.move_velocity(0);

// Prep to matchload
chassis.moveToPoint(23.8, 31, 1500, {.maxSpeed = 90});
MatchLoader.set_value(true);
MidGoal.set_value(false);
chassis.turnToHeading(-87.7, 1500);
chassis.moveToPoint(14, 32.4, 1000, {.maxSpeed = 100}, false);
intake.move_velocity(600);

// Reaches matchloader
bool intakeReached = false;
left_motors.move_velocity(120);
right_motors.move_velocity(120);
pros::delay(600);

// Clears matchloader
left_motors.move_velocity(10);
right_motors.move_velocity(10);
pros::delay(3000);

// Aligns to long goal
chassis.moveToPose(37, 46.5, -112, 1500, {.forwards = false});
chassis.turnToHeading(-90, 1000);
chassis.moveToPoint(92.7, 44.8, 5000, {.forwards = false, .maxSpeed = 100});
MatchLoader.set_value(false);
intake.move_velocity(0);
chassis.moveToPoint(125.3, 27.5, 2000, {.forwards = false, .maxSpeed = 72});
chassis.turnToHeading(90, 1200);

// Scores long goal
chassis.moveToPoint(96.3, 30, 1500, {.forwards = false}, false);
LongGoal.set_value(true);
intake.move_velocity(600);
pros::delay(3000);
LongGoal.set_value(false);

// Matchload
MatchLoader.set_value(true);
pros::delay(120);
chassis.moveToPose(chassis.getPose().x + 22.8, 30, 90, 1500, {.maxSpeed = 80}, false);
chassis.cancelAllMotions();
left_motors.move_velocity(120);
right_motors.move_velocity(120);
pros::delay(600);
left_motors.move_velocity(10);
right_motors.move_velocity(10);
pros::delay(3000);

// Score long goal again
chassis.moveToPoint(96.3, 30, 1500, {.forwards = false}, false);
LongGoal.set_value(true);
intake.move_velocity(600);
pros::delay(2400);
LongGoal.set_value(false);
pros::delay(200);

// Align to matchload 3
chassis.moveToPoint(108.0, 30, 1000);
chassis.turnToHeading(180, 670);
chassis.moveToPoint(chassis.getPose().x, -70, 1000);
chassis.turnToHeading(90, 670);
chassis.moveToPoint(118.6, -69.8, 4000);
chassis.cancelAllMotions();

// Matchload 3
left_motors.move_velocity(120);
right_motors.move_velocity(120);
pros::delay(600);
left_motors.move_velocity(10);
right_motors.move_velocity(10);
pros::delay(3000);

// Align to long goal 3
chassis.moveToPoint(96.3, -70, 1500, {.forwards = false}, false);
LongGoal.set_value(true);
intake.move_velocity(600);
pros::delay(2000);
LongGoal.set_value(false);
}


void DoNothing() {
  // Do nothing
  pros::lcd::print(0, "Running Do Nothing");
  chassis.setPose(0,0,0);
  chassis.moveToPose(0, 5, 0,1000);
}


// Starts without initial configuration
void TuneChassis() {
 
  
}

