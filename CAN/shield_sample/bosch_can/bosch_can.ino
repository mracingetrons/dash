/*Reading BOSCH CAN2 line*/

#include <Canbus.h>

//Data will be temporarily stored to this buffer
char buffer[512];
//CANBUS CS line for SPI
int D10 = 10;
//Onboard LED on pin D8
int LED2 = 8;

void setup() {
    pinMode(LED2, OUTPUT); 
    Serial.begin(9600);
    Serial.println("Bosch CAN Reader\n");
    
    //Initialize MCP2515 CAN controller at the specified speed
    if(Canbus.init(CANSPEED_500)) { 
      Serial.println("CAN init OK.\n")
    }
    else {
      Serial.println("CAN init failed.\n")
    } 
 
    delay(1000); 
}

void loop() {
  digitalWrite(LED3, HIGH);  
  
  if(Canbus.ecu_req(ATH,buffer) == 1)          /* Request for engine ATH */
  {
    sLCD.print(buffer);                         /* Display data on LCD */
  } 
   
  digitalWrite(LED3, LOW); 
  delay(100);
}



