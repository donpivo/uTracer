/*
 ST7789 240x240 IPS (without CS pin) connections (only 6 wires required):

 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> D8 or any digital
 #06 DC  -> D7 or any digital
 #07 BLK -> NC
*/

#define SCR_WD   240
#define SCR_HT   240
#include <SPI.h>
#include <Adafruit_GFX.h>


#define TFT_DC  A1
#define TFT_RST A0
#include <Arduino_ST7789_Fast.h>


Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

void setup() 
{
  // Serial.begin(9600);
  lcd.init();
  lcd.setRotation(3);
  lcd.fillScreen(BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(BLUE);
  lcd.setCursor(0, 0);
  lcd.print("Heater start");
  lcd.setTextSize(6);
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 60);
  lcd.print("12.61");
  lcd.setTextColor(GREY);
  lcd.print("V");
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 120);
  lcd.print(" 0.12");
  lcd.setTextColor(GREY);
  lcd.print("A");
  lcd.setTextSize(3);
  lcd.setTextColor(RED);
  lcd.setCursor(0, 210);
  lcd.print("High voltage");
  delay(1000);
  lcd.setTextSize(6);
  lcd.fillRect(0, 60, 180, 50, BLACK);
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 60);
  lcd.print(" 6.33");
}

void loop(void) 
{

}

unsigned long testText(int rot)
{
 
}


