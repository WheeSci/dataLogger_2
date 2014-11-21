//setupRun Tab / Copied from StellarisWheeStat5_3 sketch
//  note:  all values must be entered as six digits
//     eg: 000002 = 2
//  scaling factors included to use fewer digits when entering manually
//  remove scaling factors to run with GUI

void setupRun() {
    gotLims = false;   // setting up limit bars
    boolean startread = false;
    while (startread == false) {
      if(Serial.available() > 0) {
      int starti = Serial.read();
      if(starti == 38) {           // decimal equiv of Ascii "&"
        startread = true;
        runState = true;
        }
      }
    }   // end of while startread = false
//  mode set to one, channel to zero
  //////////// mode ////////////////
  Serial.print(",,Mode, ");

  readParam();  
  mode=param/100000;     
//  Serial.println(mode);
  delay(20); 
///////////////// channels ///////////////////////
  Serial.print("Channel, ");  //1 is A, 2 is B, 3 is both
//  Serial.print('\t');
  readParam();  
  channel=param/100000;     
//  Serial.println(channel);
  delay(20);  
  ///////////delay///////
  Serial.print("delay, ");
//  Serial.print('\t');
  readParam();  
  rdDelay=param;        // /1000;  // remove 1000 when working with GUI
//  Serial.println(rdDelay);  
  delay(20);  

  /////////// Gain A  ///////
//if (channel != 1) {
  Serial.print("Gain A,");
//  Serial.print('\t');
  readParam();
  gainA=param;              // /1000;       // remove scaling factors for GUI
//  Serial.println(gainA);  
  delay(20);
//}
  /////////// Gain B  ///////
//if (channel !=0) {
  Serial.println("Gain B, ");
 // Serial.print('\t');
  readParam();
  gainB=param;          // /1000;       // 
//  Serial.println(gainB);  
  delay(20);
//}

   /////// print header ///////////////
  Serial.print("time, ");
//  Serial.print('\t');
if(channel !=2) {  
  Serial.print("Channel A,");

  }
if(channel !=1) {  
  Serial.print("Channel B");
//  Serial.print('\t');
  }
  Serial.println("&");
  runState = true;
  k = '*';    // not sure what this is, original runState?
}  
/******************************  end setupRun *******************************/

/****************************** read Paramaters ****************************/
void readParam() {
  //void readParam(int number) {
  //void readParam(int number, float param) {
  long place[6]={
    100000,10000,1000,100,10,1  };           
  int incomingByte[6] = {
    0,0,0,0,0,0  };      // serial read variable. each incoming byte (multiplied by the place)
  int n=0;
  param = 0;
  delayMicroseconds(300);  
  while (Serial.available()<= 0) {
  }
  while (Serial.available() > 0){  
    incomingByte[n] = Serial.read()-48;
    delay(2);
    ++n;          
  }
   
  for(int n=0;n<6;++n){ 
    param = param + (place[n]*(incomingByte[n]));  
  }
}          
/* void   readStop() {               //work on readStop begun Jan 26,3014 from Run_Stop
                                   //transmission of & character from GUI stops data acquisition.
   if (Serial.available()<= 0) {}
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if (inByte == '*') {
      run = 1;
    }
    else if (inByte == '&')  {
      run = 0;
     
    }
    else {}
  }
  
  while (Serial.available()<= 0) {
  }
  while (Serial.available() > 0){  
    while(k !=2) {             // when GUI writes "2", program is initiated
      k = Serial.read()-48;
    }
  }

}
*/
