## 使用 gdb


參考 : https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html



## windows

```
PS D:\ccc\sp\code\c\04-toolchain\gcc\07-gdb> gcc main.c add.c 
-o add -g
PS D:\ccc\sp\code\c\04-toolchain\gcc\07-gdb> gdb32 -q add     
Reading symbols from add...done.
(gdb) break 6
Breakpoint 1 at 0x40135e: file main.c, line 6.
(gdb) r
Starting program: D:\ccc\sp\code\c\04-toolchain\gcc\07-gdb\add.exe 
[New Thread 5800.0x21e8]

Breakpoint 1, main () at main.c:6
6         int t = add(5, 8);
(gdb) n
7         printf("add(5, 8)=%d\n", t);
(gdb) n
[New Thread 5800.0x3fc]
add(5, 8)=13
8         return 0;
(gdb) n
9       }(gdb) n
0x004010fd in __mingw_CRTStartup ()
(gdb) n
Single stepping until exit from function __mingw_CRTStartup,  
which has no line number information.
[Inferior 1 (process 5800) exited normally]
(gdb) quit
```

## Linux

圖形版: DDD -- https://www.gnu.org/software/ddd/

```
root@localhost:/home/guest/sp/code/c/07-linux/gdb# gcc main.c add.c -o add -g
root@localhost:/home/guest/sp/code/c/07-linux/gdb# gdb -q add
Reading symbols from add...done.
(gdb) break 6
Breakpoint 1 at 0x652: file main.c, line 6.
(gdb) r
Starting program: /home/guest/sp/code/c/07-linux/gdb/add

Breakpoint 1, main () at main.c:6
6         int t = add(5, 8);
(gdb) n
7         printf("add(5, 8)=%d\n", t);
(gdb) n
add(5, 8)=13
8         return 0;
(gdb) n
9       }(gdb) n
__libc_start_main (main=0x55555555464a <main>, argc=1, argv=0x7fffffffe4f8,
    init=<optimized out>, fini=<optimized out>, rtld_fini=<optimized out>,
    stack_end=0x7fffffffe4e8) at ../csu/libc-start.c:344
344     ../csu/libc-start.c: No such file or directory.
(gdb) n
[Inferior 1 (process 23922) exited normally]
(gdb) n
The program is not being run.

```

最後按 Ctrl-d 可以離開 (Ctrl-C 無法離開)

## MSYS2

在 MSYS2 中 ...

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
