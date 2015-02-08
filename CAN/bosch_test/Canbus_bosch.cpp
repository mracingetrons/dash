//Test library for reading from Bosch CAN (0x773)

#if ARDUINO>=100
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif
#include <stdint.h>
#include <avr/pgmspace.h>

CanbusClass::CanbusClass() {

 
}

char CanbusClass::init(unsigned char speed) {

  return mcp2515_init(speed);
 
}

//Returns 0 if message is received, returns 1 if message is not received
int CanbusClass::ecu_req(int pid,  uint8_t *value) 
{
	tCAN message;
	float engine_data;
	int timeout = 0;
	char message_ok = 0;				
	
	//I think this  was in here only for sending a message
	//mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
//		SET(LED2_HIGH);	
	
	while(timeout < 4000)
	{
		timeout++;
				if (mcp2515_check_message()) 
				{

					if (mcp2515_get_message(&message)) 
					{
							//If it is message 0x773
							if((message.id == 0x773))
							{
								buffer[0] = message.data[pid];
					}
				}
				if(message_ok == 1) return 0;
	}

 	return 1;
}

CanbusClass Canbus;