#include <PS2X_lib.h>

#include <PS2X_lib.h>  //for v1.6
PS2X ps2x; // create PS2 Controller Class

enum {
  MODE_DEBUG_VERBOSE,
  MODE_RELEASE_BINARY
} BuildMode;

const byte BUILD_MODE = MODE_DEBUG_VERBOSE;

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
  signed char surge;
  signed char sway;
  signed char heave;
  signed char roll;
  signed char yaw;
  signed char pitch;
} MotionVector;
MotionVector subMotion = {0,0,0,0,0,0};


typedef struct {
  signed char pitch_bow;
  signed char pitch_stern;
  signed char yaw_port;
  signed char yaw_starboard;
  signed char roll_top;
  signed char roll_bottom;
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
  
  //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
  int controllerResponse = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, 
                           PS2_DAT, PS2_PRESSURE, PS2_RUMBLE);   

  switch(controllerResponse) {
  case CONTROLLER_SUCCESS :

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

  motorsDrivenByVectors(&newMotors.pitch_bow, &newMotors.pitch_stern, 
    subMotion.pitch, NORMAL, INVERTED, subMotion.heave, NORMAL, NORMAL);

  motorsDrivenByVectors(&newMotors.yaw_port, &newMotors.yaw_starboard, 
    subMotion.yaw, NORMAL, INVERTED, subMotion.surge, NORMAL, NORMAL);

  motorsDrivenByVectors(&newMotors.roll_top, &newMotors.roll_bottom, 
    subMotion.roll, INVERTED, INVERTED, subMotion.sway, INVERTED, NORMAL);

  
  boolean changed =   newMotors.pitch_bow      !=   subMotors.pitch_bow     ||
                      newMotors.pitch_stern    !=   subMotors.pitch_stern   ||
                      newMotors.yaw_port       !=   subMotors.yaw_port      ||
                      newMotors.yaw_starboard  !=   subMotors.yaw_starboard ||
                      newMotors.roll_top       !=   subMotors.roll_top      ||
                      newMotors.roll_bottom    !=   subMotors.roll_bottom; 
                      
                      
  subMotors = newMotors;
  return changed;
}
/**
 * Motors Driven By Vector
 * @param  motor1                Pointer to first motor
 * @param  motor2                Pointer to second motor
 * @param  vector1               First vector which modifies the motor
 * @param  vector1motor1modifier How vector 1 modifies motor 1 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector1motor2modifier How vector 1 modifies motor 2 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector2               Second vector which modifies the motor
 * @param  vector2motor1modifier How vector 2 modifies motor 1 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector2motor2modifier How vector 2 modifies motor 2 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @return                       void
 */
void   motorsDrivenByVectors(signed char *motor1, signed char *motor2, 
        signed char vector1, char vector1motor1modifier, 
        char vector1motor2modifier, signed char vector2, 
        char vector2motor1modifier, char vector2motor2modifier) {
    signed char motor1values[2], absValues[2], motor2values[2],
    larger;
    int motor1base, motor2base, motor1modifier, motor2modifier, motor1value, 
    motor2value,motor1_half_modifier,motor2_half_modifier, signDiffMotor1, 
    signDiffMotor2;
    
    motor1values[0] = vector1 * vector1motor1modifier;
    motor1values[1] = vector2 * vector2motor1modifier;
    
    motor2values[0] = vector1 * vector1motor2modifier;
    motor2values[1] = vector2 * vector2motor2modifier;
    
    absValues[0] = abs(motor1values[0]);
    absValues[1] = abs(motor1values[1]);
    larger   = (absValues[1] > absValues[0]) ? 1 : 0;
    
    motor1base     = motor1values[larger];
    motor1modifier = motor1values[!larger];
    motor2base     = motor2values[larger];
    motor2modifier = motor2values[!larger];
    //
    if(larger) {
        signDiffMotor2 = vector1motor1modifier==vector1motor2modifier ? 1 : -1;
        signDiffMotor1 = vector2motor1modifier==vector2motor2modifier ? 1 : -1;
        //std::cout << "HERE" << a;
    } else {

        signDiffMotor1 =  vector1motor1modifier==vector1motor2modifier ? 1 : -1;
        signDiffMotor2 =  vector2motor1modifier==vector2motor2modifier ? 1 : -1;
    }
    signDiffMotor1 *= vector1motor2modifier==vector2motor2modifier ? 1 : -1;
    signDiffMotor2 *= vector1motor1modifier==vector2motor1modifier ? 1 : -1;
    
    //
    motor1_half_modifier = motor1modifier/2;
    motor2_half_modifier = motor2modifier/2;
    
    
    
    motor1value = motor1base;
    motor2value = motor2base;
    
    motor1value += motor1_half_modifier;
    motor2value += motor2_half_modifier;
    
    if(motor1value > 127) {
        motor2value += signDiffMotor2 * (motor1value-127);
        motor1value = 127;

    } else if(motor1value < -127) {
        motor2value += signDiffMotor2 * (motor1value + 127);
        motor1value = -127;
        
    }
    if(motor2value > 127) {
        motor1value += signDiffMotor1 * (motor2value-127);
        motor2value = 127;

    } else if(motor2value < -127) {

        motor1value += signDiffMotor1 * (motor2value + 127);
        motor2value = -127;

    }
    *motor1 = motor1value;
    *motor2 = motor2value;
    
}


