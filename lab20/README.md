# Отчёт по лабораторной работе №20 по курсу “Фундаментальная информатика”

<b>Студент группы:</b> <ins>М80-108Б-22 Кочкожаров Иван Вячеславович, № по списку 25</ins> 

<b>Контакты e-mail:</b> <ins>tegusigaalpa@gmail.com</ins>

<b>Работа выполнена:</b> «11» <ins> марта </ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> ? </ins>

<b>Отчет сдан</b> «11» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> ? </ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема
Стандартные утилиты UNIX для обработки файлов
## 2. Цель работы
Изучение и освоение стандартных утилит UNIX, измения их поведения с помощью ключей, а так же конвеера. Приобретение навыков, необходимых для выполнения курсовых и лабораторных работ в среде UNIX.
## 3. Задание 
Изучение утилит UNIX.
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

<b>Утилиты операционной системы:</b> tar, find, df / wc, dd, grep, tail, tee, head, touch, du, file, gzip, bzip2, tr, cmp, comm, xargs, diff, patch, uniq, sort, cut

## 6. Идея, метод, алгоритм решения:
Для достижения поставленной цели используем утилиту man. Если man-страница будет непонятна, то ищем информацию в Википедии.

## 7. Сценарий выполнения работы:
### Используем следующте команды:

    tar
_работа с архивами_

    find
_поиск файлов по имени и другим свойствам_

    df
_показывает список всех файловых систем по именам устройств, сообщает их размер, занятое и свободное пространство и точки монтирования_

    wc
_вывод числа переводов строк, слов и байт для каждого указанного файла_

    dd
_копирование и конвертация файлов_

    grep
_находит на вводе строки, отвечающие заданному регулярному выражению, и выводит их_

    tail
_вывод нескольких последних строк из файла_

    tee
_выводит на экран, или же перенаправляет выходной поток  (stdout) команды и копирует его содержимое в файл или в переменную_
    
    head
_вывод первых n строк из файла_

    touch
_установка времени последнего изменения файла, также используется для создания пустых файлов_

    du
_оценка занимаемого файлового пространства_

    file
_определения типа файла_

    gzip
_утилита сжатия и восстановления файлов, использующая алгоритм Deflate_

    bzip2
_утилита сжатия и восстановления файлов, использующая алгоритм Барроуза-Уиллера_

    tr
_копирует стандартный входной поток в стандартный выходной, подставляя или удаляя некоторые символы_

    cmp
_сравнивает два файла и, если они различаются, сообщает о первом байте и строке, где было обнаружено различие_

    comm
_читает файл1 и файл2, которые должны быть предварительно лексически отсортированы, и генерирует вывод, состоящий из трёх колонок текста: строки, найденные только в файле файл1; строки, найденные только в файле файл2; и строки, общие для обоих файлов_

    xargs
_берет данные из стандартного ввода или из файла, разбивает их в соответствии с указанными параметрами, а затем передает другой программе в качестве аргумента_

    diff
_сравнение файлов, выводящая разницу между двумя файлами (т.н. patch-файл)_

    patch
_перенос правок (изменений) между разными версиями текстовых файлов, информация о правке обычно содержится в отдельном patch-файле_

    uniq
_вывести или отфильтровать повторяющиеся строки в отсортированном файле_

    sort
_вывод сортированного слияния указанных файлов на стандартный вывод_

    cut
_выборка отдельных полей из строк файла (табуляция - разделитель по умолчанию)_

## 8.Пример работы команд:
### *3 основные утилиты:*
### tar

Изначальное состояние папки ~/tests:
```
ivan@asus-vivobook ~/tests $ tree
.
├── mydir
│   └── file_in_mydir
└── myfile

1 directory, 2 files

```

