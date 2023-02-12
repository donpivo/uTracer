#define LED_MCU_STATUS 6
#define LED_Heater A2
#define LED_HighVoltage A0
#define PIN_PSU_EN A1
#define PIN_OUT_EN A3
#define FLAG_HIGH_VOLTAGE 8
#define FLAG_HEATER_FILT 2



void setup() 
{
  pinMode(LED_MCU_STATUS, OUTPUT);
  pinMode(LED_Heater, OUTPUT);
  pinMode(LED_HighVoltage, OUTPUT);
  pinMode(FLAG_HEATER_FILT, INPUT);
  pinMode(FLAG_HIGH_VOLTAGE, INPUT);



}

void loop() 
{
  digitalWrite(LED_HighVoltage, digitalRead(FLAG_HIGH_VOLTAGE));
  digitalWrite(LED_Heater, !digitalRead(FLAG_HEATER_FILT));
}