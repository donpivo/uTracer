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

//IO Pins
#define FlagHighVoltage 3
#define FlagMBHeaterActive 4
#define Heater_EN 5
#define Heater_PWM 6
#define LED_Heater_ON 9
#define LED_Heater_Start 10

//Global variables
int heaterStatus=0;
unsigned long heaterStartTime;
unsigned long lastMeasurementTime;
float lastVoltage=-1;
float lastCurrent=-1;

//Other settings
#define heaterSlowStart 20000 //milliseconds
#define MEASUREMENT_INTERVAL 500 //milliseconds


void setup() 
{
  //INA219 Power Monitor Initialization and Configuration
  ina219.begin();
  ina219.configure(INA219::RANGE_32V, INA219::GAIN_4_160MV, INA219::ADC_32SAMP, INA219::ADC_32SAMP, INA219::CONT_SH_BUS);
  ina219.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  //Initialize and Clear Display
  display.init();
  display.setRotation(3);
  display.fillScreen(BLACK);
  //Configure IO pins
  pinMode(FlagHighVoltage, INPUT);
  pinMode(FlagMBHeaterActive, INPUT);
  pinMode(Heater_EN, OUTPUT);
  digitalWrite(Heater_EN, HIGH);
  pinMode(LED_Heater_ON, OUTPUT);
  digitalWrite(LED_Heater_ON, LOW);
  pinMode(LED_Heater_Start, OUTPUT);
  digitalWrite(LED_Heater_Start, LOW);
  pinMode(Heater_PWM, OUTPUT);
  digitalWrite(Heater_PWM, LOW);
}

void loop() 
{
  if(millis()-lastMeasurementTime>MEASUREMENT_INTERVAL)
  {
    if(digitalRead(FlagMBHeaterActive))
    {
      if(heaterStatus==0) 
      {
        heaterStatus=1;
        updateDisplayHeaterStatus(heaterStatus);
        heaterStartTime=millis();
      }
      if((heaterStatus==1)&&(millis()-heaterStartTime>heaterSlowStart))
      {
        heaterStatus=2;
        updateDisplayHeaterStatus(heaterStatus);
      }
    }
    else if(heaterStatus>0)
    {
      heaterStatus=0;
      updateDisplayHeaterStatus(heaterStatus);
    }
  
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
