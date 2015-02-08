/*Reading BOSCH CAN2 line*/

#include <Canbus_bosch.h>

//Data will be temporarily stored to this char
int value;
//CANBUS CS line for SPI
int D10 = 10;
//Onboard LED on pin D8
int LED = 8;

void setup() {
    pinMode(LED, OUTPUT); 
    Serial.begin(9600);
    Serial.println("Bosch CAN Reader\n");
    
    //Initialize MCP2515 CAN controller at the specified speed
    if(Canbus.init(CANSPEED_500)) { 
      Serial.println("CAN init OK.\n");
    }
    else {
      Serial.println("CAN init failed.\n");
    } 
 
    delay(1000); 
}

void loop() {
  digitalWrite(LED, HIGH);  
  
  //Grab ATH from Bosch CAN (note it is not a request)
  if(Canbus.ecu_req(ATH,value) == 0)
  {
    Serial.println("ATH: \t");
    Serial.println(value);
  }
  else {
    Serial.print("Error reading ATH: ");
    Serial.print(value);
    Serial.println();
  }
  
  digitalWrite(LED, LOW); 
  delay(1000);
}



