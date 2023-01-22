#define LED_MCU_STATUS 12
#define LED_Heater 8
#define LED_HighVoltage 5
#define LED_CurrentLimit 7
#define PIN_PSU_EN A0
#define PIN_OUT_EN A2
#define FLAG_HIGH_VOLTAGE A1
#define FLAG_HEATER_FILT 2



void setup() 
{
  pinMode(LED_MCU_STATUS, OUTPUT);
  pinMode(LED_Heater, OUTPUT);
  pinMode(LED_HighVoltage, OUTPUT);
  pinMode(LED_CurrentLimit, OUTPUT);
  pinMode(FLAG_HEATER_FILT, INPUT);
  pinMode(FLAG_HIGH_VOLTAGE, INPUT);



}

void loop() 
{
  digitalWrite(LED_HighVoltage, digitalRead(FLAG_HIGH_VOLTAGE));
  digitalWrite(LED_Heater, !digitalRead(FLAG_HEATER_FILT));
}