Создадим архив из файлов (в т.ч. и папок) без сжатия. -c, --create — создать архив; -f, --file — указать имя архива; -v, --verbose — выводить список обработанных файлов.
```
ivan@asus-vivobook ~/tests $ tar -cvf archive.tar mydir myfile
mydir/
mydir/file_in_mydir
myfile
ivan@asus-vivobook ~/tests $ ls
archive.tar  mydir  myfile
```
Создадим новый файл и добавим его к архиву. -r, --append — добавить файлы в конец существующего архива.
```
ivan@asus-vivobook ~/tests $ touch newfile
ivan@asus-vivobook ~/tests $ tar -rf archive.tar newfile
```
Просмотрим содержимое архива. -t, --list — просмотреть содержимое архива. (прим.: порядок ключей имеет значение!)
```
ivan@asus-vivobook ~/tests $ tar -tvf archive.tar
drwxr-xr-x ivan/ivan         0 2023-03-10 02:34 mydir/
-rw-r--r-- ivan/ivan         0 2023-03-10 02:34 mydir/file_in_mydir
-rw-r--r-- ivan/ivan         0 2023-03-10 02:34 myfile
-rw-r--r-- ivan/ivan         0 2023-03-10 02:45 newfile
```
Извлечем сожержимое архива в новую папку. -C — указание каталога.
```
ivan@asus-vivobook ~/tests $ tar -xvf archive.tar -C
archive.tar  mydir/       myfile       newdir/      newfile
ivan@asus-vivobook ~/tests $ tar -xvf archive.tar -C newdir/
mydir/
mydir/file_in_mydir
myfile
newfile
ivan@asus-vivobook ~/tests $ tree newdir/
newdir/
├── mydir
│   └── file_in_mydir
├── myfile
└── newfile

1 directory, 3 files
```

Создадим архив archive.tar.gz из файлов myfile и newfile и каталога mydir и сожмём его с помощью gzip. Сравним размеры архивов с одинаковым содержанием. -a, --auto-compress — дополнительно сжать архив с компрессором который автоматически определить по расширению архива. Если имя архива заканчивается на *.tar.gz то с помощью GZip, если *.tar.xz то с помощью XZ, *.tar.zst для Zstandard и.т.п;

```
ivan@asus-vivobook ~/tests $ tar -cavf archive.tar.gz mydir/ myfile newfile
mydir/
mydir/file_in_mydir
myfile
newfile
ivan@asus-vivobook ~/tests $ du -h archive.tar.gz
4.0K	archive.tar.gz
ivan@asus-vivobook ~/tests $ du -h archive.tar
12K	archive.tar
```

