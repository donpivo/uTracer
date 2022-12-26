void updateDisplayVoltage(float voltage)
{
  display.setTextSize(7);
  display.fillRect(0, 0, 180, 59, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  String strVoltage=voltage<10?" "+String(voltage,1):String(voltage,1);
  display.print(strVoltage);
  display.setCursor(190, 0);
  display.setTextColor(GREY);
  display.print("V");
}

void updateDisplayCurrent(float current)
{
  display.setTextSize(7);
  display.fillRect(0, 50, 180, 99, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(0, 60);
  String strCurrent=current<10?" "+String(current,1):String(current,1);
  display.print(strCurrent);
  display.setCursor(190, 60);
  display.setTextColor(GREY);
  display.print("A");
}

void updateDisplayHeaterStatus(byte heaterStatus)
{
   display.setTextSize(3);
   display.fillRect(0, 200, 239, 239, BLACK);
   display.setCursor(0, 200);
   switch(heaterStatus)
   {
    case 0: display.setTextColor(GREY);
            display.print("Heater Off");
            digitalWrite(LED_Heater_ON, LOW);
            digitalWrite(LED_Heater_Start, LOW);
            break;
    case 1: display.setTextColor(0xFFBA00);
            display.print("Heater Start");
            digitalWrite(LED_Heater_ON, LOW);
            digitalWrite(LED_Heater_Start, HIGH);
            break;
    case 2: display.setTextColor(YELLOW);
            display.print("Heater On");
            digitalWrite(LED_Heater_ON, HIGH);
            digitalWrite(LED_Heater_Start, LOW);
            break;
   }
}
