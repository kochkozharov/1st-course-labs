# Отчёт по заданию №6 по курсовому проекту по циклу дисциплин «Информатика»

<b>Студент группы:</b> <ins>М80-108Б-22 Кочкожаров Иван Вячеславович, № по списку 25</ins> 

<b>Контакты e-mail:</b> <ins>tegusigaalpa@gmail.com</ins>

<b>Работа выполнена:</b> «31» <ins> мая </ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> 5 </ins>

<b>Отчет сдан</b> «1» <ins>июня</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> 5 </ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема

Обработка последовательной файловой структуры на языке Си

## 2. Цель работы

Разработать последовательную структуру данных для представления простейшей базы данных на
файлах в СП Си в соответствии с заданным вариантом.

## 3. Задание

Составить программу генерации внешнего
нетекстового файла заданной структуры, содержащего представительный набор записей.
Распечатать содержимое сгенерированного файла в виде таблицы и выполнить над ним заданное действие для
запроса `p` и распечатать результат.

Действие по выборке данных из файла оформить в виде отдельной программы с параметрами запроса,
вводимыми из стандартного входного текстового файла, или получаемыми из командной строки UNIX.
Второй способ задания параметров обязателен для работ, оцениваемых на хорошо и отлично. Параметры
задаются с помощью ключей `–f [name]` (имя обрабатываемого файла) или `–p [parameter]` (параметры конкретного варианта
задания). Получение параметров из командной строки производится с помощью стандартных библиотечных
функций `argс` и `argv`.

Cтруктуры данных и константы, совместно используемые программами, следует вынести в отдельный
заголовочный файл.

В процессе отладки и тестирования рекомендуется использовать команды обработки текстовых файлов
ОС UNIX и переадресацию ввода-вывода. Сгенерированные и отформатированные тестовые данные
необходимо заранее поместить в текстовые файлы и распечатывать при протоколировании. Рекомендуется
подобрать реальные или правдоподобные тестовые данные. Число наборов тестовых данных должно быть не
менее трёх. Имя файла с бинарными данными является обязательным параметром второй программы.

**Содержимое и структура файла:**

Информация о пассажирах аэропорта: фамилия, инициалы, количество вещей, общий вес вещей,
пункт назначения, время вылета, наличие пересадок, сведения о детях.

**Действие**

Найти пассажиров, имеющих более p вещей.

## 4. Оборудование:

<b>Процессор:</b> AMD Ryzen 5 5600H (12) @ 3.300GHz 

<b>ОП:</b> 16gb

<b>SSD:</b> 512 Gb SSD

<b>Монитор:</b> 15.6" - 1920*1080

<b>Графика:</b> Radeon RX Vega 7

## 5. Программное обеспечение:

<b>Операционная система семейства:</b> Gentoo Linux x86_64

<b>Интерпретатор команд:</b> fish, version 3.4.0

<b>Система программирования:</b> -

<b>Редактор текстов:</b> Visual Studio Code версия 1.76.0

## 6. Идея, метод, алгоритм решения:

Для работы с бинарным файлом требуется два исполняемых файла: `pdump` и `pselect`. Первый принимает имя файла, в который будет дописано бинарное представление структуры из Си, а далее запрашивается пользовательский ввод полей структуры. Если хотя бы одно поле введено некоректно, то программа завершается аварийно и ничего не сохраняет в файл. Вторая программа требует два ключа с параметрами: `-f [filename]` и `-p [parameter]` и соовершает запрос к бинарнорму файлу `filename` (созданного прошлой утилитой) c параметром `parameter`. Так же есть опциональный ключ `-v`. Если утилита вызвана с ним, то будет выведена все содержимое бинарной базы данных в человекочитаемом виде. Эти два бинарника делят между собой объектный файл, содержащий тип Пассажир с функциями выборки пассажиров и отображения, соответсвующий заголовок `passeneger.h` подключается к исходникам обеих утилит. У функций выборки и отображения параметризован ввод/вывод посредством того, что они принимают функции ввода и вывода, которые реализуются в `select_passenger.c`. Это делает код более модифицирумым.

## 7. Сценарий выполнения работы:

```
ivan@asus-vivobook ~/f/f/cp6 (master)> bin/pdump dump.dat
Last name: Petrov
Initials: SD
Amount of items: 15
Total weight of items: 34
Destination: Kaliningrad
Departure Time (e.g. 01.01.2023 16:30): 24.06.2023 10:00 
Has transfers? (y/n): n
Amount of children: 2
Passenger successfully dumped!
ivan@asus-vivobook ~/f/f/cp6 (master)> bin/pselect --help 
Usage: bin/pselect -f FILE -p PARAMETER [-v]
ivan@asus-vivobook ~/f/f/cp6 (master)> bin/pselect -f dump.dat -p10 -v
lastName = Teztxz
initials = UQ
amountOfItems = 5
totalWeightOfItems = 50
destination = Moscow
departureTime = 14.02.2023 14:25
hasTransfers = true
amountOfChildren = 2
----------------------------------
lastName = Hijstard
initials = UR
amountOfItems = 34
totalWeightOfItems = 56
destination = Jakarta
departureTime = 15.01.2023 00:00
hasTransfers = false
amountOfChildren = 1
----------------------------------
lastName = Kodd
initials = IU
amountOfItems = 3
totalWeightOfItems = 30
destination = Japan
departureTime = 01.01.2023 16:30
hasTransfers = true
amountOfChildren = 0
----------------------------------
lastName = Ivan
initials = YX
amountOfItems = 10
totalWeightOfItems = 25
destination = Orel
departureTime = 14.03.2024 03:03
hasTransfers = false
amountOfChildren = 0
----------------------------------
lastName = Petrov
initials = SD
amountOfItems = 15
totalWeightOfItems = 34
destination = Kaliningrad
departureTime = 24.06.2023 10:00
hasTransfers = false
amountOfChildren = 2
----------------------------------
passengerName = Hijstard U.R.
passengerName = Petrov S.D.
ivan@asus-vivobook ~/f/f/cp6 (master)> bin/pselect -f dump.dat -p5
passengerName = Hijstard U.R.
passengerName = Ivan Y.X.
passengerName = Petrov S.D.
```

## 8. Распечатка протокола

```
ivan@asus-vivobook ~/f/f/cp6 (master)> make clean all
rm -rf bin/*.o bin/pdump bin/pselect
mkdir -p bin
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c passenger.c -o bin/passenger.o
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c dump_passenger.c -o bin/dump_passenger.o
gcc  bin/passenger.o bin/dump_passenger.o  -o bin/pdump
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c select_passenger.c -o bin/select_passenger.o
gcc   bin/passenger.o bin/select_passenger.o   -o bin/pselect
```

## 9. Замечания автора по существу работы 

### Защита

<b>Контест (Div. 2): </b>
<b>[A](https://codeforces.com/contest/1832/submission/205601519)</b>
<b>[B](https://codeforces.com/contest/1832/submission/207907845)</b>
<b>[C](https://codeforces.com/contest/1832/submission/207951736)<b>

## 10.Вывод работы:

После выполнения работы, были получены навыки обработки бинарных файлов в Си и написания сложных Makefile-ов, а так же строгой обработки ползовательского ввода.

<b>Подпись студента:</b> ________________


