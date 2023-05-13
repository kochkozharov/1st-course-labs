# Отчёт по заданию №8 по курсовому проекту по циклу дисциплин «Информатика»

<b>Студент группы:</b> <ins>М80-108Б-22 Кочкожаров Иван Вячеславович, № по списку 25</ins> 

<b>Контакты e-mail:</b> <ins>tegusigaalpa@gmail.com</ins>

<b>Работа выполнена:</b> «12» <ins> мая </ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> 5 </ins>

<b>Отчет сдан</b> «14» <ins>мая</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> 5 </ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема
Линейные списки

## 2. Цель работы
Составить и отладить программу на языке Си для обработки линейного списка

## 3. Задание
Составить и отладить программу на языке Си для обработки линейного списка заданной организации с отображением
списка на динамические структуры. Навигацию по списку следует реализовать с применением
итераторов. Предусмотреть выполнение одного нестандартного и четырех стандартных действий:
1. Печать списка.
2. Вставка нового элемента в список.
3. Удаление элемента из списка.
4. Подсчет длины списка.

ТИП ЭЛЕМЕНТА СПИСКА: *ссылочный.

ВИД СПИСКА: кольцевой однонаправленный;

НЕСТАНДАРТНОЕ ДЕЙСТВИЕ: переставить элементы списка в обратном порядке;

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
Пустой кольцевой однонаправленный список создается со специальнымтерминатором. Структура "Связный список" состоит из следующих полей:  ссылка на терминатор, размер узла и количество узлов. Такая организация позволяет хранить только одну ссылку в структуре, а так же реализовать итераторы как в C++. Узлы являются flexible array member структурами с ссылкой на следующий. Запись и чтение из узлов происходит с помощью memcpy. Это позволяет сделать список типонезависимым, а при его создании нужно передавать размер типа, который собираемся в нем хранить. Уникальная возможность моего однонаправленного списка - вставка в конец за O(1). Осуществляется посредством того, что ссылка на последний узел хранится в терминаторе и постоянно обновляется.
## 7. Сценарий выполнения работы:
```
ivan@asus-vivobook ~/f/f/kp8 (master)> ./main
push front G
push front a
push front j
push back q
push front w
push back p
w
j
a
G
q
p
-----------------
reverse:
p
q
G
a
j
w
back and front
p
w
-----------------
work with iterators
created iterator pointing to 1st node
p
node pointed by iterator value is set to A
iterator pointing to the next node
q
iterator pointing to the next node
G
iterator pointing to the next node
a
inserted K after iterator
iterator pointing to the next node
K
erased node after iterator
iterator pointing to the next node
w
iterator pointing to the next node
Invalid argument
iterator pointing to the next node
A
-----------------
result
A
q
G
a
K
w
```

## 8. Распечатка протокола
```
ivan@asus-vivobook ~/f/f/kp8 (master)> make clean all
rm -rf *.o main
clang -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c list.c -o list.o
clang -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c main.c -o main.o
clang  list.o main.o  -o main
```

## 9. Замечания автора по существу работы 

### Защита
<b>[Контест (Div. 2)](https://codeforces.com/contest/1820/submission/202227648)</b>

<b>[Дорешка](https://codeforces.com/contest/1820/submission/205470455)</b>

## 10.Вывод работы:
После выполнения работы, были получены навыки обощенного программирования на C посредством void-указателей и memcpy, написания макросов, а так же создания и использования итераторов в собственных абстрактных типах данных. Улучшено понимание механизмов выделения памяти в C, а именно, стало очевидным различие между аллокацией "в стеке" (автоматиечская) и "в куче" (динамическая).

<b>Подпись студента:</b> ________________