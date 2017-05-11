#include <Stepper.h>
const int stepsPerRevolution = 360;
const int ldrmin1=50, ldrmax1=600, ldrmin2=100, ldrmax2=800;
//const int stepsize=1;
int powerckt=2;
int pirsensor=4, streetldr=A0;
int sunldr1=A1, sunldr2=A2, sunldr3=A3;
int sled=3, pled=5;
int statled=7;
int fade=5;
Stepper myStepper1(stepsPerRevolution, 8,9,10,11);
Stepper myStepper2(stepsPerRevolution, 11,10,9,8);
int pir, sldr, ldr1, ldr2, ldr3 , power;
int bright=0;
int i, c, d;

void setup()
{
  pinMode(powerckt, INPUT);
  pinMode(pirsensor, INPUT);
  pinMode(sled, OUTPUT);
  pinMode(pled, OUTPUT);
  pinMode(statled, OUTPUT);
}

void loop()
{
  power=digitalRead(powerckt);
  pir=digitalRead(pirsensor);
  sldr=analogRead(streetldr);
  ldr1=analogRead(sunldr1);
  ldr2=analogRead(sunldr2);
  ldr3=analogRead(sunldr3);
  
  if (power==LOW)
  {
    //start of pir and pedestrial street light
    analogWrite(pled, 25);
    analogWrite(sled, 25);
    if (pir==HIGH)
    {
      digitalWrite(pled, HIGH);
    }
    else
    {
//      digitalWrite(pled, LOW);
//      delay(30);
      analogWrite(pled, 25);
    }
    //end of pir and pedestrial street light
    
    //start of streetldr and street light
    if (sldr>ldrmin1)
    {
      if (sldr<ldrmax1)
      {
        bright=255*(sldr/ldrmax1);
        analogWrite(sled, bright);
     //   delay (30);
      }
      else if (sldr>ldrmax1)
      {
      digitalWrite(sled, HIGH);
      }
    }
    //end of streetldr and street light
    
    
  }
  else if (power==HIGH)
  {
    digitalWrite(pled, LOW);
    digitalWrite(sled, LOW);
    //start of solar ldr stepper
    if (ldr1>ldr2)
    {
      myStepper1.step(1);
      delay (100);
    }
    else if (ldr3>ldr2)
    {
      myStepper2.step(1);
      delay (100);
    }
  }
    //end of solar ldr stepper
}
