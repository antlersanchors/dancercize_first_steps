//plucks - four bumps
//three notes (400,500,600hz)
//can't get Music.setGain1, etc to work only Music.setGain() starts all of them.

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

int slider1_x, slider1_xold, slider1_xt, F; // input position x, output force F
int slider2_x, slider2_xold, slider2_xt, F; // input position x, output force F

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
  slider(2);
  
  slider1_xold = slider1_x;
  slider1_x =  analogRead(A1);
  
  slider2_xold = slider2_x;
  slider2_x =  analogRead(A9);

if (((slider1_xold <= 125) && (slider1_x > 125)) || ((slider1_xold >= 125) && (slider1_x < 125))){
  Music.setGain1(1.0f);
  Music.setFrequency1(293);
}
if (((slider1_xold <= 375) && (slider1_x > 375)) || ((slider1_xold >= 375) && (slider1_x < 375))){
  Music.setGain2(1.0f);
  Music.setFrequency2(349);
}
if (((slider1_xold <= 625) && (slider1_x > 625)) || ((slider1_xold >= 625) && (slider1_x < 625))){
  Music.setGain3(1.0f);
  Music.setFrequency3(440);
}
if (((slider1_xold <= 875) && (slider1_x > 875)) || ((slider1_xold >= 875) && (slider1_x < 875))){
  Music.setGain1(1.0f);
  Music.setFrequency1(466);
  }
  else{
    Music.setGain1(0.9995f*Music.getGain1());
    Music.setGain2(0.9995f*Music.getGain2());
    Music.setGain3(0.9995f*Music.getGain3());
  }
  


  slider1_xt = slider1_x % 250; //same force for each 250 ranage
  F = 0;
  if (slider1_xt > 60) F = - K * (slider1_xt - 60);
  if (slider1_xt > 80) F = - K * (100 - slider1_xt);
  if (slider1_xt > 120) F =  K * (140 - slider1_xt);
  if (slider1_xt > 140) F = 0;
  MotorA.torque(F);
  
 
 // print every 256 cycles
  if(count++==0){
    Serial.print(x);
    Serial.print(" ");
    Serial.print(xt);
    Serial.print(" ");
    Serial.println(F);
  }

}

void slider(int slider_number){
  
}
    
