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
#define TFT_CS 10

/*Reading BOSCH CAN2 line*/

//Data will be temporarily stored to this char

unsigned long timeout = 500;
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
  // disable screen SPI
  
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);

  // disable SD SPI
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);

  // disable CANBUS SPI
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  
  
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
  
  // Initialize MCP2515 CAN controller at the specified speed
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
  // Grab ATH from Bosch CAN (note it is not a request)
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

/*unsigned long firstrect() 
{
  // first section with warnings
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRect(0, 0, 105, 240, ILI9341_BLUE);
  unsigned long start = micros();
  tft.setCursor(6, 7);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("WARNINGS"); // Warnings display
  tft.drawLine(7, 22, 99, 22, ILI9341_WHITE);
  
  tft.setCursor(30, 70); // Oil temp warning
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("OIL TEMP"); 

  tft.setCursor(24, 120); // Water temp warning
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("WATER TEMP"); 
  
  tft.setCursor(10, 170); // Water pressure
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("WATER PRESSURE"); 
  
  return micros() - start;
}

unsigned long secondrect() 
{
  // second section with warnings
  tft.drawRect(215, 0, 105, 240, ILI9341_BLUE);
  unsigned long start = micros();
  tft.setCursor(220, 7);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("WARNINGS"); // Warnings display
  tft.drawLine(221, 22, 313, 22, ILI9341_WHITE);
  
  tft.setCursor(245, 70); // Oil temp warning
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("OIL TEMP"); 

  tft.setCursor(239, 120); // Water temp warning
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("WATER TEMP"); 
  
  tft.setCursor(225, 170); // Water pressure
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("WATER PRESSURE"); 
  
  return micros() - start;
}

unsigned long thirdrect() 
{
  // gear section
  tft.drawRect(106, 0, 108, 120, ILI9341_GREEN);
  unsigned long start = micros();
  return micros() - start;
}

unsigned long gear_change()
{
  for (int i = 0; i < 6; i++)
  {
    tft.setCursor(123, 7);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(15);
    tft.print(i);
    //delay(3000);
      
    // blanking old gear
    tft.setCursor(123, 7);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(15);
    tft.print(i);
  }
}

unsigned long fourthrect()
{
  // lap section
  tft.drawRect(106, 121, 108, 119, ILI9341_RED);
  unsigned long start = micros();
  return micros() - start;
}
*/
  
/*void check_time()
{
  if (ms > 9)
  {
    ms = 0;
    ss++;
  }
  
  else if (ss > 59)
  {
    ss = 0;
    mm++;
  }
}*/
  
// find out if seconds has changed   
  /*time = millis();
  ms = (time - reftime)/1000;
  if(ms == old_seconds) return ms;
  
  // printing new time
  tft.setCursor(108, 200);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(5);
  tft.print(ms);
  delay(1000);
  
  // blanking old time
  tft.setCursor(108, 200);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(4);
  tft.print(ms);
  old_seconds = ms;
  */