### find
Поиск первых 5 файлов с раширением .c в папке с исходныи кодом Linux. -name - искать по маске имени файла.
```
ivan@asus-vivobook ~ $ find /usr/src/linux-6.1.12-gentoo/ -name '*.c' | head -n 5
/usr/src/linux-6.1.12-gentoo/samples/nitro_enclaves/ne_ioctl_sample.c
/usr/src/linux-6.1.12-gentoo/samples/user_events/example.c
/usr/src/linux-6.1.12-gentoo/samples/kmemleak/kmemleak-test.c
/usr/src/linux-6.1.12-gentoo/samples/vfs/test-statx.c
/usr/src/linux-6.1.12-gentoo/samples/vfs/test-fsmount.c
```
Делаем исполняемыми скрипты BASH и Python в рабочей директории. -type - тип искомого; ```-exec command {} \```; - выполняет над найденными файлами команду command.
```
ivan@asus-vivobook ~/tests $ ls -l
total 0
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f1
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f3
-rw-r--r-- 1 ivan ivan 0 мар 10 21:42 s.sh
-rw-r--r-- 1 ivan ivan 0 мар 10 21:42 script.py
ivan@asus-vivobook ~/tests $ find . \( -name '*.sh' -o -name '*.py' \) -type f -exec chmod 744 {} \;
ivan@asus-vivobook ~/tests $ ls -l
total 0
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f1
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f3
-rwxr--r-- 1 ivan ivan 0 мар 10 21:42 s.sh
-rwxr--r-- 1 ivan ivan 0 мар 10 21:42 script.py
```
Список файлов во всей файловой системе, чей размер больше 50 Мб. -size - размер. (2>/dev/null позволяет игнорировать сообщения об ошибках, например — нет доступа чтения из каталога)
```
ivan@asus-vivobook ~/tests $ find / -size +100M  2>/dev/null
/opt/firefox/libxul.so
/opt/discord/Discord
/opt/vscode/code
/var/cache/distfiles/llvm-project-15.0.7.src.tar.xz
/var/cache/distfiles/linux-6.1.tar.xz
/var/cache/distfiles/rustc-1.66.1-src.tar.xz
/var/cache/distfiles/linux-5.15.tar.xz
/var/cache/distfiles/boost_1_79_0.tar.bz2
/var/cache/distfiles/rust-1.65.0-x86_64-unknown-linux-gnu.tar.xz
/var/cache/distfiles/linux-firmware-20230117.tar.xz
/var/cache/distfiles/noto-20201226.tar.gz
/var/cache/distfiles/linux-firmware-20230210.tar.xz
/var/cache/distfiles/vscode-1.76.0-amd64.tar.gz
/swapfile
/usr/share/genkernel/distfiles/boost_1_79_0.tar.bz2
/usr/lib/rust/1.66.1/lib/librustc_driver-e99e9c4986f9a201.so
/usr/lib/llvm/15/lib64/libLLVM-15.so
/usr/bin/telegram-desktop
/home/ivan/Downloads/Telegram Desktop/20 лаба.mkv
/sys/devices/pci0000:00/0000:00:08.1/0000:03:00.0/resource0_wc
/sys/devices/pci0000:00/0000:00:08.1/0000:03:00.0/resource0
/proc/kcore
```

Перечислить все файлы в домашнем каталоге, исключив из поиска некоторые каталоги. -path - искать по маске абсолютного имени файла; -not - отрицание аргумента; -a - логическое И для аргументов.
```
ivan@asus-vivobook ~/tests $ find ~ -type f -not -path '*/.*/*' -a -not -path '*/Downloads/Telegram Desktop/*'
/home/ivan/.bash_history
/home/ivan/.bash_logout
/home/ivan/.xinitrc
/home/ivan/Downloads/l20-2012.djvu
/home/ivan/Downloads/dwm-noborderfloatingfix-6.2.diff
/home/ivan/Downloads/dwm-noborder-6.2.diff
/home/ivan/Downloads/dwm-systray-6.4.diff
/home/ivan/Downloads/dwm-pertag-6.2.diff
/home/ivan/Downloads/screenshot.png
/home/ivan/Downloads/299003-vms-bashnya.jpg
/home/ivan/Downloads/pt06.pdf
/home/ivan/.gitconfig
/home/ivan/bak/package.use/gentoo-sources
/home/ivan/bak/package.use/picom
/home/ivan/bak/package.use/systemd
/home/ivan/bak/package.use/pipewire
/home/ivan/bak/package.use/ntfs3g
/home/ivan/bak/package.use/lvm2
/home/ivan/bak/package.use/vlc
/home/ivan/bak/package.use/zathura-meta
/home/ivan/bak/package.use/00cpu-flags
/home/ivan/bak/package.use/._cfg0000_zathura-meta
/home/ivan/bak/package.use/pulseaudio
/home/ivan/.lesshst
/home/ivan/pdfs/university/l20-2012.djvu
/home/ivan/pdfs/university/Бортаковский А.С., Пегачкова Е.А. Типовые задачи по линейной алгебре. Часть 2.pdf
/home/ivan/pdfs/university/pt06.pdf
/home/ivan/.bash_profile
/home/ivan/tests/script.py
/home/ivan/tests/f1
/home/ivan/tests/f3
/home/ivan/tests/s.sh
/home/ivan/tests/f2
/home/ivan/.python_history
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/.gitignore
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/lab20/README.md
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/LICENSE
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/README.md
/home/ivan/focs/contests/test.py
/home/ivan/.bashrc
/home/ivan/.Xauthority
/home/ivan/.viminfo
/home/ivan/wallpapers/gentoo-cow-gdm-remake-1920x1080.png
/home/ivan/.fehbg
```
Перечислить файлы, измененные в последние два дня в домашнем каталоге, исключив из поиска некоторые каталоги. -mtime - время последнего изменения файла (в днях).
```
ivan@asus-vivobook ~/tests $ find ~ -type f -not -path '*/.*/*' -a -not -path '*/Downloads/Telegram Desktop/*' -a -mtime -2
/home/ivan/.bash_history
/home/ivan/Downloads/000077699_ПриказОЗачисленииПереводом_186471.pdf
/home/ivan/bak/package.use/vlc
/home/ivan/bak/package.use/._cfg0000_zathura-meta
/home/ivan/.lesshst
/home/ivan/tests/script.py
/home/ivan/tests/f1
/home/ivan/tests/f3
/home/ivan/tests/s.sh
/home/ivan/tests/f2
/home/ivan/.python_history
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/.gitignore
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/lab20/README.md
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/LICENSE
/home/ivan/focs/fundamentals-of-computer-science-kochkozharov/README.md
/home/ivan/focs/contests/test.py
/home/ivan/.Xauthority
/home/ivan/.viminfo
/home/ivan/.fehbg
```

### df
Отобразить список всех файловых систем по именам устройств с их размером, занятым и свободным пространством и точки монтирования. -h, --human-readable - oтобразит размер в человеко-читаемом формате, размерностью 1024, добавив названия единиц (Kибибайт, Mебибайт, Гибибайт, Tебибайт)
```
ivan@asus-vivobook ~/tests $ df -h
Filesystem      Size  Used Avail Use% Mounted on
none            7.6G  1.4M  7.6G   1% /run
udev             10M     0   10M   0% /dev
tmpfs           7.6G   13M  7.6G   1% /dev/shm
/dev/dm-1       251G   25G  214G  11% /
tmpfs           7.6G  3.2M  7.6G   1% /tmp
/dev/nvme0n1p1 1020M  132M  889M  13% /boot
tmpfs           1.6G   12K  1.6G   1% /run/user/1000
```
-H, --si - отобразит размер в человеко-читаемом формате, в единицах СИ, размерностью 1000, добавив названия единиц (Kилобайт, Mегабайт, Гигабайт, Tерабайт)
```
ivan@asus-vivobook ~/tests $ df -H
Filesystem      Size  Used Avail Use% Mounted on
none            8.1G  1.4M  8.1G   1% /run
udev             11M     0   11M   0% /dev
tmpfs           8.1G   14M  8.1G   1% /dev/shm
/dev/dm-1       270G   27G  230G  11% /
tmpfs           8.1G  3.4M  8.1G   1% /tmp
/dev/nvme0n1p1  1.1G  139M  932M  13% /boot
tmpfs           1.7G   13k  1.7G   1% /run/user/1000
```
-a, --all -  включает в список файловых систем те, которые имеют размер в 0 блоков, и которые по умолчанию опускаются. Такие файловые системы обычно являются псевдо-файловыми системами специального назначения.
```
ivan@asus-vivobook ~/tests $ df -ah
Filesystem      Size  Used Avail Use% Mounted on
proc               0     0     0    - /proc
none            7.6G  1.4M  7.6G   1% /run
udev             10M     0   10M   0% /dev
devpts             0     0     0    - /dev/pts
tmpfs           7.6G   13M  7.6G   1% /dev/shm
sysfs              0     0     0    - /sys
/dev/dm-1       251G   25G  214G  11% /
cgroup2            0     0     0    - /sys/fs/cgroup
efivarfs           0     0     0    - /sys/firmware/efi/efivars
bpf                0     0     0    - /sys/fs/bpf
systemd-1          -     -     -    - /proc/sys/fs/binfmt_misc
mqueue             0     0     0    - /dev/mqueue
debugfs            0     0     0    - /sys/kernel/debug
tracefs            0     0     0    - /sys/kernel/tracing
hugetlbfs          0     0     0    - /dev/hugepages
ramfs              0     0     0    - /run/credentials/systemd-sysctl.service
fusectl            0     0     0    - /sys/fs/fuse/connections
ramfs              0     0     0    - /run/credentials/systemd-tmpfiles-setup-dev.service
tmpfs           7.6G  3.2M  7.6G   1% /tmp
/dev/nvme0n1p1 1020M  132M  889M  13% /boot
ramfs              0     0     0    - /run/credentials/systemd-tmpfiles-setup.service
tmpfs           1.6G   12K  1.6G   1% /run/user/1000
binfmt_misc        0     0     0    - /proc/sys/fs/binfmt_misc
```
-i, --inodes - вместо информации о блоках выдаётся информация об использовании inode'ов в файловой системе. Inode содержит информацию о файле: владелец, права доступа, временные штампы и местоположение на диске. 
```
ivan@asus-vivobook ~/tests $ df -i
Filesystem       Inodes  IUsed    IFree IUse% Mounted on
none            1971907    883  1971024    1% /run
udev            1970279    499  1969780    1% /dev
tmpfs           1971907     47  1971860    1% /dev/shm
/dev/dm-1      16777216 669337 16107879    4% /
tmpfs           1048576     27  1048549    1% /tmp
/dev/nvme0n1p1        0      0        0     - /boot
tmpfs            394381     39   394342    1% /run/user/1000
```
-T, --print-type - выдавать тип для каждой файловой системы.
```
ivan@asus-vivobook ~/tests $ df -hT
Filesystem     Type      Size  Used Avail Use% Mounted on
none           tmpfs     7.6G  1.4M  7.6G   1% /run
udev           devtmpfs   10M     0   10M   0% /dev
tmpfs          tmpfs     7.6G   13M  7.6G   1% /dev/shm
/dev/dm-1      ext4      251G   25G  214G  11% /
tmpfs          tmpfs     7.6G  3.2M  7.6G   1% /tmp
/dev/nvme0n1p1 vfat     1020M  132M  889M  13% /boot
tmpfs          tmpfs     1.6G   12K  1.6G   1% /run/user/1000
```

Также утилиту df можно использовать для получения информации о том, к какой файловой системе относится какой-либо каталог файл.
```
ivan@asus-vivobook ~/tests $ df -hT .
Filesystem     Type  Size  Used Avail Use% Mounted on
/dev/dm-1      ext4  251G   25G  214G  11% /
```
### *20 дополнительных утилит*
### wc
_вывод числа переводов строк, слов и байт для каждого указанного файла. -L - длина самой длинной строки._
```
ivan@asus-vivobook ~/tests $ cat f1
dgadsgasdf, fads
edhrsheatrjyjktykt  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
asdf
asdg arg 
ivan@asus-vivobook ~/tests $ wc f1 f2
  5  14 101 f1
  0   0   0 f2
  5  14 101 total
