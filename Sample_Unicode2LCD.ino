//#define LCD_present // LCD экран имеется?

#include "CharSet_Table.h"
#include "Unicode2LCD.h"

#ifdef LCD_present
// ----------------------------------------------------
#include <LiquidCrystal_I2C.h>

#define DROW        4  // Количество строк дисплея
#define DCOL        20 // Количество столбцов дисплея

LiquidCrystal_I2C lcd(0x27, DCOL, DROW);  // Инициализация дисплея: адрес, столбцы, строки
// ----------------------------------------------------
#endif

void setup() {
  Serial.begin(115200);

#ifdef LCD_present
// ----------------------------------------------------
  lcd.init();
  lcd.setBacklight(1);
  Show_charset(); // Show charset of LCD
// ----------------------------------------------------
#endif

}

void loop() 
{
  unsigned char buf[500]; // Буфер под строку. Символ кириллицы в кодировке Unicode занимает 2 байта.
  uint16_t len;

  do
  {
    len = Serial.readBytesUntil('\r', buf, sizeof(buf) - 1); // Важно! Обратите на последовательность окончания строки в терминале. Должно быть NL (\n) - новая строка
  } while(!len); // Ожидаем ввода данных
  buf[len - 1] = 0; // Завершаем строку
  Create_init_str(buf); // Выводим перекодированную строку на экран и в последовательный порт
}


