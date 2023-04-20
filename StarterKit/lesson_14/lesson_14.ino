/*
 * Набор для экспериментов MaxKit 01
 * Код программы для опыта №14: sketch 14
 *
 * Сдвиговый регистр
 *
 * Написано для сайта "Полный комплект" http://maxkit.ru
 *
 *
 * Помощь сообщества Arduino.
 * Посетите сайт http://www.arduino.cc
 *
 *
 * РЕГИСТР СДВИГА
 *
 * Использование микросхемы регистра сдвига для управления 8 выходами
 * используя всего 3 порта Arduino
 *
 * Интегральная Схема (ИС или "IC - integrated circuit"), или "чип",
 * это самодостаточное электронное устройство встроенное в небольшой
 * пластиковый корпус. Если внимательно посмотреть на плату Arduino
 * можно рассмотреть некоторое количеству ИС установленных на ней.
 * Есть тысячи различных видов ИС, доступных для использования, из
 * которых можно собрать множество полезных вещей.
 *
 *
 * Микросхема Сдвиговый Регистр 74HC595 из вашего набора является
 * ИС, которая имеет восемь цифровых выходов. Чтобы использовать
 * эти выходы, мы будем использовать новый интерфейс под названием
 * SPI (Serial Peripheral Interface) или последовательный
 * периферийный интерфейс. Это как ТX и RX к которому вы привыкли,
 * но имеет дополнительные "часы" линию, которая контролирует
 * скорость передачи данных. Многие микросхемы используют SPI
 * (последовательный интерфейс) для связи между собой, поэтому и у
 * Arduino тоже есть такой интерфейс, а также пара команд: shiftIn()
 * и shiftOut(), для доступа и передачи данных ИС.
 *
 * Эта ИС позволяет использовать всего три цифровых порта Arduino
 * для управления 8 цифровыми выходами. А если вам нужно еще больше,
 * вы можете подключить последовательно несколько регистров сдвига,
 * что позволит управлять практически неограниченным количество
 * выходов, все из тех же трех портов Arduino! См. таблицу
 * (datasheet) обозначения выводов регистра сдвига SN74HC595:
 *
 * http://www.sparkfun.com/datasheets/IC/SN74HC595.pdf
 *
 * Подключение оборудования:
 *
 * Сдвиговый регистр:
 *
 *  Подключите чип, так чтобы его выводы оказались с разных
 *  сторон центральной линии макетной платы.
 *
 *  ИС "Регистр Сдвига" имеет 16 контактов. Они пронумерованы
 *  против часовой стрелки, начиная от ключа (не большой выемки
 *  - углубления на торце чипа). См таблицу выше.
 *
 *  74HC595 pin		LED pin		Arduino pin
 *
 *  1  (QB)		LED 2 +
 *  2  (QC)		LED 3 +
 *  3  (QD)		LED 4 +
 *  4  (QE)		LED 5 +
 *  5  (QF)		LED 6 +
 *  6  (QG)		LED 7 +
 *  7  (QH)		LED 8 +
 *  8  (GND)				GND
 *
 *  9  (QH*)
 *  10 (SRCLR*)				5V
 *  11 (SRCLK)				Digital 3
 *  12 (RCLK)				Digital 4
 *  13 (OE*)				GND
 *  14 (SER)				Digital 2
 *  15 (QA)		LED 1 +
 *  16 (VCC)				5V
 *
 *  Светодиоды:
 *
 *  После присоединения всех положительных выводов, указанных выше,
 *  (длинных ножек) светодиодов, соедините их отрицательные выводы
 *  (короткие ножки), каждого светодиода, с резисторами по 330 Ом,
 *  и соедините другую сторону каждого резистора с общим проводом.
 * 
 *
 *
 *
 *
 * Этот sketch был написан SparkFun Electronics,
 * Переведен специально для сайта http://maxkit.ru
 * 01 февраля 2015г.
 *
*/


// Определения контактов:
// 74HC595 использует SPI (последовательный интерфейс),
// которому требуется всего три пина:
// data - данные
// clock - тактовые импульсы
// latch - защелка

int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

// Для наглядности и понимания пины названы соответственно:
// Англ. - рус.: data - данные; clock - тактовые импульсы;
// latch - защелка.

// Мы также объявим глобальную переменную для данных, которые
// будем отправлять в регистр сдвига:

byte data = 0;


void setup()
{
  // Установим три SPI пина, которые будут выходными:

  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}


void loop()
{
  // Мы собираемся использовать те же самые функции, которые
  // использовали в опыте №4 (про несколько светодиодов), мы
  // просто заменили DigitalWrite() новой функцией shiftWrite()
  // Про эту функцию поговорим чуть ниже.
  // Еще появилась новая функция, которая демонстрирует работу
  // двоичного счетчика.

  // Чтобы опробовать различные функции расположенные ниже, просто
  // раскомментируйте одну из них, которую хотите запустить, и
  // закомментируйте оставшиеся, которые не будут использоваться.
  
  one after another - один за другим
  //oneAfterAnother();      // один за другим
  
  //oneOnAtATime();       // прокрутить строку вниз
  
  //pingPong();           // прокрутить строку вниз и обратно

  //randomLED();          // мигание случайным светодиодом
  
  //marquee();            // бегущие огни

  //binaryCount();        // двоичный счет от 0 до 255
}


