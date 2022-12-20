#include <Wire.h>
#include <INA219.h>
#define SHUNT_MAX_V 0.125  
#define BUS_MAX_V   32.0  
#define MAX_CURRENT 5 
#define SHUNT_R   0.025
INA219 monitor;

void setup()
{
  Serial.begin(9600);
  monitor.begin();
  monitor.configure(INA219::RANGE_32V, INA219::GAIN_4_160MV, INA219::ADC_32SAMP, INA219::ADC_32SAMP, INA219::CONT_SH_BUS);
  monitor.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
}

void loop()
{
  Serial.print("raw shunt voltage: ");
  Serial.println(monitor.shuntVoltageRaw());
  
  Serial.print("raw bus voltage:   ");
  Serial.println(monitor.busVoltageRaw());
  
  Serial.println("--");
  
  Serial.print("shunt voltage: ");
  Serial.print(monitor.shuntVoltage() * 1000, 4);
  Serial.println(" mV");
  
  Serial.print("shunt current: ");
  Serial.print(monitor.shuntCurrent() * 1000, 4);
  Serial.println(" mA");
  
  Serial.print("bus voltage:   ");
  Serial.print(monitor.busVoltage(), 4);
  Serial.println(" V");
  
  Serial.print("bus power:     ");
  Serial.print(monitor.busPower() * 1000, 4);
  Serial.println(" mW");
  
  Serial.println(" ");
  Serial.println(" ");
  
  delay(10000);
}


