#include <PS2X_lib.h>

#include <PS2X_lib.h>  //for v1.6
PS2X ps2x; // create PS2 Controller Class
const byte PS2_CLK = 13;
const byte PS2_CMD = 11;
const byte PS2_SEL = 10;
const byte PS2_DAT = 12;
const boolean PS2_PRESSURE = true;
const boolean PS2_RUMBLE = true;
const long BAUD_RATE = 9600;
int controllerStatus = 0; 
byte type = 0;
char  vibrate = 0;

typedef struct {
  char surge;
  char sway;
  char heave;
  char roll;
  char yaw;
  char pitch;
} MotionVector;
MotionVector subMotion = {0,0,0,0,0,0};


typedef struct {
  char pitch_bow;
  char pitch_stern;
  char yaw_port;
  char yaw_starboard;
  char roll_top;
  char roll_bottom;
} SixMotorControl;

SixMotorControl subMotors = {0,0,0,0,0,0};


enum {
  CONTROLLER_SUCCESS, 
  CONTROLLER_NOT_FOUND, 
  CONTROLLER_NOT_ACCEPTING_COMMANDS, 
  CONTROLLER_REFUSING_PRESSURES_MODE
} ControllerStatusCode;

enum {
  CONTROLLER_TYPE_UNKNOWN,
  CONTROLLER_TYPE_DUALSHOCK,
  CONTROLLER_TYPE_GUITARHERO
} ControllerTypeCode;


void setup(){
  Serial.begin(BAUD_RATE);
  controllerStatus = initializeControllers();
}


int initializeControllers() {
  int controllerResponse = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, PS2_PRESSURE, PS2_RUMBLE);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  switch(controllerResponse) {
  case CONTROLLER_SUCCESS :
    /*Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");*/
    type = ps2x.readType(); 
    switch(type) {
    case CONTROLLER_TYPE_UNKNOWN:
      //Serial.println("Unknown Controller type");
      break;
    case CONTROLLER_TYPE_DUALSHOCK:
      //Serial.println("DualShock Controller Found");
      break;
    case CONTROLLER_TYPE_GUITARHERO:
      //Serial.println("GuitarHero Controller Found");
      break;
    }
    break;
  case CONTROLLER_NOT_FOUND:
    //Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
    break;
  case CONTROLLER_NOT_ACCEPTING_COMMANDS:
    //Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
    break;
  case CONTROLLER_REFUSING_PRESSURES_MODE:
    //Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
    break;
  }



  return controllerResponse;
}


char mapToPercentageVector(byte value, boolean invert) {
  char newValue = value - 128;
  if(newValue == -128) newValue = -127;
  if(invert) newValue = -newValue;
  return newValue;
}

