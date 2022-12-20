void updateVoltage(float voltage)
{
  voltage=round2(voltage);
  display.setTextSize(6);
  display.fillRect(0, 60, 180, 50, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(0, 60);
  String strVoltage=voltage<10?" "+String(voltage,2):String(voltage,2);
  display.print(strVoltage);
  display.setTextColor(GREY);
  display.print("V");
}

void updateCurrent(float current)
{
  current=round2(current);
  display.setTextSize(6);
  display.fillRect(0, 130, 180, 50, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(0, 130);
  String strVoltage=current<10?" "+String(current,2):String(current,2);
  display.print(strVoltage);
  display.setTextColor(GREY);
  display.print("A");
}

float round2(float value) {
   return (int)(value * 100 + 0.5) / 100.0;
}
