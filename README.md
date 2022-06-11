# Marusia Game Challenge

> About [Challenge](https://uptu.work/job/mail-ru-group-marusia-game-challenge/)

Solutions to all problems are implemented in C++.

Disclaimer:
* In task2 and task3 tasks, in addition to outputting commands to a file, they are also output to the console. When output to the console, there may be problems with the output of Russian words.

## English

#### Task 1
When we were kids, we often played Tic-Tac-Toe. Voice assistants also want to learn this fun. Help Marusa, who has never played Tic-Tac-Toe before, to identify the winner. In the field for the game [N x N] to determine the winner or draw.
Input data: the first line specifies the size of the playing field N. On the next N lines, rows are specified, each of which contains N values separated by a space.
Multiple values:
- x — cell is occupied by a cross
- 0 — the cell is occupied by a zero
- . — the cage is not occupied
Output data:
- x — won crosses (x)
- 0 — zeros won (zero)
- x0 is a draw or the result cannot be determined yet (x is zero).
Constraints: N is an integer on the segment [0; 30]

* The small case of the English letter x - 'x' was used as a cross, and the large case of the English letter 'O' was used as a zero.
* Since the problem condition does not give a tic-tac-toe winning condition for N > 3, so I searched for these conditions on the Internet and took the following as a basis from the Wikipedia article: when placing n >= 3 identical signs in a row (tic-tac-toe), then this is considered a victory on a large field (>= 3 on 3).
I am attaching the [article](https://ru.wikipedia.org/wiki/Крестики-нолики#Более_длинные_линии).
* But also, in order to avoid misunderstandings in the future and to make my program more versatile, I wrote code in the program that determines the winner from the condition that ONE of the diagonals (or verticals, or horizontals) It is completely filled with identical symbols (i.e. crosses or zeros). Example: if a field is given 6 by 6, then the winner will be the one whose symbols occupy either all 6 cells horizontally, or all 6 cells vertically, or all 6 cells along one of the diagonals. It is impossible to completely fill 2 verticals/horizontals/diagonals at the same time (although diagonals are clearly superfluous here). In order to use this condition as a winning one, it is necessary to comment out the 374 line "string s = Board.check_func();" in the main() function and uncomment the 382 line "string s = Board.check_func_n();" also in the main() function.

#### Task 2
Marusya wants to learn how to play naval combat. Help her figure out the mechanics of the game and react correctly to the opponent's moves. A field for playing naval combat is given [9×9]. The very first row is the numeric designation of the columns. The first character on each line is its letter designation [A—I], and then its contents are separated by a space:
- _ - empty cell.
- x - the deck of the ship.
After that, 10 cell designations are submitted to the input, each on a separate line. In response, the result is expected in the form: "Hit!" or "Miss!".

* The condition does not say which input stream the field and commands are fed into, so I made the input of a field of size 9 by 9 from a file (10 commands are also read from the file, which come immediately after the field from a new line), and the output to cin and each time to a separate file, as requested at the end of the tasks. The case of the symbol (English letter x) denoting the deck of the ship, 'x' can be any. I did in the conditional statement for both the small 'x' and the large 'X'.
* To output Russian text to the console, the setlocale(LC_ALL, "Russian") function was used;

#### Task 3
Help Marusa to get Dasha the Traveler out of the dungeon. A square field [N x N] of a given value is given (N is in the range [10; 100]). The field is a dungeon with a corridor that leads to the exit. Dasha is at the beginning of the corridor, and the voice assistant helps her get out of the dungeon. The exit is at the end of the corridor on the border of the map.
On the first line, the program accepts the size of the dungeon as input — N, then the representation of the dungeon itself separated by a space:
- _ — dungeon walls.
- x is Dasha's location.
- . — continuation of the corridor.
Instructions — the following words:
- Upstairs!
- To the right!
- Down!
- To the left!

* To complete a maze (any maze with a given finish on the edge of the map, as in the condition) I have implemented the [wave algorithm](https://ru.wikipedia.org/wiki/Алгоритм_Ли ) (Lee's algorithm, as it is also sometimes called). Neighboring cells were classified by [von Neumann neighborhood](https://ru.wikipedia.org/wiki/Neighborhood of Phone_neiman).
* The solution assumes that there is definitely a way out of the maze. The program is able to bypass loops in the maze, dead ends, and intersections. It finds the shortest path from start to finish and outputs a set of commands to the cout stream, and also writes them to a file. I made the maze input from a file (it's much more convenient with this task). On the first line there should be an N - number indicating the size of the maze. The maze map should start from the next line.

## Russian

#### Task 1
Условие:
Когда мы были детьми, то часто играли в «Крестики-нолики». Голосовые помощники тоже хотят научиться этой забаве. Помоги Марусе, которая никогда раньше не играла в «Крестики-нолики», выявить победителя. В поле для игры [N x N] определи победителя или ничью.
Входные данные: на первой строке задается размер игрового поля N. На последующих N строках задаются строки, каждая из которых содержит N значений, разделенных пробелом.
Множество значений:
- x — клетка занята крестиком
- 0 — клетка занята ноликом
- . — клетка не занята
Выходные данные:
- x — победили крестики (икс)
- 0 — победили нолики (ноль)
- x0 — ничья или результат ещё нельзя определить (икс ноль).
Ограничения: N — целое число на отрезке [0; 30]

* В качестве крестика использовался маленький регистр английской буквы икс - 'x', а в качество нолика использовался большой регистр английской буквы 'O'.
* Поскольку условие задачи не дает условия выигрыша в крестики-нолики для N > 3, поэтому я искал эти условия в Интернете и взял за основу из статьи в Википедии следующее: при размещении n >= 3 идентичных знаков подряд (крестики или нолики), тогда это считается победой на большом поле (>= 3 на 3).
Я прилагаю [статью](https://ru.wikipedia.org/wiki/Крестики-нолики#Более_длинные_линии).
* Но также, чтобы не было недоразумений в будущем и чтобы моя программа была более универсальной, я написал код в программе, который определяет победителя из условия, что ОДНА из диагоналей (или вертикалей, или горизонталей) ПОЛНОСТЬЮ заполнена одинаковыми символами (то есть крестиками или ноликами). Пример: если дано поле 6 на 6, то победитель будет тот, чьи символы занимают либо все 6 ячеек по горизонтале, либо все 6 ячеек по вертикале, либо все 6 ячеек по одной из диагоналей. Одновременно полностью заполнить 2 вертикали/горизонтали/диагонали (хотя диагонали тут явно лишние) нельзя. Для того, чтобы использовать данное условие, как выигрышное, необходимо закомментить 374 строку "string s = Board.check_func();" в функции main() и раскомментить 382 строку "string s = Board.check_func_n();" тоже в функции main().

#### Task 2:
Условие:
Маруся хочет научиться играть в морской бой. Помоги ей разобраться с механикой игры и верно реагировать на ходы противника. Дано поле для игры в морской бой [9×9]. Самая первая строка — числовое обозначение столбцов. Первый символ на каждой строке — её буквенное обозначение [A-I], а дальше через пробел идет её содержимое:
- _ — пустая клетка.
- x — палуба корабля.
После этого на вход подается 10 обозначений клеток, каждое на отдельной строке. В ответ ожидается результат в виде: «Попал!» или «Промах!».

* В условии не сказано в какой поток ввода подается поле и команды, поэтому я сделал ввод поля размера 9 на 9 из файла (также из файла считываются 10 команд, которые идут сразу после поля с новой строки), а вывод в cin и каждый раз в отдельный файл, как просят в конце задач. Регистр символа (английская буква икс), обозначающего палубу корабля, 'x' может быть любой. Я сделал в условном операторе как для маленького 'x', так и для большого 'X'.
* Для вывода русского текста в консоль использовалась функция setlocale(LC_ALL, "Russian");

#### Task 3:
Условие:
Помоги Марусе вывести Дашу Путешественницу из подземелья. Дано квадратное поле [N x N] заданной величины (N находится в диапазоне [10; 100]). Поле — подземелье с коридором, который ведет к выходу. Даша находится в начале коридора, а голосовой помощник помогает ей выбраться из подземелья. Выход находится в конце коридора на границе карты.
На первой строке программа принимает на вход размер подземелья — N, затем представление самого подземелья через пробел:
- _ — стены подземелья.
- х — местонахождение Даши.
- . — продолжение коридора.
Указания — следующие слова:
- Наверх!
- Направо!
- Вниз!
- Налево!

* Для прохождения лабиринта (любого лабиринта с заданным финишем на краю карты, как в условии) я реализовал [волновой алгоритм](https://ru.wikipedia.org/wiki/Алгоритм_Ли) (алгоритм Ли, как его еще иногда называют). Соседние ячейки классифицировал по [окрестности фон Неймана](https://ru.wikipedia.org/wiki/Окрестность_фон_Неймана).
* В решении предполагается, что выход из лабиринта точно есть. Программа способна обходить петли в лабиринте, тупики, перекестки. Она находит кратчайший путь от старта до финиша и выводит в поток cout набор команд, а также записывает их в файл. Ввод лабиринта я сделал из файла (так гораздо удобнее с этим заданием). На первой строчке должно быть N - число, обозначающее размеры лабиринта. Со следующей строчки должна начинаться карта лабиринта.
