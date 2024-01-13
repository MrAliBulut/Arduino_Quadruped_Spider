#include <Servo.h>
#include <IRremote.h>



/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------- IR Variables ---------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define irUp  1033561079
#define irDown 465573243
#define irRight 71952287
#define irLeft 2351064443
#define irOK 1217346747
#define ir1 3810010651
#define ir2 5316027
#define ir3 4001918335
#define ir4 1386468383
#define ir5 3622325019
#define ir6 553536955
#define ir7 4034314555
#define ir8 2747854299
#define ir9 3855596927
#define ir0 2538093563
#define irStar 3238126971         
#define irPound 4039382595

#define recieverPin 12

IRrecv irrecv(recieverPin);

decode_results results;

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------- Servo Variables -------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Define servo objects
Servo legServos[8];



//                          RFL = Right Front Lift , LBP = Left Back Pivot
//                          RFP   RFL   RBP   RBL   LFP   LFL   LBP   LBL
int lowPositions[]       =  {30 , 22  , 50  , 50  , 30  , 60  , 50  , 32  };
int neutralPositions[]   =  {80 , 72  , 100 , 100 , 80  , 110 , 100 , 82  };
int highPositions[]      =  {130, 130 , 150 , 150 , 130 , 160 , 150 , 132 };


int counterIR5 = 0; 
int levelIR5 = 0;
bool alternateMovement = false ;


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------- Setup and Loop  -------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {

  Serial.begin(9600);
  // Attach servos to Arduino Pins
  for (int i = 0; i < 8; ++i) {
    legServos[i].attach(i + 2);  // Assuming the servos are connected to pins 2 to 9

  }

  // Initialize IR Receiver
  irrecv.enableIRIn();
  
}

void loop() {

  while (!(irrecv.decode(&results))) {
    //Wait for IR Signal
  }
  handleIRCommand(results.value);

  irrecv.resume(); 

}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------ IR Command Handler ------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void handleIRCommand(unsigned long value) {

  switch (value) {

    case ir1: 
      
      leanSpecific(5);
      break;
    
    
    case ir2: 
      
      leanForward(300);
      break;
    
    
    case ir3: 

      leanSpecific(1);    
      break;
    
    
    case ir4: 
      
      leanLeft(300);
      break;
    
    
    case ir5:
      levelIR5 = counterIR5 % 4;
      counterIR5++;

      switch (levelIR5){
        case 0:
          Elevate();
          break;

        case 1:
          Centralize();
          break;

        case 2:
          DeElevate();
          break;

        case 3:
          Centralize();
          break;
          
        default:
          break;
      }
      break;
    
    
    case ir6: 
      
      leanRight(300);
      break;
    
    
    case ir7: 
      
      leanSpecific(7);
      break;
    
    
    case ir8: 
      
      leanBackward(300);
      break;
    
    
    case ir9: 
      
      leanSpecific(3);
      break;
    
    
    case ir0: 
      
      alternateMovement= !alternateMovement;
      break;

    case irUp:
      
      alternateMovement ? walkForward_Alternate(700) : walkForward(700);
      break;
    
    
    case irDown: 
      
      alternateMovement ? walkBackward_Alternate(700) : walkBackward(700);
      break;
    
    
    case irRight: 
      turnRight();
      break;
    
    
    case irLeft: 
      turnLeft();      
      break;
    
    
    case irOK: 
      
      center_servos();
      break;  

    //We can add more functions fore Star and Pound Later  
    default:
      break;
  }
}


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------- Servo Position Functions ---------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//Sets argument Servo's position to its High State.
void setHigh(int servoNo) {
  if (servoNo <= 7 && servoNo >= 0) // Check if the servoNo is valid
  {
    legServos[servoNo].write(highPositions[servoNo]);
    delay(5);
  }
}

//Sets argument Servo's position to its Notr State.
void setNotr(int servoNo) {
  if (servoNo <= 7 && servoNo >= 0) // Check if the servoNo is valid
  {
    legServos[servoNo].write(neutralPositions[servoNo]);
    delay(5); 
  }
}


//Sets argument Servo's position to its Low State.
void setLow(int servoNo) // Check if the servoNo is valid
{
  if (servoNo <= 7 && servoNo >= 0) {
    legServos[servoNo].write(lowPositions[servoNo]);
    delay(5);  
  }
}

