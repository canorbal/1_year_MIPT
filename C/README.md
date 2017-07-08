# usage
****
###  Компиляция

    user@ubuntu:~$ gcc file_name.c -o file_name.out
****

* [односвязный список](https://github.com/canorbal/1_year_MIPT/blob/master/C/singly_linked_list.c)

      реализованы базовые функции:
      insert, pop, remove

      пример использования в функции main

* [двусвязный список](https://github.com/canorbal/1_year_MIPT/blob/master/C/doubly_linked_list.c)

      реализованы базовые функции:
      1. проверка на пустоту
      2. push, pop
      3. unshift, shift
      4. инверсия

      пример использования в функции main

* [проверка скобочной последовательности](https://github.com/canorbal/1_year_MIPT/blob/master/C/brackets_on_stack.c)

      используется реализация двусвязного списка из предыдущего примера;

      работает только с [, {, <, (, ), >, }, ]

      user@ubuntu:~$ gcc brackets_on_stack.c -o brackets_on_stack.out
      user@ubuntu:~$ ./brackets_on_stack.out
      <{}>
      YES
      user@ubuntu:~$ ./brackets_on_stack.out
      <{>}
      NO
      user@ubuntu:~$

* [перевод арифметического выражения в обратную польскую запись](https://github.com/canorbal/1_year_MIPT/blob/master/C/to_RPN.c)

      используется реализация двусвязного списка;

      работает только с цифрами и + - * / ^;

      user@ubuntu:~$ gcc to_RPN.c -o to_RPN.out
      user@ubuntu:~$ ./to_RPN.out
      (1+2/3-4*5^6*(7-4/3))
      1 2 3 / + 4 5 6 ^ * 7 4 3 / - * -
      user@ubuntu:~$ ./to_RPN.out
      (((1+2)/4)*5)+(8*(7-6))
      1 2 + 4 / 5 * 8 7 6 - * +
      user@ubuntu:~$

* [вычисление арифметического выражения, записанного в обратной польской записи](https://github.com/canorbal/1_year_MIPT/blob/master/C/RPN_calculate.c)

      используется реализация двусвязного списка;

      работает только с цифрами и + - * /;

      user@ubuntu:~$ gcc RPN_calculate.c -o RPN_calculate.out
      user@ubuntu:~$ ./RPN_calculate.out
      1 2 + 4 / 5 * 8 7 6 - * +
      11.75
      user@ubuntu:~$

* [бинарное дерево поиска](https://github.com/canorbal/1_year_MIPT/blob/master/C/binary_search_tree.c)

      реализация бинарного дерева поиска

      пример из функции main:

 ![alt](https://github.com/canorbal/1_year_MIPT/blob/master/figures/binary_search_tree.png)

      реализованы:
      1. добавление/удаление узлов (push, delete)
      2. обход в глубину, ширину (dfs, bfs)
      3. поиск минимального элемента
      4. очередь для узлов дерева (используется в bfs)

      примеры использования в функции main
