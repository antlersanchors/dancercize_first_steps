//plucks - four bumps
//three notes (400,500,600hz)
//can't get Music.setGain1, etc to work only Music.setGain() starts all of them.

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int slider1_x, slider1_xold, slider1_xt, slider1_F; // input position x, output force F
int slider2_x, slider2_xold, slider2_xt, slider2_F; // input position x, output force F

int K = 10; // slope constant
byte count; //for print count-down

// new stuff for timing and comparison
int step_pos1;
int step_pos2;
int last_pos1;
int last_pos2;

boolean stepped = false;
int time_limit = 1000;
int start_timer = 0;
boolean out_of_sync = false;

void setup() {
  Music.init();
  Music.setFrequency1(200);
  Music.setFrequency2(250);
  Music.setFrequency3(300);

  MotorA.init();

  Serial.begin(9600);
  slider1_x = analogRead(A1); // initialize x
  slider2_x = analogRead(A9);
}

void loop() {

  slider1();
  slider2();
  check_pos();

}

void check_pos() {

  if (step_pos1 != last_pos1 && step_pos1 != 0 || step_pos2 != last_pos2 && step_pos2 != 0 && stepped == false) { // if there is a change and we are not static, and one has not already stepped

    stepped = true;  // say a step has happened
    start_timer = millis();

  }

  if (stepped = true) {
    if (millis() - start_timer >= time_limit) { // if more than the allowed time has passed...
      Serial.println("DANCE FAIL!");
    }

    if (step_pos1 == step_pos2) {
      stepped == false; // if we are now on the same position, the step is complete
    }
  }

  last_pos1 = step_pos1;
  last_pos2 = step_pos2;

}

void late() {

}

void slider1() {

  slider1_xold = slider1_x;
  slider1_x = analogRead(A1);

  if (((slider1_xold <= 125) && (slider1_x > 125)) || ((slider1_xold >= 125) && (slider1_x < 125))) {
    Music.setGain1(1.0f);
    Music.setFrequency1(293);

    step_pos1 = 1;
  }
  if (((slider1_xold <= 375) && (slider1_x > 375)) || ((slider1_xold >= 375) && (slider1_x < 375))) {
    Music.setGain2(1.0f);
    Music.setFrequency2(349);

    step_pos1 = 2;
  }
  if (((slider1_xold <= 625) && (slider1_x > 625)) || ((slider1_xold >= 625) && (slider1_x < 625))) {
    Music.setGain3(1.0f);
    Music.setFrequency3(440);

    step_pos1 = 3;
  }
  if (((slider1_xold <= 875) && (slider1_x > 875)) || ((slider1_xold >= 875) && (slider1_x < 875))) {
    Music.setGain1(1.0f);
    Music.setFrequency1(466);

    step_pos1 = 4;
  }
  else {
    Music.setGain1(0.9995f * Music.getGain1());
    Music.setGain2(0.9995f * Music.getGain2());
    Music.setGain3(0.9995f * Music.getGain3());

    step_pos1 = 0;
  }

  slider1_xt = slider1_x % 250; //same force for each 250 ranage
  slider1_F = 0;
  if (slider1_xt > 60) slider1_F = - K * (slider1_xt - 60);
  if (slider1_xt > 80) slider1_F = - K * (100 - slider1_xt);
  if (slider1_xt > 120) slider1_F =  K * (140 - slider1_xt);
  if (slider1_xt > 140) slider1_F = 0;
  MotorA.torque(slider1_F);

}

void slider2() {

  slider2_xold = slider2_x;
  slider2_x =  analogRead(A9);

  if (((slider2_xold <= 125) && (slider2_x > 125)) || ((slider2_xold >= 125) && (slider2_x < 125))) {
    Music.setGain1(1.0f);
    Music.setFrequency1(293);

    step_pos2 = 1;
  }
  if (((slider2_xold <= 375) && (slider2_x > 375)) || ((slider2_xold >= 375) && (slider2_x < 375))) {
    Music.setGain2(1.0f);
    Music.setFrequency2(349);

    step_pos2 = 2;
  }
  if (((slider2_xold <= 625) && (slider2_x > 625)) || ((slider2_xold >= 625) && (slider2_x < 625))) {
    Music.setGain3(1.0f);
    Music.setFrequency3(440);

    step_pos2 = 3;
  }
  if (((slider2_xold <= 875) && (slider2_x > 875)) || ((slider2_xold >= 875) && (slider2_x < 875))) {
    Music.setGain1(1.0f);
    Music.setFrequency1(466);

    step_pos2 = 4;
  }
  else {
    Music.setGain1(0.9995f * Music.getGain1());
    Music.setGain2(0.9995f * Music.getGain2());
    Music.setGain3(0.9995f * Music.getGain3());

    step_pos2 = 0;
  }

  slider2_xt = slider2_x % 250; //same force for each 250 ranage
  slider2_F = 0;
  if (slider2_xt > 60) slider2_F = - K * (slider2_xt - 60);
  if (slider2_xt > 80) slider2_F = - K * (100 - slider2_xt);
  if (slider2_xt > 120) slider2_F =  K * (140 - slider2_xt);
  if (slider2_xt > 140) slider2_F = 0;
  MotorA.torque(slider2_F);

}

