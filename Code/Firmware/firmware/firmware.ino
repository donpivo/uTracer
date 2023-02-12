#include <Wire.h>
#include <INA219.h> //https://github.com/flav1972/ArduinoINA219
#include <SPI.h>
#include <Arduino_ST7789_Fast.h>
#include <Adafruit_GFX.h>

//INA219 Power Monitor Settings
#define SHUNT_MAX_V 0.03  
#define BUS_MAX_V   32.0  
#define MAX_CURRENT 5 
#define SHUNT_R   0.0105
INA219 ina219;

//Display Settings and Initialization
#define SCR_WD   240
#define SCR_HT   240
#define DISP_DC  10
#define DISP_RST 9
Arduino_ST7789 display = Arduino_ST7789(DISP_DC, DISP_RST);

//IO Pins
#define PIN_LED_MCU_STATUS 6
#define PIN_LED_HEATER A2
#define PIN_LED_HIGH_VOLTAGE A0
#define PIN_LED_LIMIT_I 3
#define PIN_LED_LIMIT_V 4
#define PIN_PSU_EN A1
#define PIN_OUT_EN A3
#define FLAG_HIGH_VOLTAGE 8
#define FLAG_HEATER_FILT 2
#define FLAG_CUR_LIM_FILT 5


//Global variables
bool heaterOn, prevHeaterOn;
bool currentLimited, prevCurrentLimited;
bool highVoltage, prevHighVoltage;
bool displayStatechange;
unsigned long lastMeasurementTime;
float lastVoltage=-1;
float lastCurrent=-1;

//Other settings
#define MEASUREMENT_INTERVAL 250 //milliseconds


void setup() 
{
  //Status LED: BOOT
  pinMode(PIN_LED_MCU_STATUS, OUTPUT);
  digitalWrite(PIN_LED_MCU_STATUS, LOW);
  //INA219 Power Monitor Initialization and Configuration
  ina219.begin();
  ina219.configure(INA219::RANGE_32V, INA219::GAIN_1_40MV, INA219::ADC_32SAMP, INA219::ADC_32SAMP, INA219::CONT_SH_BUS);
  ina219.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  //Initialize and Clear Display
  display.init();
  display.setRotation(3);
  display.fillScreen(BLACK);
  //Configure IO pins
  pinMode(PIN_LED_HEATER, OUTPUT);
  pinMode(PIN_LED_HIGH_VOLTAGE, OUTPUT);
  pinMode(PIN_LED_LIMIT_I, OUTPUT);
  pinMode(PIN_LED_LIMIT_V, OUTPUT);
  pinMode(PIN_PSU_EN, OUTPUT);
  pinMode(PIN_OUT_EN, OUTPUT);
  pinMode(FLAG_HIGH_VOLTAGE, INPUT);
  pinMode(FLAG_HEATER_FILT, INPUT);
  pinMode(FLAG_CUR_LIM_FILT, INPUT);
  digitalWrite(PIN_PSU_EN, HIGH);
  digitalWrite(PIN_LED_LIMIT_V, HIGH);
  digitalWrite(PIN_LED_MCU_STATUS, HIGH);
}

void loop() 
{
  heaterOn=true;
  // heaterOn=!digitalRead(FLAG_HEATER_FILT);
  if(heaterOn!=prevHeaterOn)
  {
    digitalWrite(PIN_LED_HEATER, heaterOn);
    digitalWrite(PIN_OUT_EN, heaterOn);
    displayStatechange=true;
    prevHeaterOn=heaterOn;
  }
  
  currentLimited=!digitalRead(FLAG_CUR_LIM_FILT);
  if(currentLimited!=prevCurrentLimited)
  {
    digitalWrite(PIN_LED_LIMIT_I, currentLimited);
    digitalWrite(PIN_LED_LIMIT_V, !currentLimited);
    displayStatechange=true;
    prevCurrentLimited=currentLimited;
  }
  
  highVoltage=digitalRead(FLAG_HIGH_VOLTAGE);
  if(highVoltage!=prevHighVoltage)
  {
    digitalWrite(PIN_LED_HIGH_VOLTAGE, highVoltage);
    displayStatechange=true;
    prevHighVoltage=highVoltage;
  }  
  
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
    if(displayStatechange) updateDisplayStatus();
    lastMeasurementTime=millis();

  }
}



float round1(float value) {
   return (int)(value * 10) / 10.0;
}
