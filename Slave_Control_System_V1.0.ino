//i2c Slave Code(Leonardo)
#include <Wire.h>
#include <Servo.h>

Servo M1,M2,M3,M4,M5;

bool State = false;
int Lights = 6;

void setup()
{
  int val ;
  Wire.begin(5);
  Wire.onReceive(Potentiometer);
  
  M1.attach(0);
  M2.attach(1);
  M3.attach(2);
  M4.attach(3);
  M5.attach(4);
  
  pinMode(Lights, OUTPUT);
  digitalWrite(Lights,State);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  
  M1.writeMicroseconds(1000);
  M2.writeMicroseconds(1000);
  M3.writeMicroseconds(1000);
  M4.writeMicroseconds(1000);
  M5.writeMicroseconds(1000);
  
  Serial.begin(9600);
}

void loop()
{
}

void Potentiometer(int howMany)
{
  while(Wire.available())
  {
    char command = Wire.read();
      if (command == 'O'){
        digitalWrite(Lights,HIGH);
      }
      if (command == 'o'){
        digitalWrite(Lights,LOW);
    }
   

    int Speed = Wire.read();
    Speed=map(Speed, 0, 1023, 1000, 2000);
    if (command == 'U'){
      digitalWrite(7,HIGH);
      M5.writeMicroseconds(Speed);
    }
     if (command == 'u'){
      M5.writeMicroseconds(Speed);
    }
    if (command == 'D'){
      digitalWrite(7,LOW);
      M5.writeMicroseconds(Speed);
      }
     if (command == 'd'){
      M5.writeMicroseconds(Speed);
    }
    if (command == 'F'){
      M3.writeMicroseconds(Speed);
      Serial.println('F');
      M4.writeMicroseconds(2000);
    }
     if (command == 'f'){
      M3.writeMicroseconds(1000);
      Serial.println('f');
      M4.writeMicroseconds(1000);
    }
    if (command == 'B'){
      M1.writeMicroseconds(2000);
      M2.writeMicroseconds(2000);
    }
     if (command == 'b'){
      M1.writeMicroseconds(1000);
      M2.writeMicroseconds(1000);
    }
    if (command == 'L'){
      M1.writeMicroseconds(2000);
      M4.writeMicroseconds(2000);
    }
     if (command == 'l'){
      M1.writeMicroseconds(1000);
      M4.writeMicroseconds(1000);
    }
    if (command == 'R'){
      M3.writeMicroseconds(2000);
      M2.writeMicroseconds(2000);
    }
     if (command == 'r'){
      M3.writeMicroseconds(1000);
      M2.writeMicroseconds(1000); 
    }
  
  }
  }