void shiftWrite(int desiredPin, boolean desiredState)

// Эта функция позволяет устанавливать на выходах регистра
// сдвига либо HIGH либо LOW, точно также, как при использовании
// функции digitalWrite().

// И также как digitalWrite(), эта функция принимает два параметра:

//    "desiredPin" желаемый pin сдвигового регистра от 0 до 7

//    "desiredState" желаемый потенциал на нем HIGH или LOW


// Внутри Arduino, цифры хранятся в виде "битовых" (bits) массивов,
// Каждый бит может содержать лишь одно значение: либо единицу,
// либо ноль (5 Вольт или 0, HIGH или LOW). Из за того что 8 бит
// называется "байтом" (byte) мы будем использовать переменную,
// которой мы дали название "data" в верхней части скетча, длинною
// в байт (byte=8bit), для передачи данных в регистр сдвига.
// Если бит в "data" при входе был единицей, на выходе будет 1.
// Если бит в "data" был "0", на выходе будет 0.

// Для изменения отдельных битов в переменной "data", мы будем
// использовать новую команду Arduino с названием bitWrite(),
// которая может изменять состояние указанного бита на 1 или 0.
{
  // Сначала мы изменим глобальную переменную "data", выборочно
  // поменяв выбранные биты на 1 или 0:

  bitWrite(data,desiredPin,desiredState);
  
  // Теперь мы отправим эти данные в регистра сдвига. Для этого
  // используем функцию shiftOut(), она делает всю тяжелую работу
  // управляет данными, тактовыми импульсами и т.д.:

  shiftOut(datapin, clockpin, MSBFIRST, data);

  // После того, как данные попали в регистр сдвига, нам надо чтобы
  // они появились на его выходах. Для этого их нужно "защелкнуть",
  // подав логическую единицу (HIGH) на 12 pin регистра сдвига.
  // Поэтому даем HIGH через переменную LatchPin, которая будет
  // сигнализировать сдвиговому регистру о том что данным пора
  // появиться на выходах.

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}


/*
oneAfterAnother()

Эта функция будет зажигать один светодиод, делать маленькую паузу,
включать следующий светодиод, опять пауза, затем следующий и так, пока
все светодиоды не загорятся. Затем начнет отключить их в обратном
порядке.
*/


void oneAfterAnother()
{
  int index;
  int delayTime = 1000; // Время (в миллисекундах) для пауз
                        // уменьшите или увиличте значение

  // Включить светодиоды:
 
  // Этот цикл for() увеличивает переменную на единицу от 0 до 7
  // Затем используется digitalWrite(), чтобы включить светодиод.
  // Затем пауза
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);                
  }

  // Выключить светодиоды:

  // Этот цикл for() уменьшает переменную на единицу от 0 до 7
  // Затем используется digitalWrite(), чтобы выключить светодиод.
  // Затем пауза
 
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, LOW);
    delay(delayTime);
  }
}


/*
oneOnAtATime ()

Эта функция будет шаг за шагом, по очереди, по одному,
включать светодиоды - первый, второй, третий и т.д.
*/

void oneOnAtATime()
{
  int index;
  int delayTime = 1000; // Время (в миллисекундах) для пауз
                       // попробуйте уменьшить или увиличить
  
  // Этот цикл for() увеличивает переменную на единицу от 0 до 7
  // Т.е. "переменная", включили, пауза, выключили, прибавили
  // в переменную единицу, включили, пауза, выключили и так до 7,
  // затем все с начала
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);	// включить светодиод
    delay(delayTime);		// маленькая пауза, или большая
    shiftWrite(index, LOW);	// выключить светодиод
  }
}

 
/*
pingPong()

Эта функция будет шаг за шагом, по очереди, по одному,
включать светодиоды - первый, второй, третий и так до
восьмого, затем действие пойдет в обратном порядке 7, 6,
5, 4, 3, 2, 1 и все повторится, как в игре пинг-понг.
*/

void pingPong()
{
  int index;
  int delayTime = 100; // Время (в миллисекундах) для пауз
                       // попробуйте уменьшить или увеличить
  
  // Снова тот же цикл for() увеличивает переменную на единицу
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);	// включить светодиод
    delay(delayTime);		// маленькая пауза
    shiftWrite(index, LOW);	// выключить светодиод
  }

  // Снова цикл for() с уменьшением переменной
  
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, HIGH);	// включить светодиод
    delay(delayTime);		// маленькая пауза
    shiftWrite(index, LOW);	// выключить светодиод
  }
}


/*
randomLED()

Функция включает по одному светодиоду в случайной
последовательности, также случайна длительность свечения
*/

