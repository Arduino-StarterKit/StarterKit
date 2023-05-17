
//  Код программы для опыта №6:

// *********************** ФОТОРЕЗИСТОР *****************************

//  Использование фоторезистора (датчика освещенности) для управления
//  светодиодом.

//  Подключение оборудования:

//  Фоторезистор:
//  Подсоедините один вывод фоторезистора к питанию +5 Вольт (5V).
//  Другой вывод фотрезистора к Аналоговому порту 0 (ANALOG pin 0).
//  Подсоедините резистор 10 КОм (коричн., черн., оранж.)
//  между Аналоговом портом 0 и землей (GND).

// 	Такая конструкция называется делителем напряжения, она состоит из
// 	двух резисторов, в данном случае один из которых - фоторезистор.
// 	Выходной сигнал делителя будет поступать на аналоговый вход Arduino (pin 0),
// 	и будет изменяться в зависимости от меняющегося освещенности фоторезистора.

//  Светодиод:
// 	Подсоедините положительный вывод (длинная ножка) светодиода
//  к цифровому порту 9 (pin 9) платы Arduino. Для того чтобы Arduino
// 	могла плавно изменять его яркость, он должен быть подключен к ШИМ,
// 	напомним ШИМ это Широтно Импульсная Модуляция, эти порты помечены
// 	на плате "~".

// 	Подсоедините отрицательный вывод (короткая ножка) светодиода к
// 	резистору 220 Ом. (красн., красн., черн.)
// 	Подсоедините другой вывод резистора к Земле (GND).

//  Как обычно, мы создадим константы с именами для используемых портов.
//  Это позволит сделать код более понятным.

const int sensorPin = 0;
const int ledPin = 9;

// А также создадим глобальные переменные для уровней яркости
// high (высокий), low (низкий):

int lightLevel, high = 0, low = 1023;


void setup()
{
  // Укажем Arduino, что порт управления светодиодом, - исходящий (Нам не
  // нужно делать ничего особенного, чтобы использовать аналоговый вход).

  pinMode(ledPin, OUTPUT);
  // Serial.begin(9600); // для отладки, чтобы увидеть показания датчиков
  // через "монитор порта"
}


void loop()
{
  // Для того чтобы измерить напряжение, идущее с делителя напряжения
  // (фоторезистор - резистор), как и  в прошлых опытах, мы будем
  // использовать функцию analogRead(). Диапазон чисел с которыми работает
  // функция находится в пределах от 0 (0 вольт) и 1023 (5 вольт).
  // Но! Управлением яркостью светодиода занимается функция analogWrite(),
  // у нас возникают не большие сложности, так как она использует
  // диапазон от от 0 до 255..

  lightLevel = analogRead(sensorPin);

  // Эту проблему можно решить с помощью двух полезных функций под названием
  // map() и constrain():
  // Функция map() может преобразовывать один диапазон значений
  // в другой. К примеру - мы указываем map() в параметрах, диапазон "из" 0-1023
  // "в" 0-255, она преобразует первый больший диапазон во второй, более мелкий.
  // Так 0 останется 0, а 1023 станет 255, средние значения - 500 станет ~ 125.

  // lightLevel = map(lightLevel, 0, 1023, 0, 255);

  // Поскольку map() может столкнуться с числами за пределами диапазона,
  // скажем или больше, или меньше, или даже с отрицательными, - она просто
  // сделает свою работу "не моргнув глазом" и будет права.
  // Поэтому нужно за ранее подготовиться к такому повороту событий, для этого
  // можно, и даже нужно использовать еще одну функцию - constrain().
  // Функция constrain() проверит содержится ли число в заданном диапазоне.
  // Если число выше диапазона, он будет уменьшено до самого большого,
  // а если число ниже диапазона, он будет увеличенно до самого низкого
  // Пример:  если constrain() столкнулось с числами 1024, 1025, 1026.., она
  // их преобразует в 1023, 1023, 1023..). С отрицательными числами она сделает
  // тоже самое, т.е все отрицательные станут 0. Если числа находится в пределах
  // диапазона, они станется теми же самым.

  // lightLevel = constrain(lightLevel, 0, 255);

  // Еще одна вещь, о которой стоит задуматься. Схема, которую мы
  // сделали не будет работать в полную силу, потому что изменение освещенности
  // не так сильно меняет сопротивление фоторезистора, как нам хотелось бы, а
  // следовательно и ток на sensorPin() (делителя напряжения).
  // Это будет меньший диапазон чем 0-1023, он будет приблизительно от 300 (темно)
  // до 800 (светло). Если мы просто отдадим эти значения map(), светодиод конечно
  // изменит яркость, но это никогда не будут максимальные значения.

  // Изменить это можно двумя способами, каждый из которых представляет из
  // себя функцию расположенную ниже: manualTune() и autoTune().
  // Для того чтобы задействовать оду из них - раскомментируйте одну и
  // закомментируйте другую. Выбор за вами!

  manualTune();  // ручное изменение диапазона от светлого к темному

  // autoTune();  // автоматическое - пусть Arduino все сделает за нас!

  // Вышеупомянутые функции будут изменять "lightLevel", до максимальных
  // значений от "Полностью Вкл" к "Полному Выкл". И это значит, что теперь
  // мы сможем регулировать яркость светодиода в широких пределах:

  analogWrite(ledPin, lightLevel);

  // Выражение выше, будет изменять яркость светодиода вместе с уровнем
  // освещенности. Чтобы сделать наоборот, заменить в analogWrite(ledPin, lightLevel)
  // "lightLevel" на "255-lightLevel". Теперь у нас получился ночник!

  // для отладки, чтобы увидеть показания датчиков через "монитор порта",
  // раскомментируйте следующие 3 строчки
  // Serial.print(lightLevel);     // вывод данных с фоторезистора (0-1023)
  // Serial.println("");           // возврат каретки
  // delay(500);                   // пауза
}


