#include <MCP2515.h>
// Author: Livesey George
// Organization: University of Michigan M-Racing, Electronics, 2015

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 6

/*Reading BOSCH CAN2 line*/

//Data will be temporarily stored to this char
//CANBUS CS line for SPI
int D6 = 6;

unsigned long timeout = 100;
int val;
CANMSG message;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

unsigned long time;
unsigned long old_seconds = 0;
unsigned long reftime;
unsigned long ss = 0, ms = 0; // second, milliseccond

void setup() 
{
  Serial.begin(9600);
  reftime = millis();
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();
  
  // START JOHN'S STUFF
  //pinMode(LED, OUTPUT);
  
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Bosch CAN Reader\n");
  
  //Initialize MCP2515 CAN controller at the specified speed
  if(MCP2515::initCAN(CAN_BAUD_500K)) 
  {
     tft.setTextSize(2);
     tft.setCursor(0, 40);
     Serial.println("CAN init OK.\n");
  }
  else 
  {
     tft.setTextSize(2);
     tft.setCursor(0, 60);    
     Serial.println("CAN init failed.\n");
  } 
 
   if(!MCP2515::setCANNormalMode(LOW));
  // END JOHN'S STUFF
  
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  tft.setTextSize(2);
  tft.setCursor(0, 80);
  tft.print("Display Power Mode: 0x"); tft.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  
  tft.setTextSize(2);
  tft.setCursor(0, 100);
  tft.print("MADCTL Mode: 0x"); tft.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  
  tft.setTextSize(2);
  tft.setCursor(0, 120);
  tft.print("Pixel Format: 0x"); tft.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  
  tft.setTextSize(2);
  tft.setCursor(0, 140);
  tft.print("Image Format: 0x"); tft.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  
  tft.setTextSize(2);
  tft.setCursor(0, 160);
  tft.print("Self Diagnostic: 0x"); tft.println(x, HEX); 
  tft.setRotation(3);
  //firstrect();
  //secondrect();
  //thirdrect();
  //fourthrect();
}

void loop(void) 
{
  //check_time();
  //laptime();
  //gear_change();
  
  // START JOHN'S STUFF
  //digitalWrite(LED, HIGH);  
  MCP2515::queryOBD(0x773);
  //Grab ATH from Bosch CAN (note it is not a request)
  if( MCP2515::receiveCANMessage(&message, timeout) )
  {
    if(message.adrsValue == 0x773){
      Serial.println("ATH: \t");
      val = message.data[5];
      Serial.println(val);
      //delay(1000);
    }
  }
  else {
    Serial.print("Error reading ATH: ");
    Serial.println();
  } 
  //digitalWrite(LED, LOW);
 // END JOHN'S STUFF 
  //delay(1000);
}