void randomLED()
{
  int index;
  int delayTime = 1000; // Время (в миллисекундах) для пауз
                       // попробуйте уменьшить или увеличить
  
  // Далее используется функция random(), которая возвращает
  // случайное (точнее сказать псевдослучайное) число. Как
  // ее использовать. См https://arduino.ru/Reference/Random
  
  index = random(8); // Выбрать случайное число между 0 и 7
  
  shiftWrite(index, HIGH);	// включить светодиод
  delay(delayTime);		// маленькая пауза
  shiftWrite(index, LOW);	// выключить светодиод
}


/*
marquee()

Функция имитирует эффек бегущих огней
*/

void marquee()
{
  int index;
  int delayTime = 2000; // Время (в миллисекундах) для пауз
                       // попробуйте уменьшить или увеличить
  
  // Шаг - через три светодиода 1-ый и 5-ый, 2-ой и 6-ой...
  // То есть Мы будем включать каждый четвертый светодиод
  
  for(index = 0; index <= 3; index++)
  {
    shiftWrite(index, HIGH);    // включить светодиод
    shiftWrite(index+4, HIGH);  // увеличить на 4 и включить
    delay(delayTime); // Пауза, чтобы замедлить последовательность
    shiftWrite(index, LOW);	// выключить светодиод
    shiftWrite(index+4, LOW);  // увеличить на 4 и выключить
  }
}


/*
binaryCount()

Числа хранятся во внутренней памяти Arduino в виде массивов "бит".
Каждый бит может быть либо логической единицей (HIGH - высокий
потенциал, либо логическим нулем (LOW - низкий потенциал). Так же,
как десятичные числа, которые мы используем каждый день, положение
занимаемой позиции каждого бита влияет на общее число (сумму в байте).

Для примера: В двоичной системе положение бита в первой позиции
(первая позиция в данном случае "0" см. таблицу ниже, вторая "1",
третья "2" и т.д) будет соответствовать "1" в десятичной системе
исчисления, положение во 2 позиции будет соответствовать двойке
в десятичной, положение в третьей позиции буде соответствовать 4
в десятичной, следующая 8, 16, 32 и т.д )).

Таблица. Соответствие позиции битов десятичной системы к двоичной:

0              1
1              2
2              4
3              8
4              16
5              32
6              64
7              128

Пример 1:
Чтобы создать цифру пять нужно включить бит в первой позиции, т.е
записать в него единицу (HIGH), и бит в третьей позиции, записать
в него тоже единицу (HIGH). Складываем 1+4:

0=HIGH           1
1=LOW            2
2=HIGH           4
3=LOW            8
4=LOW            16
5=LOW            32
6=LOW            64
7=LOW            128

Пример 2:
Чтобы создать цифру 10 нужно включить бит во второй позиции, т.е
записать в него единицу, и бит в четвертой позиции, тоже записать
в него единицу. Складываем 2+8:

0=LOW            1
1=HIGH           2
2=LOW            4
3=HIGH           8
4=LOW            16
5=LOW            32
6=LOW            64
7=LOW            128

Пример 3:
Чтобы создать цифру 20 нужно включить бит в третьей позиции, т.е
установить его в HIGH, и бит в пятой позиции, тоже HIGH.
Складываем 4+16:

0=LOW            1
1=LOW            2
2=HIGH           4
3=LOW            8
4=HIGH           16
5=LOW            32
6=LOW            64
7=LOW            128

Если все биты LOW, это соответствует 0. Если все биты HIGH (включены),
чило равно 255.

Таким образом можно записать любое число от 0 до 255. Именно столько
помещается в 1 byte. 

Пример 4: число 200 (8+64+128):
11001000 

Пример 5: число 0:
00000000

Пример 6: число 255:
11111111


Эта функция будет увеличивать переменную "data" на 1 шаг за шагом
от 0 до 255. Достигнув 255 начнет все сначала и т.д. Из переменной,
данные передаются в регистр сдвига, после чего появляюются на
его выходах. Индикатором служат светодиоды. Если их выставить в
ряд, они покажут содержание переменной "data", т.е шаблон из
восьми бит, которые и составляют 1 байт.

См http://www.arduino.cc/playground/Code/BitMath для получения
дополнительной информации о двоичных чисел.
*/

void binaryCount()
{
  int delayTime = 1000; // Время (в миллисекундах) для пауз
                       // попробуйте уменьшить или увиличить
  
  // Отправить байт данных в регистр сдвига:

  shiftOut(datapin, clockpin, MSBFIRST, data);

  // Защелкиваем данные для того чтобы они появились на выходах:

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  // Увиличиваем данные на единицу и повторяем! 
  // Из за того что тип "byte" это 8-ми битное, беззнаковое,
  // целое число, в диапазоне от 0 до 255, мы не може добавить
  // более 255-и, в противном случае все "завалится" обратно
  // в 0, все начнется сначала.
  

  data++;

  // Задержка, для того чтобы вы что-то успели рассмотреть:

  delay(delayTime);
}

