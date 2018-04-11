#include <PS2X_lib.h>  //for v1.6
#include <Wire.h>
/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
#define pressures   true
//#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class


bool State = false;  
//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
 
  Serial.begin(9600);
  Wire.begin();
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successfully ");
    Serial.println("Try out all the buttons");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 1:
      Serial.println("MizuchyVody09水島 Cockpit Controller Ready");
      Serial.println("MizuchyVody09水島 Systems all green");
      break;
   }
}

void loop() {
  if(error == 1) //skip loop if no controller found
    return; 
  else { //DualShock Controller
    ps2x.read_gamepad(true, vibrate); //read controller and set large motor to spin at 'vibrate' speed

// while you are pressing the button, the there will be output

    if (ps2x.ButtonPressed(PSB_START)){
      if (State == true){
      Wire.beginTransmission(5);
      Wire.write('O');
      Wire.endTransmission();
      State = false;
    } else if (State == false){
      Wire.beginTransmission(5);
      Wire.write('o');
      Wire.endTransmission();
      State = true;
    }
    }
    
    if(ps2x.Button(PSB_PAD_UP)) {      
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      Wire.beginTransmission(5);
      Wire.write('F');
      Wire.write(ps2x.Analog(PSAB_PAD_UP));
      Wire.endTransmission();
    }
    else if(ps2x.ButtonReleased(PSB_PAD_UP)) {      
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      Wire.beginTransmission(5);
      Wire.write('f');
      Wire.write(0);
      Wire.endTransmission();
    }


    
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      Wire.beginTransmission(5);
      Wire.write('B');
      Wire.endTransmission();
    } else if(ps2x.ButtonReleased(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      Wire.beginTransmission(5);
      Wire.write('b');
      Wire.write(0);
      Wire.endTransmission();
    }   


    
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      Wire.beginTransmission(5);
      Wire.write('R');
      Wire.endTransmission();
    } else if(ps2x.ButtonReleased(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      Wire.beginTransmission(5);
      Wire.write('r');
      Wire.write(0);
      Wire.endTransmission();
    }


    
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      Wire.beginTransmission(5);
      Wire.write('L');
      Wire.endTransmission();
    } else if(ps2x.ButtonReleased(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      Wire.beginTransmission(5);
      Wire.write('l');
      Wire.write(0);
      Wire.endTransmission();
    }

    if(ps2x.Button(PSB_R2)){
      Wire.beginTransmission(5);
      Wire.write('U');
      Wire.write(ps2x.Analog(PSB_R2));
      Wire.endTransmission();
    } else if(ps2x.ButtonReleased(PSB_R2)){
      Wire.beginTransmission(5);
      Wire.write('u');
      Wire.write(0);
      Wire.endTransmission();
    }
    
    if(ps2x.Button(PSB_L2)){
      Wire.beginTransmission(5);
      Wire.write('D');
      digitalWrite(7,HIGH);
      Wire.write(ps2x.Analog(PSB_L2));
      Wire.endTransmission();
    } else if(ps2x.ButtonReleased(PSB_L2)){
      Wire.beginTransmission(5);
      Wire.write('d');
      Wire.write(0);
      Wire.endTransmission();
    }

  }
  delay(50);  
}
