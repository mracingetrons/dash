#include <MCP2515.h>

/*Reading BOSCH CAN2 line*/

//Data will be temporarily stored to this char
//CANBUS CS line for SPI
int D10 = 10;
//Onboard LED on pin D8
int LED = 8;
unsigned long timeout = 4000;
int val;
CANMSG message;
//MCP2515 decoder;
/*
int getCAN(int addr){
 
  CANMSG msg;
  long val;
  boolean rxSuccess;
  int noMatch;

  msg.adrsValue = 0x773;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;
  msg.data[0] = 0;
  msg.data[1] = 0;
  msg.data[2] = 0;
  msg.data[3] = 0;
  msg.data[4] = 0;
  msg.data[5] = 0;
  msg.data[6] = 0;
  msg.data[7] = 0;

  rxSuccess = receiveCANMessage(&msg,1000);
  if (rxSuccess) 
  {
    
  }
  
  
  
}
*/
void setup() {
    pinMode(LED, OUTPUT); 
    Serial.begin(9600);
    Serial.println("Bosch CAN Reader\n");
    
    //Initialize MCP2515 CAN controller at the specified speed
    if(MCP2515::initCAN(CAN_BAUD_500K)) { 
      Serial.println("CAN init OK.\n");
    }
    else {
      Serial.println("CAN init failed.\n");
    } 
 
   if(!MCP2515::setCANNormalMode(LOW));
    //delay(1000); 
}

void loop() {
  digitalWrite(LED, HIGH);  
  //MCP2515::queryOBD(0x773);
  //Grab ATH from Bosch CAN (note it is not a request)
  if( MCP2515::receiveCANMessage(&message, timeout) )
  {
    if(message.adrsValue == 0x773){
      Serial.println("ATH: \t");
      val = message.data[5];
      Serial.println(val);
      delay(1000);
    }
  }
  else {
    Serial.print("Error reading ATH: ");
    Serial.println();
  }
  
  //Serial.print("errors receiving: ");
  //Serial.println(MCP2515::getCANRxErrCnt());  
  
  
  digitalWrite(LED, LOW); 
  //delay(1000);
}



