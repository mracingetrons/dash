//Test library for reading from Bosch CAN (0x773)

#ifndef canbus_bosch__h
#define canbus_bosch__h

#define CANSPEED_500	1		// CAN speed at 500 kbps
#define ATH 5					// Throttle's Position in 0x773

class CanbusClass
{
  public:

	CanbusClass();
    char init(unsigned char);
	char ecu_req(int pid,  uint8_t *value);
private:
	
};
extern CanbusClass Canbus;
//extern tCAN message;

#endif
