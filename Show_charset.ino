void Show_charset(void) // Show charset of LCD. DCOL and DROW number of characters and number of lines LCD
{
  uint8_t j, k;
  uint16_t i;
  char buf[3];

  lcd.clear();
  for(i = 0;i < 255;)
  {
    for(j = 0;j < DROW;j++)
    {
      lcd.setCursor(0, j);
      for(k = 0;k < DCOL;k += 5)
      {
        lcd.print(String(i, HEX) + " ");
        lcd.write(i++);
        lcd.print(" ");
        if(i < 0x10)
          lcd.print(" "); // Erases old symbols
      }
    }
    while(!Serial.readBytes(buf, 1)); // Waiting input via COM port
    lcd.clear();
  }
}
