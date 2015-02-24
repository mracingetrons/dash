Trying to read ATH (throttle angle) from Bosch Functions Sheet it is CAN ID=0x773 Byte 5.

I have pared down the shield_sample (see one directory up). I put the pared down library in dash/library (where it needs to go for Arduino). The code is pretty simple and I put some debugging values in there to be displayed on the serial monitor. It does not show that there is a message to be taken in. >>>>> It must be a timing problem, but I'm not entirely sure. <<<<<

The board might also not be built right. (See schematic with a grounded res/cap circuit on CANH and CANL - this is a lowpass filter, it grounds high frequencies).