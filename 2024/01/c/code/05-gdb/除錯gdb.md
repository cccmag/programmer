# gdb 除錯


參考 : https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html

在 MSYS2 中 (或 linux 中) ...

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/01-add
$ gcc main.c add.c -o add -g

user@DESKTOP-96FRN6B MSYS /d/ccc/book/sp/code/c/03-asm/01-add
$ gdb -q add
Traceback (most recent call last):
  File "<string>", line 3, in <module>
ImportError: No module named libstdcxx.v6.printers
/etc/gdbinit:6: Error in sourced command file:
Error while executing Python code.
Reading symbols from add...done.
(gdb) break 6
Breakpoint 1 at 0x10040108d: file main.c, line 6.
(gdb) r
Starting program: /d/ccc/book/sp/code/c/03-asm/01-add/add
[New Thread 1896.0x26cc]
[New Thread 1896.0x13b8]
[New Thread 1896.0xb84]
[New Thread 1896.0x22ec]

Thread 1 "add" hit Breakpoint 1, main () at main.c:6
6         int t = add(5, 8);
(gdb) n
7         printf("add(5, 8)=%d\n", t);
(gdb) n
add(5, 8)=13
8       }(gdb) n
[Thread 1896.0x22ec exited with code 0]
[Thread 1896.0x13b8 exited with code 0]
[Inferior 1 (process 1896) exited normally]
(gdb)

```

