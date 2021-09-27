# Описание
Программа cub3d реализует алгоритм рейкастинга, который использовался в такой игре, как Wolfenstein 3D.
# Как установить cub3d
**Требуемые библиотеки для компиляции**
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev
sudo apt-get install libbsd-dev
```
**В корне репозитория ввести**
```
//Для MacOS (требуется OpenGL):
cd mlx_mac; make
make -f Makefile_mac


//Для Linux:
cd mlx_linux; make
make -f Makefile_linux
```
# Управление
W - вперёд
S - назад
A - влево
D - впарво
← - повернуть камеру влево
→ - повернуть камеру вправо
M - карта
# Пример работы
![](https://github.com/dwanett/cub3d/blob/master/gif/1.gif)
![](https://github.com/dwanett/cub3d/blob/master/gif/2.gif)
