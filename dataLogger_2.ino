

/* Sketch for dataLogger
   Built from AnalogReadSerialOut_test
   modified Apr 09, 2014
   Original sketch written to test data logging gui.
   Gui sends "&" to serial communiation initiating program
   LaunchPad sends serial header information followed by "&"
   LaunchPad then sends serial data to be logged.
   At the end of serial data, LaunchPad sends "@" symbol, indicating
     end of run.
 
 
  The circuit:
   PWM output on P1_6 to resistor to analog read on P1_0.  
   Capacitor bridges P1_0 to ground, generating analog signal. 
   Analog read result printed to the serial monitor.
 
begun November 16, 2013 
 This code is in the public domain.
 
 */
#include<Energia.h>   //need this for SPI to work
#include "wiring_analog.c"    // need this for pwm at high frequency, resolution
#include <altSPI.h>

const int analogInA = A11;  // Analog input pin, J1 pin 2, next to vcc
const int analogOutB = PB_4; // pwm pin used to establish reference voltage
const int analogInB = A9;  // Analog input pin, J1 pin 5
const int analogOutA = PB_6; // pwm pin used to establish reference voltage

boolean runState = false;       // tells the program to stop running
boolean gotLims = false;        // tells program to establish min and max I vals

int mode;                // discreet time
int channel;             // channel A
int gainA;         // was 3
int gainB;
int sensorA = 0;        // value read from the pot
int sensorB = 0;
int offSetA = 8;  //128;        // value output to the PWM (analog out)
int offSetB = 200;  //128;        // max value = 255
int nLoop =3;
int rdDelay = 500;              // ms between readings
int pwmClock = 40000; 
int pwmRes = 330;  // gives 10 mV resolution, for greater res, increase value
int sRead;                      // read for stop sign durring run

int i;
int j;
int k = 0;              // start signal; k = *
unsigned long time;     // milliseconds from beginning of expreriment
unsigned long time0;    // milliseconds at beginning of experiment
int param;   // parameter used in reading Serial comm.
int maxRead;
int minRead;
/************************************************/
void setup() {
  // initialize serial communications at 9600 bps:
  pinMode (analogInA, INPUT);
  pinMode (analogInB, INPUT);
  pinMode (analogOutA, OUTPUT);
  pinMode (analogOutB, OUTPUT);
  PWMWrite(analogOutA,330,165,pwmClock);  // sets current offset to VCC/2
  PWMWrite(analogOutB,330,165,pwmClock);     // set reference voltage to VCC/2
  Serial.begin(38400);  //9600); 

}

/***********************************************/
void loop() {
time = 0;
  setupRun();
  setupDigiPot();
  PWMWrite(analogOutA,330,165,pwmClock);  // sets current offset to VCC/2
  PWMWrite(analogOutB,330,165,pwmClock);     // set reference voltage to VCC/2
//  analogWrite(analogOutA, offSetA);   // set voltages for offsets
  //analogWrite(analogOutB, offSetB);  //  readSerial();
  time0 = millis();
  while (runState == true) {
 
  if (mode == 1){             // discrete time
    for (i=0; i<nLoop; ++i){
    readData();
    }
    runState = false;
  }   
  else {                        // continuous mode
    readData();
//    Serial.println(runState);
    }
   }     // end of if runState is true loop  
    
//   Serial.println("end");
   Serial.print(99999);
   Serial.print(",");
   Serial.println(99999); // signal GUI to end run               
//k = 0;   // ends loop
}
//}

/*void   readSerial() {
  if (Serial.available()<= 0) {
  }
  if (Serial.available() > 0){  
   k = Serial.read();  }
 }*/

//}