void manualTune()
{
  // Как мы упоминали выше, фоторезистор не в состоянии менять сопротивление, в
  // зависимости от освещения, в широких пределах, а значит схемка, которую мы
  // создали, не будет перекрывать весь диапазон от 0 до 1023. Скорее всего весь
  // он будет от 300 темно, до 800 (светло). Поэтому если выполнить этот скетч
  // как есть, то видимые изменения яркости светодиода конечно видны будут, но
  // это не будут максимальные значения.

  // В качестве эксперимента мы изменим параметры, и скормим их функции map().
  // Сначала попробуем полный спектр от 0 до 1023, а потом изменим его на 300 и 800.
  // Если светодиод все же не загорается в полную силу, увеличте большее число.
  // Если светодиод полностью не выключается, уменьшайте меньшее число.

  // Не забудьте, изменения не должны выходить за пределы диапазона от 0 до 1023!

  lightLevel = map(lightLevel, 300, 800, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

  // Теперь возвратимся к main loop(), и пошлем lightLevel светодиоду.
}


void autoTune()
{
  // Как мы, уже не однократно упоминали, фоторезистор не в состоянии менять
  // сопротивление, в зависимости от освещения, в широких пределах - весь
  // диапазон будет иметь границы, примерно от 300 темно, до 800 (светло).

  // В функции manualTune() вам придется неоднократно изменять цифры в ручную и
  // запускать программу снова, и снова пока она не заработает так как должна.
  // Но почему мы должны делать эту работу в ручную? У Вас же есть компьютер,
  // который просто обязан выполнить такую работу за нас!

  // В этой функции, Arduino будет отслеживать самые высокие и самые низкие
  // значения, которые мы читаем из analogRead().

  // Если Вы посмотрите в начало программы, то увидите, что мы специально
  // выбрали LOW(НИЗКИЙ)=1023, т.е показания датчика гарантированно уместятся
  // в заданные пределы. Таким образом мы надеемся что ничего не упустим.

  if (lightLevel < low)   // если уровень "lightLevel" меньше 1023, то присвоим
  { // константе "low" новое значение, которое и будет
    low = lightLevel;     // теперь самым "низким" ~ 800
  }

  // Тоже самое мы сделаем и с "HIGH" ~ 200:

  if (lightLevel > high)
  {
    high = lightLevel;
  }

  // Теперь, когда мы определили самые высокие и самые низкие значения, мы
  // можем "отдать" их непосредственно функции map(). И никакое ручное
  // изменение не потребуется!

  // Здесь есть один маленький баг - мерцание светодиода, чтобы этого
  // не происходило добавим небольшие смещения, чтобы уменьшить границы:

  lightLevel = map(lightLevel, low + 0, high - 30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

  // Теперь возвратимся к main loop(), и пошлем lightLevel светодиоду.
}
