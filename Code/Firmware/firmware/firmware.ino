#include <Wire.h>
#include <INA219.h> //https://github.com/flav1972/ArduinoINA219
#include <SPI.h>
#include <Arduino_ST7789_Fast.h>
#include <Adafruit_GFX.h>

//INA219 Power Monitor Settings
#define SHUNT_MAX_V 0.03  
#define BUS_MAX_V   32.0  
#define MAX_CURRENT 5 
#define SHUNT_R   0.0107
INA219 ina219;

//Display Settings and Initialization
#define SCR_WD   240
#define SCR_HT   240
#define DISP_DC  10
#define DISP_RST 9
Arduino_ST7789 display = Arduino_ST7789(DISP_DC, DISP_RST);

//IO Pins
#define LED_MCU_STATUS 12
#define LED_HEATER 8
#define LED_HIGH_VOLTAGE 5
#define LED_CURRENT_LIMIT 7
#define PIN_PSU_EN A0
#define PIN_OUT_EN A2
#define FLAG_HIGH_VOLTAGE A1
#define FLAG_HEATER_FILT 2
#define FLAG_CUR_LIM_FILT A3


//Global variables
bool heaterOn = false;
bool currentLimit = false;
unsigned long lastMeasurementTime;
float lastVoltage=-1;
float lastCurrent=-1;

//Other settings
#define MEASUREMENT_INTERVAL 250 //milliseconds


void setup() 
{
  //Status LED: BOOT
  digitalWrite(LED_MCU_STATUS, LOW);
  //INA219 Power Monitor Initialization and Configuration
  ina219.begin();
  ina219.configure(INA219::RANGE_32V, INA219::GAIN_1_40MV, INA219::ADC_32SAMP, INA219::ADC_32SAMP, INA219::CONT_SH_BUS);
  ina219.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  //Initialize and Clear Display
  display.init();
  display.setRotation(3);
  display.fillScreen(BLACK);
  //Configure IO pins
  
  pinMode(LED_HEATER, OUTPUT);
  pinMode(LED_HIGH_VOLTAGE, OUTPUT);
  pinMode(LED_CURRENT_LIMIT, OUTPUT);
  pinMode(PIN_PSU_EN, OUTPUT);
  pinMode(PIN_OUT_EN, OUTPUT);
  pinMode(FLAG_HIGH_VOLTAGE, INPUT);
  pinMode(FLAG_HEATER_FILT, INPUT);
  pinMode(FLAG_CUR_LIM_FILT, INPUT);
  digitalWrite(LED_MCU_STATUS, HIGH);
  digitalWrite(PIN_PSU_EN, HIGH);
  delay(1000);
  digitalWrite(PIN_OUT_EN, HIGH);
}

void loop() 
{
  currentLimit=!digitalRead(FLAG_CUR_LIM_FILT);
  digitalWrite(LED_CURRENT_LIMIT, currentLimit);
  if(millis()-lastMeasurementTime>MEASUREMENT_INTERVAL)
  {
    
    float voltage=round1(ina219.busVoltage());
    if(voltage!=lastVoltage)
    {
      updateDisplayVoltage(voltage);
      lastVoltage=voltage;
    }
    float current=round1(ina219.shuntCurrent());
    if(current!=lastCurrent)
    {
      updateDisplayCurrent(current);
      lastCurrent=current;
    }

    lastMeasurementTime=millis();

  }
}



float round1(float value) {
   return (int)(value * 10) / 10.0;
}
