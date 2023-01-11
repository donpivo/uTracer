#define LED_MCU_STATUS 12
#define LED_Heater 8
#define LED_HighVoltage 5
#define LED_CurrentLimit 7
#define PIN_PSU_EN A0
#define PIN_OUT_EN A2



void setup() 
{
  pinMode(LED_MCU_STATUS, OUTPUT);
  pinMode(LED_Heater, OUTPUT);
  pinMode(LED_HighVoltage, OUTPUT);
  pinMode(LED_CurrentLimit, OUTPUT);
  pinMode(PIN_PSU_EN, OUTPUT);
  pinMode(PIN_OUT_EN, OUTPUT);

  digitalWrite(LED_MCU_STATUS, LOW);
  delay(1000);
  digitalWrite(LED_MCU_STATUS, HIGH);
  delay(1000);
  digitalWrite(LED_Heater, HIGH);
  digitalWrite(PIN_PSU_EN, HIGH);
  delay(1000);
  digitalWrite(LED_HighVoltage, HIGH);
  delay(1000);
  digitalWrite(LED_CurrentLimit, HIGH);
  digitalWrite(PIN_OUT_EN, HIGH);

}

void loop() 
{
  
}