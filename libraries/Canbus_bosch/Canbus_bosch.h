//Test library for reading from Bosch CAN (0x773)

#ifndef canbus_bosch__h
#define canbus_bosch__h

#define CANSPEED_500	1		// CAN speed at 500 kbps
#define ATH 5					// Throttle's Position in 0x773

class Canbus_bosch
{
  public:

	Canbus_bosch();
    char init(unsigned char);
	int ecu_req(int pid,  int &value);
};
extern Canbus_bosch Canbus;
//extern tCAN message;

#endif
