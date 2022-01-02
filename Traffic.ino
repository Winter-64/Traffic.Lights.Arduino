
// Author: Patrick Zhang
// Purporse: Write a program that simulates traffic lights at a 4 way intersection, 
// this means repeating the green, yellow and red light for the road going
// North to south and east to west. As well as implement an "emergency vehicle button" for both directions 
// of the intersection to simulate an emergency vehicle passing through, which will quickly turn the light
// to green if the light is red or extend the time of green light if the light is already green.  
// Status: DONE 



// these are the slots on the arduino where the lights are connected to
const int greenLightNorthToSouth = 2;
const int yellowLightNorthToSouth = 3;
const int redLightNorthToSouth = 4;
const int greenLightEastToWest = 7;
const int yellowLightEastToWest = 6;
const int redLightEastToWest = 5;

// the MULTIPLIER and milliSecond are time functions that convert the number of times the loop runs into a specific time. 
// After adjusting due to my loop running at a different speed then other programs, second should be 300L*milliSecond in my
// case, but this may vary with other people's code. 

const long MULTIPLIER = 100L;

const long milliSecond = 1L*MULTIPLIER; 
const long second = 300L*milliSecond;


// green light will stay on for 10 seconds
// red light will stay on for 12 seconds
// yellow light will stay on for 1 second

 long greenLightDelayTime = 10L*second;
 long yellowLightDelayTime = second;
 long redLightDelayTime = 12L*second;


// button delay time is created so the user can hold the button longer 

const int buttonDelayTime = 175;

// ON and OFF are set to HIGH and LOW respectively which will control if the light is off or on
// PRESSED checks if any of the two buttons are pressed
// At the start, the green light of the East to West direction will be on and the red light of the 
// North to South direction will be on. The other lights are off but will be turned on and off during the 
// timer interval in the main loop code. 

const int ON = HIGH;
const int OFF = LOW; 
const int PRESSED = HIGH;
int greenLightEWState = ON;
int greenLightNSState = OFF;
int yellowLightEWState = OFF; 
int yellowLightNSState = OFF;
int redLightEWState = OFF;
int redLightNSState = ON; 


// the slots on the arduino where the 2 buttons are plugged in

const int buttonNorthToSouth = 8;
const int buttonEastToWest = 9;

// long timer variable, which will document how many times the loop will be run, at the beginning, it 
// will be 0. 

long timer = 0; 

void setup() {




  
  // put your setup code here, to run once:



  // set the lights to OUTPUT for the arduino to output the lights, and to check the input from the buttons (pressing the button) 
    pinMode( greenLightEastToWest, OUTPUT );
    pinMode( yellowLightEastToWest, OUTPUT );
    pinMode( redLightEastToWest, OUTPUT );
    
    pinMode( greenLightNorthToSouth, OUTPUT );
    pinMode( yellowLightNorthToSouth, OUTPUT );
    pinMode( redLightNorthToSouth, OUTPUT );
    pinMode( buttonNorthToSouth, INPUT);
    pinMode( buttonEastToWest, INPUT);

    



}