void loop() {

  readController();
  if(calculateMotorSpeedsChanged())
    sendMotorSpeeds();
  
  delay(50);
}
void sendMotorSpeeds() {
  switch(BUILD_MODE) {
    case MODE_RELEASE_BINARY: {
      const byte SET_MOTOR_SPEEDS_COMMAND = 0xAB;
      Serial.write(SET_MOTOR_SPEEDS_COMMAND);
      Serial.write(subMotors.pitch_bow);
      Serial.write(subMotors.pitch_stern);
      Serial.write(subMotors.yaw_port);
      Serial.write(subMotors.yaw_starboard);
      Serial.write(subMotors.roll_top);
      Serial.write(subMotors.roll_bottom);
      break;
    }

    case MODE_DEBUG_VERBOSE: {
      
      Serial.print("\tpitch_bow: ");      
      printThreeDigits(subMotors.pitch_bow);
      
      Serial.print("\tpitch_stern: ");    
      printThreeDigits(subMotors.pitch_stern); 
      
      Serial.print("\tyaw_port: ");       
      printThreeDigits(subMotors.yaw_port);
      
      Serial.print("\tyaw_starboard: ");  
      printThreeDigits(subMotors.yaw_starboard);  
      
      Serial.print("\troll_top: ");       
      printThreeDigits(subMotors.roll_top);
      
      Serial.print("\troll_bottom: ");    
      printThreeDigits(subMotors.roll_bottom);
      
      Serial.println();
      break;
    }
  }
}
void printThreeDigits(char n) {
char abs_n = abs(n);
if(n>=0) Serial.print(" "); else Serial.print("-");

if(abs_n<100) Serial.print(" ");
if(abs_n<10) Serial.print(" ");
Serial.print(abs_n, DEC);
}
void readController() {
  if(controllerStatus != CONTROLLER_SUCCESS) { // skip loop if no controller found
    controllerStatus = initializeControllers();
    return; 
  }
  
  if(type == CONTROLLER_TYPE_DUALSHOCK) { // Guitar Hero Controller
    const boolean INVERTED = true;
    const boolean NORMAL   = false;
    ps2x.read_gamepad(false, vibrate);          // read controller and set large motor to spin at 'vibrate' speed
    subMotion.surge = mapToPercentageVector(ps2x.Analog(PSS_LY), INVERTED);
    subMotion.sway  = mapToPercentageVector(ps2x.Analog(PSS_LX), NORMAL);
    subMotion.roll  = mapToPercentageVector(ps2x.Analog(PSS_RX), NORMAL);
    subMotion.pitch = mapToPercentageVector(ps2x.Analog(PSS_RY), INVERTED);
    
    subMotion.heave = mapToPercentageVector((ps2x.Analog(PSAB_R2)-1)/2 + 128 - 
      ps2x.Analog(PSAB_L2)/2, NORMAL);
    subMotion.yaw   = mapToPercentageVector((ps2x.Analog(PSAB_R1)-1)/2 + 128 - 
      ps2x.Analog(PSAB_L1)/2, NORMAL);
    
    /*Serial.print("\tsurge: ");  Serial.print(subMotion.surge, DEC);
    Serial.print("\tsway:  ");    Serial.print(subMotion.sway, DEC); 
    Serial.print("\tpitch: ");    Serial.print(subMotion.pitch, DEC);
    Serial.print("\tyaw:   ");    Serial.print(subMotion.yaw, DEC);  
    Serial.print("\theave: ");    Serial.print(subMotion.heave, DEC);
    Serial.print("\troll: ");     Serial.print(subMotion.roll, DEC); 
    
    Serial.println();*/

  } else {
    //Serial.print("Invalid controller type");
  }
}
  
