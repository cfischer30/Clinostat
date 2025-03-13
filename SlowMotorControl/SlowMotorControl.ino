/*  Program for very slow quasi-continuous motion below the stall speed of the motor.
Chris Fischer
March 13, 2025
Clinostat control program
Controls two motors with different cycle durations.

Pulse duration sets the "on" time for each motor, in milliseconds
Cycle duration sets the total time from the "on" of one pulse, to the "on" of the next pulse.


*/
#include <LiquidCrystal_I2C.h>

#define m1En 6
#define m2En 5
#define m1Dir 8
#define m2Dir 7

#define sp1in "A2"
#define sp2in "A3"

#define PWM 150

int sp1Delay, sp2Delay;
int sp1SecPerRev, sp2SecPerRev;
float pulseDuration = 100;   //milliseconds
float cycleDuration1 = 3000;
float cycleDuration2 = 3000;  //milliseconds
float delayDuration1, delayDuration2;

long int offTime1, onTime1, tnow;
long int offTime2, onTime2;
int is1on, is2on;





void setup() {
  pinMode(m1En, OUTPUT);
  pinMode(m2En, OUTPUT);
  pinMode(m1Dir, OUTPUT);
  pinMode(m2Dir, OUTPUT);
  pinMode(sp1in, INPUT);
  pinMode(sp2in, INPUT);
  analogWrite(m1En, PWM);
  analogWrite(m2En, PWM);
  offTime1 = millis();
  onTime1 = millis();
  offTime2 = millis();
  onTime2 = millis();
  //digitalWrite(m1Dir, HIGH);
  //digitalWrite(m2Dir, HIGH);
  //digitalWrite(m2Dir, HIGH);
  delay(3000);
 // digitalWrite(m1Dir, LOW);
  is1on = 1;
  is2on = 1;
 

}

void loop() {
  delayDuration1 = cycleDuration1 - pulseDuration;
  delayDuration2 = cycleDuration2 - pulseDuration;
  tnow = millis();
 
  if((tnow > (offTime1 + delayDuration1)) && (is1on == 0)){
    digitalWrite(m1Dir, HIGH); 
    onTime1 = millis();
    is1on = 1;
  }
  if((tnow > (pulseDuration+onTime1))&& (is1on == 1)){
    digitalWrite(m1Dir, LOW);
    offTime1 = millis();
    is1on = 0;
  }

   if((tnow > (offTime2 + delayDuration2)) && (is2on == 0)){
    digitalWrite(m2Dir, HIGH); 
    onTime2 = millis();
    is2on = 1;
  }
  if((tnow > (pulseDuration+onTime2))&& (is2on == 1)){
    digitalWrite(m2Dir, LOW);
    offTime2 = millis();
    is2on = 0;
  }
  

}
