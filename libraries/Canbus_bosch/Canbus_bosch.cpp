//Test library for reading from Bosch CAN (0x773)

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pins_arduino.h"
#include <inttypes.h>
#include "global.h"
#include "mcp2515.h"
#include "defaults.h"
#include "Canbus_bosch.h"

Canbus_bosch::Canbus_bosch() {
}

char Canbus_bosch::init(unsigned char speed) {

  return mcp2515_init(speed);
 
}

//Returns 0 if message is received, returns 1 if message is not received
int Canbus_bosch::ecu_req(int pid,  int &value)  {
	tCAN message;
	float engine_data;
	int timeout = 0;
	char message_ok = 0;				
	
	//I think this  was in here only for sending a message
	//mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
	
	while(timeout < 4000)
	{
		timeout++;
		
		value = 253;
		
				if (mcp2515_check_message()) {
					
					//debug
					value= 254;
					
					if (mcp2515_get_message(&message))  {
							//If it is message 0x773
							if((message.id == 0x773)) {
								value = message.data[pid];
							}
							
							//debug
							value = 255;
					}
				}
				if(message_ok == 1) return 0;
	}
	
	timeout = 0;
 	return 1;
}

Canbus_bosch Canbus;