boolean calculateMotorSpeedsChanged() {
  SixMotorControl newMotors = {127,127,127,127,127,127};
  const float INVERTED = -1;
  const float NORMAL   = 1;
  const float DIAGONAL = 1; //sqrt(2)/2; // should be preprocessed into a good value
  
  boolean TRANSLATE = subMotion.heave || subMotion.surge || subMotion.heave;
  boolean ROTATE =    subMotion.pitch || subMotion.yaw   || subMotion.roll;
  const int numberOfMotors = sizeof(newMotors)/sizeof(SixMotorControl);
  if(TRANSLATE && ROTATE) {
    subMotion.surge /= 2;
    subMotion.sway  /= 2;
    subMotion.heave /= 2;
    subMotion.roll  /= 2;
    subMotion.yaw   /= 2;
    subMotion.pitch /= 2;
  }  
  //
  //                         Motor                  Vector       Modifier       Vector2       Modifier2
  motorDrivenByVectors(&newMotors.pitch_bow,     subMotion.pitch, NORMAL  , subMotion.heave, NORMAL*DIAGONAL  );
  motorDrivenByVectors(&newMotors.pitch_stern,   subMotion.pitch, INVERTED, subMotion.heave, NORMAL*DIAGONAL  );
  
  motorDrivenByVectors(&newMotors.yaw_port,      subMotion.yaw,   NORMAL  , subMotion.surge, NORMAL           );
  motorDrivenByVectors(&newMotors.yaw_starboard, subMotion.yaw,   INVERTED, subMotion.surge, NORMAL           );
  
  motorDrivenByVectors(&newMotors.roll_top,      subMotion.roll,  INVERTED, subMotion.sway,  INVERTED         );
  motorDrivenByVectors(&newMotors.roll_bottom,   subMotion.roll,  INVERTED, subMotion.sway,  NORMAL           );
  /*
  Serial.print("\tpitch_bow: ");      Serial.print(newMotors.pitch_bow, DEC);
  Serial.print("\tpitch_stern: ");    Serial.print(newMotors.pitch_stern, DEC); 
  Serial.print("\tyaw_port: ");       Serial.print(newMotors.yaw_port, DEC);
  Serial.print("\tyaw_starboard: ");  Serial.print(newMotors.yaw_starboard, DEC);  
  Serial.print("\troll_top: ");       Serial.print(newMotors.roll_top, DEC);
  Serial.print("\troll_bottom: ");    Serial.print(newMotors.roll_bottom, DEC);
  Serial.println();
  */
  
  boolean changed =   newMotors.pitch_bow      !=   subMotors.pitch_bow     ||
                      newMotors.pitch_stern    !=   subMotors.pitch_stern   ||
                      newMotors.yaw_port       !=   subMotors.yaw_port      ||
                      newMotors.yaw_starboard  !=   subMotors.yaw_starboard ||
                      newMotors.roll_top       !=   subMotors.roll_top      ||
                      newMotors.roll_bottom    !=   subMotors.roll_bottom; 
                      
                      
  subMotors = newMotors;
  return changed;
}

float motorDrivenByVectors(char* motor, char vectorValue1, float modifier1,  char vectorValue2, float modifier2) {
  *motor = vectorValue1*modifier1 + vectorValue2*modifier2;
}
void loop() {

  readController();
  if(calculateMotorSpeedsChanged())
    sendMotorSpeeds();
  
  delay(50);
}
void sendMotorSpeeds() {
  const byte SET_MOTOR_SPEEDS_COMMAND = 0xAB;
  Serial.write(SET_MOTOR_SPEEDS_COMMAND);
  Serial.write(subMotors.pitch_bow);
  Serial.write(subMotors.pitch_stern);
  Serial.write(subMotors.yaw_port);
  Serial.write(subMotors.yaw_starboard);
  Serial.write(subMotors.roll_top);
  Serial.write(subMotors.roll_bottom);
}

void readController() {
  if(controllerStatus != CONTROLLER_SUCCESS) {//skip loop if no controller found
    controllerStatus = initializeControllers();
    return; 
  }
  
  if(type == CONTROLLER_TYPE_DUALSHOCK) { //Guitar Hero Controller
    const boolean INVERTED = true;
    const boolean NORMAL   = false;
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    subMotion.surge = mapToPercentageVector(ps2x.Analog(PSS_LY), INVERTED); // move forwards/back
    subMotion.sway  = mapToPercentageVector(ps2x.Analog(PSS_LX), NORMAL); // strafe
    subMotion.roll  = mapToPercentageVector(ps2x.Analog(PSS_RX), NORMAL); // rotate left/right
    subMotion.yaw   = mapToPercentageVector(ps2x.Analog(PSS_RY), INVERTED); // rotate up/down
    
    subMotion.heave = mapToPercentageVector((ps2x.Analog(PSAB_R2)-1)/2 + 128 - ps2x.Analog(PSAB_L2)/2, false);
    subMotion.pitch = mapToPercentageVector((ps2x.Analog(PSAB_R1)-1)/2 + 128 - ps2x.Analog(PSAB_L1)/2, false);
    
    /*Serial.print("\tsurge: ");Serial.print(subMotion.surge, DEC);
    Serial.print("\tsway:  ");Serial.print(subMotion.sway, DEC); 
    Serial.print("\tpitch: ");Serial.print(subMotion.pitch, DEC);
    Serial.print("\tyaw:   ");Serial.print(subMotion.yaw, DEC);  
    Serial.print("\theave: ");Serial.print(subMotion.heave, DEC);
    Serial.print("\troll: ");Serial.print(subMotion.roll, DEC); 
    
    Serial.println();*/

  } else {
    //Serial.print("Invalid controller type");
  }
}
