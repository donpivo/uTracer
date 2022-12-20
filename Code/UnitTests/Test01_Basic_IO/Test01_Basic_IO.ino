#define LED_MCU_ON 12
#define LED_Heater_Start 10
#define LED_Heater_ON 9

void setup() 
{
  pinMode(LED_MCU_ON, OUTPUT);
  pinMode(LED_Heater_Start, OUTPUT);
  pinMode(LED_Heater_ON, OUTPUT);
  digitalWrite(LED_MCU_ON, HIGH);
  delay(1000);
  digitalWrite(LED_Heater_Start, HIGH);
  delay(1000);
  digitalWrite(LED_Heater_Start, LOW);
  digitalWrite(LED_Heater_ON, HIGH);
}

void loop() 
{
  
}