ivan@asus-vivobook ~/tests $ wc -L f1
67 f1
```

### dd
_копирование и конвертация файлов. У утилиты много возможностей, в примере создается пустой файл размером 100MB и выводятся первые 256 байтов другого файла_
```
ivan@asus-vivobook ~/tests $ dd if=/dev/zero of=test bs=1M count=100
100+0 records in
100+0 records out
104857600 bytes (105 MB, 100 MiB) copied, 0.0670762 s, 1.6 GB/s
ivan@asus-vivobook ~/tests $ du -h test 
100M    test
```
```
ivan@asus-vivobook ~/tests $ dd if=f1 of=/dev/stdout bs=1 count=10 
dgadsgasdf10+0 records in
10+0 records out
10 bytes copied, 6.5764e-05 s, 152 kB/s
```

### grep
_находит на вводе строки, отвечающие заданному регулярному выражению, и выводит их. -c - подсчет отвечающих строк._
```
ivan@asus-vivobook ~/tests $ cat f1
df, fads
edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
asdf
asdg arg
ivan@asus-vivobook ~/tests $ grep -c arg f1
2
```
```
ivan@asus-vivobook ~/tests $ cat /proc/cpuinfo | grep 'model name' | uniq
model name	: AMD Ryzen 5 5600H with Radeon Graphics
```

### tail
_вывод нескольких последних строк из файла. -n - количество строк._
```
ivan@asus-vivobook ~/tests $ cat /proc/cpuinfo | tail -n 5
clflush size	: 64
cache_alignment	: 64
address sizes	: 48 bits physical, 48 bits virtual
power management: ts ttp tm hwpstate cpb eff_freq_ro [13] [14]
```
```
ivan@asus-vivobook ~/tests $ cat f1
df, fads
edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
asdf
asdg arg
ivan@asus-vivobook ~/tests $ tail -c 3 f1
rg
```

### tee
_выводит на экран, или же перенаправляет выходной поток  (stdout) команды и копирует его содержимое в файл или в переменную. -a - приписать в конец файла_
```
ivan@asus-vivobook ~/tests $ uname -r | tee kernel.txt | rev
ootneg-21.1.6
ivan@asus-vivobook ~/tests $ cat kernel.txt
6.1.12-gentoo
ivan@asus-vivobook ~/tests $ uname -a | tee -a kernel.txt
Linux asus-vivobook 6.1.12-gentoo #18 SMP PREEMPT_DYNAMIC Wed Mar  8 15:42:12 MSK 2023 x86_64 AMD Ryzen 5 5600H with Radeon Graphics AuthenticAMD GNU/Linux
ivan@asus-vivobook ~/tests $ cat kernel.txt
6.1.12-gentoo
Linux asus-vivobook 6.1.12-gentoo #18 SMP PREEMPT_DYNAMIC Wed Mar  8 15:42:12 MSK 2023 x86_64 AMD Ryzen 5 5600H with Radeon Graphics AuthenticAMD GNU/Linux
```

### head
_вывод первых n строк из файла._
```
df, fads
edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
asdf
asdg arg
ivan@asus-vivobook ~/tests $ head -n2 f1
df, fads
edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
ivan@asus-vivobook ~/tests $ head -c2 f1
df
```

### touch
_установка времени последнего изменения файла, также используется для создания пустых файлов_
```
ivan@asus-vivobook ~/tests $ ls -l
total 102408
-rw-r--r-- 1 ivan ivan        95 мар 11 00:48 f1
-rw-r--r-- 1 ivan ivan         0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan         0 мар 10 21:40 f3
-rw-r--r-- 1 ivan ivan        14 мар 11 01:11 kernel.txt
-rwxr--r-- 1 ivan ivan         0 мар 10 21:42 s.sh
-rwxr--r-- 1 ivan ivan         0 мар 10 21:42 script.py
-rw-r--r-- 1 ivan ivan 104857600 мар 10 23:38 test
ivan@asus-vivobook ~/tests $ touch -d '2007-01-31 8:46:26' f1
ivan@asus-vivobook ~/tests $ ls -l
total 102408
-rw-r--r-- 1 ivan ivan        95 янв 31  2007 f1
-rw-r--r-- 1 ivan ivan         0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan         0 мар 10 21:40 f3
-rw-r--r-- 1 ivan ivan        14 мар 11 01:11 kernel.txt
-rwxr--r-- 1 ivan ivan         0 мар 10 21:42 s.sh
-rwxr--r-- 1 ivan ivan         0 мар 10 21:42 script.py
-rw-r--r-- 1 ivan ivan 104857600 мар 10 23:38 test
```
```
ivan@asus-vivobook ~/tests $ ls
f1  f2  f3  kernel.txt  s.sh  script.py  test
ivan@asus-vivobook ~/tests $ touch f
ivan@asus-vivobook ~/tests $ file f
f: empty
```

### du
_оценка занимаемого файлового пространства. -h - человеко-читаемый вывод; -d - глубина поиска._
```
ivan@asus-vivobook ~ $ du -h Downloads/
923M	Downloads/
ivan@asus-vivobook ~ $ du -hd 1
403M	./.vscode
600M	./.config
338M	./.local
20K	./.ssh
4.0K	./empt
4.0K	./.w3m
923M	./Downloads
118M	./.mozilla
52K	./bak
8.0K	./.vim
27M	./pdfs
101M	./tests
76K	./.pki
308K	./focs
1.1G	./.cache
20K	./wallpapers
12K	./.dbus
12M	./.suckless
3.6G	.
```

### file
_определения типа файла (-i Mime тип)_
```
ivan@asus-vivobook ~/pdfs/university $ file l20-2012.djvu
l20-2012.djvu: DjVu image or single page document
ivan@asus-vivobook ~/pdfs/university $ file -i l20-2012.djvu
l20-2012.djvu: image/vnd.djvu; charset=binary
```

### gzip
_утилита сжатия и восстановления файлов, использующая алгоритм Deflate_
```
ivan@asus-vivobook ~/tests $ tar -cvf arch.tar *
f
f1
f2
f3
s.sh
script.py
test
ivan@asus-vivobook ~/tests $ du -h arch.tar
101M	arch.tar
ivan@asus-vivobook ~/tests $ gzip arch.tar
ivan@asus-vivobook ~/tests $ du -h arch.tar.gz
100K	arch.tar.gz
ivan@asus-vivobook ~/tests $ gzip -d arch.tar.gz
ivan@asus-vivobook ~/tests $ ls
arch.tar  f  f1  f2  f3  s.sh  script.py  test
```

### bzip2
_утилита сжатия и восстановления файлов, использующая алгоритм Барроуза-Уиллера_
```
ivan@asus-vivobook ~/tests $ tar -cvf arch.tar *
f
f1
f2
f3
s.sh
script.py
test
ivan@asus-vivobook ~/tests $ du -h arch.tar
101M	arch.tar
ivan@asus-vivobook ~/tests $ bzip2 arch.tar
ivan@asus-vivobook ~/tests $ du -h  arch.tar.bz2
4.0K	arch.tar.bz2
ivan@asus-vivobook ~/tests $ bzip2 -d arch.tar.bz2
ivan@asus-vivobook ~/tests $ ls
arch.tar  f  f1  f2  f3  s.sh  script.py  test
```

### tr
_копирует стандартный входной поток в стандартный выходной, подставляя или удаляя некоторые символы ([:lower:] - строка из всех строчных букв, [:upper:] - стркоа всех заглавных букв, [:digits:] - строка из всех цифр, -d  удаление символов, указанных в наборе)_
```
ivan@asus-vivobook ~/tests $ echo "feh" | tr "[:lower:]" "[:upper:]"
FEH
ivan@asus-vivobook ~/tests $ $ echo "1 please 2 remove 3 all 4 digits" | tr -d [:digit:]
please remove all digits
```

### cmp
_сравнивает два файла и, если они различаются, сообщает о первом байте и строке, где было обнаружено различие. -b - вывести различающиеся байты; -l - вывести номера различающихся байтов и их значения_
```
ivan@asus-vivobook ~/tests $ cmp f1 f2
f1 f2 differ: byte 77, line 2
ivan@asus-vivobook ~/tests $ cmp -b f1 f2
f1 f2 differ: byte 77, line 2 is 147 g 104 D
ivan@asus-vivobook ~/tests $ cmp -l f1 f2
77 147 104
78 141 147
79  40 141
80 163  40
81  12 163
82 141  12
83 163 141
84 144 163
85 146 144
86  12 146
87 141  12
88 163 141
89 144 163
90 147 144
91  40 147
92 141  40
93 162 141
94 147 162
95  12 147
cmp: EOF on f1 after byte 95
```

### comm
_читает файл1 и файл2, которые должны быть предварительно лексически отсортированы, и генерирует вывод, состоящий из трёх колонок текста: строки, найденные только в файле файл1; строки, найденные только в файле файл2; и строки, общие для обоих файлов. -n -подавить вывод n столбца (n = {1,2,3}); --check-order - проверка отсортированности файлов_
```
ivan@asus-vivobook ~/tests $ cat foo
apple
banana
cactus
ivan@asus-vivobook ~/tests $ cat bar
apple
banana
cherry
ivan@asus-vivobook ~/tests $ comm -check-order foo bar
comm: invalid option -- 'c'
Try 'comm --help' for more information.
ivan@asus-vivobook ~/tests $ comm --check-order foo bar
		apple
		banana
