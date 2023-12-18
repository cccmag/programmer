# factorial

## fact.c

```
$ gcc -g fact.c -o fact.o
$ gdb fact.o
GNU gdb (GDB) 8.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".    
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
---Type <return> to continue, or q <return> to quit---
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from fact.o...done.
(gdb) r
Starting program: C:\ccc\course\sp\01-gcc\06-gdb\fact\fact.o 
[New Thread 4100.0x2210]
[New Thread 4100.0x3704]
factorial(5)=120
[Thread 4100.0x3704 exited with code 0]
[Inferior 1 (process 4100) exited normally]
(gdb) gcc -g fact.c -o fact.o
Undefined command: "gcc".  Try "help".
(gdb) make 
make: *** No targets specified and no makefile found.  Stop.
make exited with status 2
(gdb) quit
$ gcc -g fact.c -o fact.o
$ gdb fact.o
GNU gdb (GDB) 8.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"     
and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
---Type <return> to continue, or q <return> to quit---
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from fact.o...done.
(gdb) break fact.c:5
Breakpoint 1 at 0x401562: file fact.c, line 5.
(gdb) r
Starting program: C:\ccc\course\sp\01-gcc\06-gdb\fact\fact.o 
[New Thread 9620.0x2aa0]
[New Thread 9620.0x3330]

Thread 1 hit Breakpoint 1, factorial (n=5) at fact.c:5
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) p i
$1 = 5
(gdb) p r
$2 = 120
(gdb) n
8           return r;
(gdb) n
9       }
(gdb) n
factorial(5)=120
main () at fact.c:13
13      }
(gdb) n
0x00000000004013c7 in __tmainCRTStartup ()
```

## fact_bug.c

```
$ gcc -g fact.c -o fact.o
$ gdb fact.o
GNU gdb (GDB) 8.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".    
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
---Type <return> to continue, or q <return> to quit---
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from fact.o...done.
(gdb) r
Starting program: C:\ccc\course\sp\01-gcc\06-gdb\fact\fact.o 
[New Thread 4100.0x2210]
[New Thread 4100.0x3704]
factorial(5)=120
[Thread 4100.0x3704 exited with code 0]
[Inferior 1 (process 4100) exited normally]
(gdb) gcc -g fact.c -o fact.o
Undefined command: "gcc".  Try "help".
(gdb) make 
make: *** No targets specified and no makefile found.  Stop.
make exited with status 2
(gdb) quit
$ gcc -g fact.c -o fact.o
$ gdb fact.o
GNU gdb (GDB) 8.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"     
and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
---Type <return> to continue, or q <return> to quit---
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from fact.o...done.
(gdb) break fact.c:5
Breakpoint 1 at 0x401562: file fact.c, line 5.
(gdb) r
Starting program: C:\ccc\course\sp\01-gcc\06-gdb\fact\fact.o 
[New Thread 9620.0x2aa0]
[New Thread 9620.0x3330]

Thread 1 hit Breakpoint 1, factorial (n=5) at fact.c:5
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) p i
$1 = 5
(gdb) p r
$2 = 120
(gdb) n
8           return r;
(gdb) n
9       }
(gdb) n
factorial(5)=120
main () at fact.c:13
13      }
(gdb) n
0x00000000004013c7 in __tmainCRTStartup ()
(gdb) quit
A debugging session is active.

        Inferior 1 [process 9620] will be killed.

Quit anyway? (y or n) y
$ gcc -g fact_bug.c -o fact_bug.o
$ gdb fact_bug.o
GNU gdb (GDB) 8.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
---Type <return> to continue, or q <return> to quit---
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from fact_bug.o...done.
(gdb) break fact_bug.c:5
Breakpoint 1 at 0x40155b: file fact_bug.c, line 5.
(gdb) r
Starting program: C:\ccc\course\sp\01-gcc\06-gdb\fact\fact_bug.o 
[New Thread 11680.0x30e4]
[New Thread 11680.0x16b0]

Thread 1 hit Breakpoint 1, factorial (n=5) at fact_bug.c:5
5           for (int i=2; i<=n; i++) {
(gdb) p r
$1 = 0
(gdb) p r=1
$2 = 1
(gdb) p r
$3 = 1
(gdb) n
6               r = r*i;
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) n
Program not restarted.
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
6               r = r*i;
(gdb) n
5           for (int i=2; i<=n; i++) {
(gdb) n
8           return r;
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) n
Program not restarted.
(gdb) p r
$4 = 120
(gdb) n
9       }
(gdb) n
factorial(5)=120
main () at fact_bug.c:13
13      }
(gdb) n
0x00000000004013c7 in __tmainCRTStartup ()
(gdb) n
Single stepping until exit from function __tmainCRTStartup,
which has no line number information.
[Thread 11680.0x16b0 exited with code 0]
[Inferior 1 (process 11680) exited normally]
(gdb) n
The program is not being run.
(gdb) quit
```