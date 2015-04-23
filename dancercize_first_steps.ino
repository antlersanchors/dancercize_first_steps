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

void setup(){
  Music.init();
  Music.setFrequency1(200);
  Music.setFrequency2(250);
  Music.setFrequency3(300);  
  
  MotorA.init();
  
  Serial.begin(9600);
  slider1_x = analogRead(A1); // initialize x
  slider2_x = analogRead(A9);
}

void loop(){
  
  slider(1);
  // slider(2);

}

void slider(int sl_num){
  
  int num = sl_num;
  
  slider[num]_xold = slider[num]_x;
  slider[num]_x =  analogRead(A1);

if (((slider[num]_xold <= 125) && (slider[num]_x > 125)) || ((slider[num]_xold >= 125) && (slider[num]_x < 125))){
  Music.setGain1(1.0f);
  Music.setFrequency1(293);
}
if (((slider[num]_xold <= 375) && (slider[num]_x > 375)) || ((slider[num]_xold >= 375) && (slider[num]_x < 375))){
  Music.setGain2(1.0f);
  Music.setFrequency2(349);
}
if (((slider[num]_xold <= 625) && (slider[num]_x > 625)) || ((slider[num]_xold >= 625) && (slider[num]_x < 625))){
  Music.setGain3(1.0f);
  Music.setFrequency3(440);
}
if (((slider[num]_xold <= 875) && (slider[num]_x > 875)) || ((slider[num]_xold >= 875) && (slider[num]_x < 875))){
  Music.setGain1(1.0f);
  Music.setFrequency1(466);
  }
  else{
    Music.setGain1(0.9995f*Music.getGain1());
    Music.setGain2(0.9995f*Music.getGain2());
    Music.setGain3(0.9995f*Music.getGain3());
  }
  


  slider[num]_xt = slider[num]_x % 250; //same force for each 250 ranage
  slider[num]_F = 0;
  if (slider[num]_xt > 60) slider[num]_F = - K * (slider[num]_xt - 60);
  if (slider[num]_xt > 80) slider[num]_F = - K * (100 - slider[num]_xt);
  if (slider[num]_xt > 120) slider[num]_F =  K * (140 - slider[num]_xt);
  if (slider[num]_xt > 140) slider[num]_F = 0;
  
  MotorA.torque(slider[num]_F);
  
  
  
}
    
