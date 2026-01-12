void Create_init_str(char *buf) // Формирует строку для инициализации переменной в формате языка C: ch[] = {0xa8, 'p', 0xb8, 0xb3, 'e', 0xbf, '!', 0x00}; // Привет!
{
  char *tmp = nullptr;

  tmp = (char *)malloc(sizeof(char) * (strlen(buf) + 1)); // Выделяем память для новой строки 
  if(tmp == nullptr)
    return; // Память выделить не удалось.
  strcpy(tmp, buf); // buf может ссылаться на область памяти расположенной во Flash МК. Копируем содержимое buf в RAM

  Unicode2LCD(tmp); // Выполняем перекодировку строки tmp для вывода на LCD

  Serial.print("{"); 
  for(uint8_t i = 0; tmp[i] != 0;i++)
  {
    if(tmp[i] >= 0x7F)
      Serial.print("0x" + String(tmp[i], HEX) + ", "); // Выводим символ в шестнадцатеричном формате
    else
      Serial.print("\'" + String(tmp[i]) + "\', "); // Выводим символ в формате 'что-то'
  }
  Serial.println("0x00}; // " + String(buf)); 
  lcd.print(tmp); // Выводим перекодированную строку на LCD
  free(tmp);
}