// Set's all Servo's to their Neutral States.
void center_servos() {
  
  for (int i = 0; i < 8; ++i) {
    setNotr(i);
    delay(100);  
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------- Leg Position Functions ---------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


// Turns the specified leg to the left.
// The argument should be the lift servo number of the relevant leg.
void legLeft(int servoNo,int _delay=100) {
  if (servoNo <= 7 && servoNo >= 0) {

    setLow(servoNo);  // Lift Leg
    delay(_delay);
    setHigh(servoNo - 1);  // Move Leg to the Left
    delay(_delay+300);

    setNotr(servoNo); //Lower Leg to Neutral Position

    delay(_delay);
  }
}

// Turns the specified leg to the Center.
// The argument should be the lift servo number of the relevant leg.

void legCenter(int servoNo,int _delay=100){

  if (servoNo <= 7 && servoNo >= 0) {

    setLow(servoNo);  // Lift Leg
    delay(_delay);
    setNotr(servoNo - 1);  // Move Leg to the Center
    delay(_delay+300);

    setNotr(servoNo); //Lower Leg to Neutral Position

    delay(_delay);
  }
}


// Turns the specified leg to the Right.
// The argument should be the lift servo number of the relevant leg.
void legRight(int servoNo,int _delay=100) {
  if (servoNo <= 7 && servoNo >= 0) {

    setLow(servoNo);  // Lift Leg
    delay(_delay);
    setLow(servoNo - 1);  // Move Leg to the Right
    delay(_delay+300);

    setNotr(servoNo); //Lower Leg to Neutral Position

    delay(_delay);
  }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------- Forward Movement Functions --------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



void walkForward_Alternate(int _delay) {

  //Right Front and Left Back Legs
  legLeft(1,50);
  legRight(7,50);
  
  delay(300);

  setNotr(0);
  setNotr(6);

  delay(_delay);
  //Right Front and Left Back Legs
  legRight(5,50);
  legLeft(3,50);
  
  delay(300);

  setNotr(4);
  setNotr(2);
  delay(_delay);
 
}



void walkForward(int _delay) {

  legLeft(1,50);
  legRight(5,50);

  legLeft(3,50);
  legRight(7,50);

  delay(_delay);
  pullForward();  
}

//For the use of walkForward function.
void pullForward(){

    for (int servoNo = 0; servoNo < 8; servoNo += 2) {
      
    if (servoNo > 2) // Detect 0 and 2 numbered servos.
    {
      setHigh(servoNo);

    } else {
      setLow(servoNo);
    }
  }

}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------- Backward Movement Functions -------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void walkBackward_Alternate(int _delay) {

  //Right Back and Left Front Legs
  legRight(3,50);
  legLeft(5,50);
  
  delay(300);

  setNotr(2);
  setNotr(4);

  delay(_delay);


  //Right Front and Left Back Legs
  legLeft(7,50);
  legRight(1,50);
  
  delay(300);

  setNotr(6);
  setNotr(0);
  delay(_delay);
}



void walkBackward(int _delay) {

  legRight(3);
  legLeft(7);

  legRight(1);
  legLeft(5);

  delay(_delay);
  pullBackward();

}

//For the use of walkBackward function.
void pullBackward() {

  for (int servoNo = 0; servoNo < 8; servoNo += 2) {
    if (servoNo <= 2)// Detect 0 and 2 numbered Servos.
    {
      setHigh(servoNo);
    } 
    else {
      setLow(servoNo);
    }
  }
  delay(300);  // Adjust the delay as needed
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------ Elevation Functions -----------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void leanSpecific(int servoNo){
  switch (servoNo){

    case 1:
      setLow(1);
      setHigh(3);
      setHigh(5);
      setHigh(7);
      break;

    case 3:
      setLow(3);
      setHigh(1);
      setHigh(5);
      setHigh(7);
      break;

    case 5:
      setLow(5);
      setHigh(1);
      setHigh(3);
      setHigh(7);
      break;

    case 7:
      setLow(7);
      setHigh(1);
      setHigh(3);
      setHigh(5);
      break;

    default:
      break;
  }
}

void leanForward(int _delay){

  setLow(1);
  setLow(5);

  delay(_delay);

  setHigh(3);
  setHigh(7);

}

void leanBackward(int _delay){

  setLow(3);
  setLow(7);

  delay(_delay);

  setHigh(1);
  setHigh(5);

}

void leanLeft(int _delay){

  setLow(5);
  setLow(7);

  delay(_delay);

  setHigh(1);
  setHigh(3);

}

void leanRight(int _delay){

  setLow(1);
  setLow(3);

  delay(_delay);

  setHigh(5);
  setHigh(7);

}

void Elevate(){

  for(int i =1 ; i<8 ; i+=2 ){
    setHigh(i);
    delay(5);
  }

}

void Centralize(){

  for(int i =1 ; i<8 ; i+=2 ){
    setNotr(i);
    delay(5);
  }

}

void DeElevate(){

  for(int i =1 ; i<8 ; i+=2 ){
    setLow(i);
    delay(5);
  }

}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------ Rotation Functions ------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void turnLeft(){

  for (int servoNo = 1; servoNo < 8; servoNo+=2 ){
    legLeft(servoNo);
    delay(100);
  }
  delay(500);

  for (int servoNo = 0; servoNo < 8; ++servoNo ){
    setNotr(servoNo);
  }
}

void turnRight(){
  for (int servoNo = 1; servoNo < 8; servoNo+=2 ){
    legRight(servoNo);
    delay(100);
  }
  delay(500);
  
  for (int servoNo = 0; servoNo < 8; ++servoNo ){
    setNotr(servoNo);
  }
}



