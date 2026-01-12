#include <LiquidCrystal_I2C.h>
#include <string.h>
#include "Char_Table.h"

#define DROW        4  // Количество строк дисплея
#define DCOL        20 // Количество столбцов дисплея

LiquidCrystal_I2C lcd(0x27, DCOL, DROW);  // Инициализация дисплея: адрес, столбцы, строки


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.setBacklight(1);
  Show_charset(); // Show charset of LCD
}

void loop() 
{
  char buf[80];
  uint8_t len;

  do
  {
    len = Serial.readBytesUntil('\r', buf, sizeof(buf) - 1); // Важно! Обратите на последовательность окончания строки в терминале. Должно NL - новая строка
  } while(!len); // Ожидаем ввода данных
  buf[len - 1] = 0; // Завершаем строку
  lcd.clear();
  Create_init_str(buf); // Выводим перекодированную строку на экран и в последовательный порт
}