void loop() {



  // The phases of this intersection is split into 6 parts

  // termology (for convenience): 
  // NS -> North-South intersection
  // EW -> East-West intersection


  // phase 1 will be set to greenLightDelayTime as thats how long the EW green light will be running before it stops. 

  // phase 2 will be set to phase1 + yellowLightDelayTime, this is the part where the EW yellow light will stop shining and the 
  // EW red light will start.  

  // phase 3 will be set to phase2 + second because between phase 2 and phase 3, both red lights (NS and EW), are on. When
  // the timer reaches phase 3, the NS red light will be turned off and NS green light will be on.

  // phase 4 will be set to phase3 + greenLightDelayTime because between phase 3 and 4, the NS green light will be on. At phase 4, 
  // the NS green light will be turned off and the NS yellow light will be on.

  // phase 5 will be set to phase4 + yellowLightDelayTime because between phase 4 and 5, the NS yellow light will be on. The NS 
  // yellow light will be turned off whne timer reaches phase 5 and the NS red light will be turned on.

  // phase 6 will be set to phase5 + second because between phase 5 and 6, both red light (NS and EW) are on. When the timer reaches
  // phase 6, the EW red light will be turned off and the EW green light will come on. 



  long phase1 = greenLightDelayTime;
  long phase2 = phase1 + yellowLightDelayTime;
  long phase3 = phase2 + second;
  long phase4 = phase3 + greenLightDelayTime;
  long phase5 = phase4 + yellowLightDelayTime;
  long phase6 = phase5 + second;


  // If emergency button of direction North to South is pressed, then 
  // the it will first determine if the North South red light is ON or OFF.
  // If the North South red light is on, then the timer will be set to phase 1, when the
  // EW yellow light was first lit, which makes it seems like the traffic lights has switched over faster. 
  // If the light is OFF, then the timer will be set to phase 3 when the green light was first lit, which
  // resets the time elapsed for the NS green light.

    int buttonPressedNS = 0; 

  buttonPressedNS = digitalRead( buttonNorthToSouth );

  if( buttonPressedNS == PRESSED ) {

    if(redLightNSState == ON) {
      timer = phase1;
      
    } else if(redLightNSState == OFF){
      timer = phase3; 
    }

    delay (buttonDelayTime);
  }


  // If emergency button of direction East to West is pressed, then 
  // the it will first determine if the East West red light is ON or OFF.
  // If the East West red light is on, then the timer will be set to phase 4, when the
  // NS yellow light was first lit, which makes it seems like the traffic lights has switched over faster. 
  // If the light is OFF, then the timer will be set to phase 6 when the green light was first lit, which
  // resets the time elapsed for the EW green light.

  int buttonPressedEW = 0;

   buttonPressedEW = digitalRead( buttonEastToWest );

     if( buttonPressedEW == PRESSED ) {

    if(redLightEWState == ON) {
      timer = phase4;
      
    } else if(redLightEWState == OFF){
      timer = phase6; 
    }

    delay (buttonDelayTime);
  }



  // As timer increments at a rapid rate everytime the loop is run, it checks for the conditions to see if
  // it has reached the number of times equal to phase 1 to 6. 

  // The specific functions of each phase has been described above. 







    if(timer == phase1) {
      greenLightEWState = OFF;
      yellowLightEWState = ON;
      
    } else if(timer == phase2) {
      yellowLightEWState = OFF;
      redLightEWState = ON; 
      
    } else if(timer == phase3)  {
      redLightNSState = OFF; 
      greenLightNSState = ON;
      
    }  else if(timer == phase4)  {
      greenLightNSState = OFF;
      yellowLightNSState = ON;
      
    } else if(timer == phase5)  { 
      yellowLightNSState = OFF;
      redLightNSState = ON;
      
    } else if(timer == phase6)   { 
      redLightEWState = OFF; 
      greenLightEWState = ON;







      // If timer has incremented above phase6, when both NS and EW red lights are on, then
      // the timer will reset back to 0, restarting the traffic cycle with EW green light on and
      // NS green light off.

      
    } else if(timer > phase6)   { 
      timer = 0; 
    }


    // lit the LED lights based on the set state for each light according to the if statements above.


    digitalWrite( redLightNorthToSouth, redLightNSState );
    digitalWrite( greenLightEastToWest, greenLightEWState );
    digitalWrite( yellowLightEastToWest, yellowLightEWState );
    digitalWrite( greenLightNorthToSouth, greenLightNSState );
    digitalWrite( yellowLightNorthToSouth, yellowLightNSState );
    digitalWrite( redLightEastToWest, redLightEWState );


    // increment the timer so it increases everytime loop() is ran. 

        timer++;






}
