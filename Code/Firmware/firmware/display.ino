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


