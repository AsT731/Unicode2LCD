void Unicode2LCD(unsigned char *buf) // Конвентирует строку buf содержащую символы кириллицы в кодировке UNICODE в строку для вывода на LCD в кодировке экрана
                            // Важно: buf должен ссылаться на адрес ОЗУ МК. Если buf будет ссылаться на Flash, произойдет аварийный перезапуск МК
{
  uint16_t j = 0, k;

  for (uint16_t i = 0; buf[i] != 0;i++)
  {
    if(buf[i] == 0xD0) // Проверка на кириллицу в UNICODе.
    {
      i++; // Пропускаем символ 0xD0
      if(buf[i] == 0x81) // Проверяем букву 'Ё'
      {
        buf[j++] = BIG_YO;
        continue;
      }
      // Вычитаем из символа сивол кириллицы 'А' (0x90) и получаем индекс в массиве перекодировки.      
      k = constrain((uint8_t)(buf[i] - 0x90), 0, sizeof(Char_Table) - 1); // Навсякий случай, что бы не вылететь за границу массива.
      buf[j++] = Char_Table[k]; 
      continue;
    }
    if(buf[i] == 0xD1) // Проверка на кириллицу в UNICODе.
    {
      i++; // Пропускаем символ 0xD1
      // Вычитаем из из символа сивол кириллицы 'р' (0x80), добавляем 48 и получаем индекс в массиве перекодировки.
      k = constrain((uint8_t)(buf[i] + 48 - 0x80), 0, sizeof(Char_Table) - 1); // Навсякий случай, что бы не вылететь за границу массива.
      buf[j++] = Char_Table[k];                                                
      continue;
    }
    if(buf[i] > 0x7F) // Символы с номером больше чем 127 считаются записанными в кодировке UNICODE и имеют размер 2 байта. В этом случае если символ не попадает в диапазон кириллицы, оставляем его в строке без изменения.
    {
      if(i != j) // Если i == j то символ уже находится на своем месте в перекодируемой строке.
      {
        buf[j++] = buf[i++]; // Копируем 2 байта символа UNICODE без изменений.
        buf[j++] = buf[i];
      }
      else
      {
        i++; // Символ находится на своем месте 
        j += 2;
      }
    }
    else // Символ из первой половины таблицы ASCII и занимает 1 байт.
    {
      if(i != j)
        buf[j] = buf[i]; // Символ не в кодировке UNICODE, копируем его без изменений. Если i == j то символ уже находится на своем месте
      j++;
    }
  }
  buf[j] = 0; // Завершающий строку символ.
}

void Create_init_str(unsigned char *buf) // Формирует строку для инициализации переменной в формате языка C: ch[] = {0xa8, 'p', 0xb8, 0xb3, 'e', 0xbf, '!', 0x00}; // Привет!
{
  unsigned char *tmp;

  tmp = (unsigned char *)malloc(sizeof(unsigned char) * (strlen((char *)buf) + 1)); // Выделяем память для новой строки
  if(tmp == nullptr)
    return; // Память выделить не удалось.
  strcpy((char *)tmp, (char *)buf); // buf может ссылаться на область памяти расположенной во Flash МК. Копируем содержимое buf в RAM

  Unicode2LCD(tmp); // Выполняем перекодировку строки tmp для вывода на LCD

  Serial.print("{"); 
  for(uint16_t i = 0; tmp[i] != 0;i++)
  {
    if(tmp[i] >= 0x7F)
    {
      Serial.print("0x"); // Выводим символ в шестнадцатеричном формате
      Serial.print(tmp[i], HEX); 
      Serial.print(", "); 
    }
    else
    {
      Serial.print("\'"); // Выводим символ в формате 'что-то'
      Serial.print((char)tmp[i]); 
      Serial.print("\', "); 
    }
  }
  Serial.print("0x00}; // "); // Завершающий символ строки 0x00
  Serial.println((char *)buf); // Выводим исходную строку в качестве комментария
// Второй вариант строки инициализации   
    Serial.print("\""); 
  for(uint16_t i = 0; tmp[i] != 0;i++)
  {
    if(tmp[i] != ' ')
    {
      Serial.print("\\x"); // Выводим символ в шестнадцатеричном формате
      Serial.print(tmp[i], HEX); 
    }
    else
      Serial.print((char)tmp[i]); // Выводим символ в пробела
  }
  Serial.print("\"; // "); // Завершаем строку
  Serial.println((char *)buf); // Выводим исходную строку в качестве комментария

#ifdef LCD_present
// ----------------------------------------------------
  lcd.clear();
  lcd.print(tmp); // Для проверки выводим перекодированную строку на LCD
// ----------------------------------------------------
#endif
  free(tmp);
}

#ifdef LCD_present
// ----------------------------------------------------
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
// ----------------------------------------------------
#endif

