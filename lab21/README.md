# Отчёт по лабораторной работе №21 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Кочкожаров Иван Вячеславович, № по списку 25</ins> 

<b>Контакты e-mail:</b> <ins>tegusigaalpa@gmail.com</ins>

<b>Работа выполнена:</b> «25» <ins> марта </ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> ? </ins>

<b>Отчет сдан</b> «25» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> ? </ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема
Программирование на интерпретируемых командных языках

## 2. Цель работы
Изучение и освоение интерпретируемых языков программирования BASH и Python для написания скриптов для работы над файлами.

## 3. Задание 
Рекурсивный обход, подсчет числа различных суффиксов в указанном каталоге и вывод уникальных суффиксов.
### Дополнительные условия
1. Если параметры опущены, то устанавливаются некоторые стандартные значения параметров. 
2. Если указаны ключи -h или --help, то выводится подсказака (спецификация программы).

## 4. Оборудование:
<b>Процессор:</b> AMD Ryzen 5 5600H (12) @ 3.300GHz 

<b>ОП:</b> 16gb

<b>SSD:</b> 512 Gb SSD

<b>Монитор:</b> 15.6" - 1920*1080

<b>Графика:</b> Radeon RX Vega 7

## 5. Программное обеспечение:
<b>Операционная система семейства:</b> Gentoo Linux x86_64

<b>Интерпретатор команд:</b> bash версия 5.1.16

<b>Система программирования:</b> -

<b>Редактор текстов:</b> Visual Studio Code версия 1.76.0

## 6. Идея, метод, алгоритм решения:

1. Рассматриваем введенные аргументы. Если их меньше, чем 1, то программа установит некоторые стандартные значения (см. -h, чтобы узнать какие).
2. Рассматриваем введенные аргументы. Если параметры некорректны, программа поднимет исключение с описанием ошибки.
3. Программа проходится по директории, получает и сохраняет суффиксы, затем сортирует их и выводит уникальные с их количеством. Вывод будет отсортирован.


## 7. Сценарий выполнения работы:

Сначала будет написан скрипт на BASH, затем он будет переписан на Python.

## 8.Пример работы команд:

```
ivan@asus-vivobook ~/focs/fundamentals-of-computer-science-kochkozharov/lab21 $ ./unique_suffix.sh ~/Downloads/
     43 pdf
     16 docx
     10 png
      8 HEIC
      4 md
      4 jpg
      4 diff
      3 zip
      3 rar
      3 c
      2 html
      2 SLDPRT
      1 txt
      1 ipynb
      1 img
      1 gz
      1 gif
      1 doc
      1 djvu
      1 7z
ivan@asus-vivobook ~/focs/fundamentals-of-computer-science-kochkozharov/lab21 $ ./unique_suffix.py ~/Downloads/
     43 pdf
     16 docx
     10 png
      8 HEIC
      4 diff
      4 md
      4 jpg
      3 rar
      3 zip
      3 c
      2 SLDPRT
      2 html
      1 gz
      1 img
      1 txt
      1 doc
      1 gif
      1 7z
      1 djvu
      1 ipynb
ivan@asus-vivobook ~/focs/fundamentals-of-computer-science-kochkozharov/lab21 $ ./unique_suffix.sh
      1 sh
      1 py
      1 md
ivan@asus-vivobook ~/focs/fundamentals-of-computer-science-kochkozharov/lab21 $ ./unique_suffix.py
      1 sh
      1 md
      1 py
ivan@asus-vivobook ~/focs/fundamentals-of-computer-science-kochkozharov/lab21 $ ./unique_suffix.py -h
unique_suffix.sh [DIR] finds and counts all of the distinct file suffixes in a [DIR] recursively. Default [DIR] is a current directory.
```

## 9. Замечания автора по существу работы 

### Защита

<b>[Контест (Div. 2)](https://codeforces.com/contest/1806/submission/197929363)</b>

<b>[Дорешка](https://codeforces.com/contest/1806/submission/197976614)</b>

## 10.Вывод работы:

После изучения интерпретируемых языков программирования BASH и Python были получены навыки написания скриптов для решения нетривиальных задач по обработке файлов в UNIX.

<b>Подпись студента:</b> ________________