cactus
	cherry
ivan@asus-vivobook ~/tests $ comm --check-order -3 foo bar
cactus
	cherry
```

### xargs
_берет данные из стандартного ввода или из файла, разбивает их в соответствии с указанными параметрами, а затем передает другой программе в качестве аргумента_
```
ivan@asus-vivobook ~/tests $ ls -l
total 0
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f1
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f3
-rw-r--r-- 1 ivan ivan 0 мар 10 21:42 s.sh
-rw-r--r-- 1 ivan ivan 0 мар 10 21:42 script.py
ivan@asus-vivobook ~/tests $ find . \( -name '*.sh' -o -name '*.py' \) -type f | xargs chmod 744;
ivan@asus-vivobook ~/tests $ ls -l
total 0
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f1
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f2
-rw-r--r-- 1 ivan ivan 0 мар 10 21:40 f3
-rwxr--r-- 1 ivan ivan 0 мар 10 21:42 s.sh
-rwxr--r-- 1 ivan ivan 0 мар 10 21:42 script.py
```
```
ivan@asus-vivobook ~/tests $ ls | xargs wc
        4        30 104867840 arch.tar
        3         3        20 bar
        0         0         0 f
        4        15        95 f1
        4        15        96 f2
        0         0         0 f3
        3         3        20 foo
        0         0         0 s.sh
        0         0         0 script.py
        0         0 104857600 test
       18        66 209725671 total
