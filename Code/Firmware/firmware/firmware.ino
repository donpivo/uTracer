#include <Wire.h>
#include <INA219.h> //https://github.com/flav1972/ArduinoINA219
#include <SPI.h>
#include <Arduino_ST7789_Fast.h>
#include <Adafruit_GFX.h>

//INA219 Power Monitor Settings
#define SHUNT_MAX_V 0.125  
#define BUS_MAX_V   32.0  
#define MAX_CURRENT 5 
#define SHUNT_R   0.025
INA219 ina219;
//Display Settings and Initialization
#define SCR_WD   240
#define SCR_HT   240
#define TFT_DC  A1
#define TFT_RST A0
Arduino_ST7789 display = Arduino_ST7789(TFT_DC, TFT_RST);



void setup() {
  //INA219 Power Monitor Initialization and Configuration
//  ina219.begin();
//  ina219.configure(INA219::RANGE_32V, INA219::GAIN_4_160MV, INA219::ADC_32SAMP, INA219::ADC_32SAMP, INA219::CONT_SH_BUS);
//  ina219.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  //Clear display
  display.init();
  display.setRotation(3);
  display.fillScreen(BLACK);


  //debug
  updateVoltage(2.125);
  updateCurrent(3.245);
}

void loop() {
  // put your main code here, to run repeatedly:

}
