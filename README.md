# Unicode2LCD
Transcoding a Unicode string containing Cyrillic characters into a string for output to a Russified LCD display.

I encountered the problem of displaying messages in Russian on an LCD display. It turned out that the display's character generator was missing Cyrillic characters that had similar shapes to Latin characters, such as 'A'. To display a Cyrillic string on such an LCD display, I had to replace the missing Cyrillic characters with Latin characters. This is quite inconvenient and takes some time. To make this task easier, I wrote several small programs that will help display Cyrillic on an LCD display. IMPORTANT: This applies to LCD displays that have been Russified by the manufacturer (with Cyrillic character support).

Show_charset - displays characters from 0x00 to 0xFF on the screen. This is useful for viewing the display's character generator. Once the screen is full, it waits for user input via the COM port.

Create_init_str is a program that generates a string for initializing a variable in C format. The initial string is read via the COM port, precoded, and output to the LCD in readable form and to the COM port in C format. Example of COM port output:

{0xa8, 'p', 0xb8, 0xb3, 'e', ​​0xbf, ',', ' ', 'M', 0xb8, 'p', '!', 0x00}; // Привет, Мир!

Just copy the string from the terminal and paste it into your code.

Я столкнулся с задачей вывода сообщений на русском языке на LCD дисплей. Выяснилось что в знакогенераторе дисплея отсутствуют символы кириллицы имеющие сходное начертание с символами латинского языка, например, ' А' . Что бы вывести строку кириллицы на такой LCD дисплей приходится заменять в строке отсутствующие символы кириллицы на символы латинского алфавита. Это довольно неудобно и занимает некоторое время. Что бы облегчить эту задачу я написал несколько небольших программ, которые помогут с выводом кириллицы на LCD дисплей. ВАЖНО: речь идет о LCD дисплях русифицированных производителем (с поддержкой символов кириллицы).

Show_charset - показывает на экране символы с 0х00 до 0хFF Будет полезна для просмотра знакогенератора дисплея. По заполнении экрана ждет от пользователя ввода через COM порт.

Create_init_str - программа формирующая строку для инициализации переменной в формате языка C. Исходная строка считывается через COM порт, прекодируется, выводится на LCD в читаемом виде и в COM порт в формате языка C. Пример вывода в  COM порт: 

{0xa8, 'p', 0xb8, 0xb3, 'e', 0xbf, ',', ' ', 'M', 0xb8, 'p', '!', 0x00}; // Привет, Мир!

Достаточно скопировать строку из терминала и вставить её в свой код.