```
### diff
_сравнение файлов, выводящая разницу между двумя файлами (т.н. patch-файл) -u - универасльный формат патча._
```
ivan@asus-vivobook ~/tests $ diff f1 f2
2c2
< edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
---
> edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga Dga s
ivan@asus-vivobook ~/tests $ diff -u f1 f2
--- f1	2007-01-31 08:46:26.000000000 +0300
+++ f2	2023-03-11 02:02:59.223225768 +0300
@@ -1,4 +1,4 @@
 df, fads
-edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
+edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga Dga s
 asdf
 asdg arg
```

### patch
_перенос правок (изменений) между разными версиями текстовых файлов, информация о правке обычно содержится в отдельном patch-файле. -R - отменить патч._
```
ivan@asus-vivobook ~/tests $ diff -u f1 f2 > patch.diff
ivan@asus-vivobook ~/tests $ cat patch.diff
--- f1	2007-01-31 08:46:26.000000000 +0300
+++ f2	2023-03-11 02:02:59.223225768 +0300
@@ -1,4 +1,4 @@
 df, fads
-edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga ga s
+edhrsheatrjyjktykt arg  kty kteyk tydjdtr jsrtjwrsthaer e  eraerga Dga s
 asdf
 asdg arg
ivan@asus-vivobook ~/tests $ patch < patch.diff
patching file f1
ivan@asus-vivobook ~/tests $ cmp f1 f2
ivan@asus-vivobook ~/tests $ patch -R < patch.diff
patching file f1
ivan@asus-vivobook ~/tests $ cmp f1 f2
f1 f2 differ: byte 77, line 2
```

### uniq
_вывести или отфильтровать повторяющиеся строки в отсортированном файле. -d - выввести только повторяющиеся строки_
```
ivan@asus-vivobook ~/tests $ cat notuniqfile
apple
apple
apple
apple
apple
banana
banana
cherry
apple
ivan@asus-vivobook ~/tests $ uniq notuniqfile
apple
banana
cherry
apple
ivan@asus-vivobook ~/tests $ sort notuniqfile | uniq
apple
banana
cherry
ivan@asus-vivobook ~/tests $ sort notuniqfile | uniq -d
apple
banana
```

### sort
_вывод сортированного слияния указанных файлов на стандартный вывод. -r - сортировка по убыванию._
```
ivan@asus-vivobook ~/tests $ cat notuniqfile
apple
apple
apple
apple
apple
banana
banana
cherry
apple
ivan@asus-vivobook ~/tests $ sort notuniqfile
apple
apple
apple
apple
apple
apple
banana
banana
cherry
ivan@asus-vivobook ~/tests $ sort -r notuniqfile
cherry
banana
banana
apple
apple
apple
apple
apple
apple
```

### cut
_выборка отдельных полей из строк файла (табуляция - разделитель по умолчанию). -d - указать разделитель полей, -fn - номер выводимого поля, -cn - номер выводимого символа (вместо поля)_
```
ivan@asus-vivobook ~/tests $ df
Filesystem     1K-blocks     Used Available Use% Mounted on
none             7887628     1380   7886248   1% /run
udev               10240        0     10240   0% /dev
tmpfs            7887628    13116   7874512   1% /dev/shm
/dev/dm-1      263096388 25857556 223801496  11% /
tmpfs            7887632     3244   7884388   1% /tmp
/dev/nvme0n1p1   1044480   135040    909440  13% /boot
tmpfs            1577524       12   1577512   1% /run/user/1000
ivan@asus-vivobook ~/tests $ df | tail -n2 | head -n1 | cut -d" " -f1
/dev/nvme0n1p1
```
```
ivan@asus-vivobook ~/tests $ cat notuniqfile
apple
apple
apple
apple
apple
banana
banana
cherry
apple
ivan@asus-vivobook ~/tests $ cut -c1 notuniqfile
a
a
a
a
a
b
b
c
a
```

## 9. Дневник отладки 

| №      |  Лаб. или дом. | Дата     | Время   | Событие                        | Действие по исправлению | Примечание |
| ------ | ------         | ------   | ------  | ------                         | ------                  | ------     |
| 1      |  дом.          | 9.03.23-10.03.23 | 21:00-2:00    | Выполнение лабораторной работы | Создана структура и запротоколирован tar     | -          |
| 2      |  дом.          | 10.03.23-11.03.23 | 20:00-3:00  | Выполнение лабораторной работы | Лабораторная работа выполнена                       | -          |
## 10.Вывод работы:

Изучив основные команды, я научился более эффективно и уверенно пользоваться UNIX-подобной операционной системой.