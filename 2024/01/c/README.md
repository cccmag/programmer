# GCC 工具鏈用法

GCC（GNU Compiler Collection）是一個開源的編程語言編譯器套件，被廣泛用於開發各種不同類型的軟體。它支援多種語言，包括C、C++、Fortran、Objective-C、Ada等。GCC工具鏈由多個工具組成，可以執行編譯、連接和除錯等操作。在這篇文章中，我們將著重介紹GCC工具鏈的常用用法。

## 安裝

如果您在 windows 的環境中，還沒安裝 gcc，可以先安裝 《choco 套件安裝程式》，安裝方法請參考下文

* [套件安裝器](./skill/README.md)

先用系統管理員身分打開 Powershell (或其他終端機，例如 VsCode 中的終端機) ，記得按滑鼠右鍵 選《以系統管理員身分執行》

要用 choco 安裝 gcc ，可以用 `choco install mingw` 指令安裝 MinGW 套件，MinGW（Minimalist GNU for Windows）是將 GCC 編譯器和 GNU Binutils 移植到 Windows 平台下的產物。安裝過程如下：

```bash
$ choco install mingw
Chocolatey v0.10.15
Installing the following packages:
mingw

...
Do you want to run the script?([Y]es/[A]ll - yes to all/[N]o/[P]rint): y
...

Environment Vars (like PATH) have changed. Close/reopen your shell to
 see the changes (or in powershell/cmd.exe just type `refreshenv`).
 The install of mingw was successful.
  Software installed to 'C:\ProgramData\chocolatey\lib\mingw\tools\install'

Chocolatey installed 1/1 packages. 
 See the log for details (C:\ProgramData\chocolatey\logs\chocolatey.log).
```

記得在 choco 問你時選擇 y，這樣就會在你電腦裡安裝一個 mingw 套件

安裝好之後記得關閉你的《終端機》，然後重新開啟，這樣才能重新抓取系統路徑 PATH 。

然後你就可以開始使用 gcc 編譯器了。

## 編譯程式碼

GCC的最基本用法是用於編譯程式碼。可以使用`gcc`命令來將 C 程式碼編譯成可執行檔。例如，我們可以寫一個 `hello.c` 程式碼如下：

```c
#include <stdio.h>

int main(void) {
  printf("Hello!\n");
}
```

然後執行以下命令：

```
$ gcc hello.c -o hello

$ ./hello
Hello!
```

這將會將`hello.c`編譯成可執行檔`hello`。`-o`選項用於指定輸出檔名。

但是由於 C 語言的中文可移植行並不高，所以若輸出文字有中文，是有可能會輸出亂碼的 (我的經驗是在 windows 中會輸出亂碼，但在 Linux / iMac 中不會有亂碼)

檔案： hello2.c

```c
#include <stdio.h>

int main(void) {
  printf("Hello 你好!\n");
}
```

執行結果

```
$ gcc hello2.c -o hello2

$ ./hello2
Hello 雿末!
```

這是因為繁體中文 windows 預設的 code page 是 big5，而不是 unicode 的 UTF8，如果你是在 Powershell 的終端機當中，那麼可以試著用 `chcp 65001` 指令切換為 UTF8， 這樣或許就不會有亂碼了 (但不一定，我還是有遇過某些 windows 平台照樣還是亂碼 ....) ，以下是我們用了 `chcp 65001` 之後的結果。

```
$ chcp 65001

Active code page: 65001

$ ./hello2
Hello 你好!
```

## 編譯為組合語言

如果加上 -S 參數，您可以將 C 語言編譯為組合語言輸出，這是學習組合語言的一個好用方法。

```s
$ gcc -S hello.c -o hello.s

$ cat hello.s
        .file   "hello.c"
        .text
        .def    __main; .scl    2;      .type   32;     .endef
        .section .rdata,"dr"
.LC0:
        .ascii "Hello!\0"
        .text
        .globl  main
        .def    main;   .scl    2;      .type   32;     .endef
        .seh_proc       main
main:
        pushq   %rbp
        .seh_pushreg    %rbp
        movq    %rsp, %rbp
        .seh_setframe   %rbp, 0
        subq    $32, %rsp
        .seh_stackalloc 32
        .seh_endprologue
        call    __main
        leaq    .LC0(%rip), %rcx
        call    puts
        movl    $0, %eax
        addq    $32, %rsp
        popq    %rbp
        ret
        .seh_endproc
        .ident  "GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
        .def    puts;   .scl    2;      .type   32;     .endef
```

## 編譯 c++ 程式

檔案： hello.cpp

```cpp
#include <iostream>
using namespace std;
int main() {
    cout << "hello!" << endl;
}
```

編譯執行

```
$ g++ hello.cpp -o hello
$ ./hello
hello!
```

上述行結果我是在 Powershell 中得到的，但若在 git bash 的 MINGW64 環境中，會得到 Segmentation fault 的結果如下：

```
$ g++ hello.cpp -o hello

$ ./hello
Segmentation fault
```

這再次驗證了 windows 平台中的 gcc 環境，和 Linux 當中還是有些差異的。(在 Linux 當中 C 語言通常穩定得多，即使從 Ubuntu 換到 CentOS 等不同平台也是 OK 的)

## 其他用法

```bash
$ gcc -c hello.c -o hello.o # 只編譯不連結

$ ./hello.o # hello.o 是未連結完成的目的檔，所以不能執行
bash: ./hello.o: cannot execute binary file: Exec format error

$ gcc hello.o -o hello # 將 hello.o 連結後變成 hello

$ ls hello.*
hello.c  hello.exe  hello.o hello.s # windows 中執行檔的附檔名會自動加上 .exe (但在 Linux/iMac 中不會)

$ ./hello # 連結完之後，可以執行
Hello!
```

GNU/MinGW 工具除了 gcc 之外，也附上了被稱為 binutil 的一系列工具，像是 objdump (目的檔傾印) / strings (列印字串表) / objcopy (目的檔處理拷貝) / ld (連結器) / as (組譯器) / make (專案建置器) .... 等等。

以下我們先示範 objdump 的一個用法，用來將剛剛的未連結目的檔 hello.o 進行反組譯列印。

```
$ objdump -d hello.o

hello.o:     file format pe-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp

   4:   48 83 ec 20             sub    $0x20,%rsp
   8:   e8 00 00 00 00          call   d <main+0xd>
   d:   48 8d 05 00 00 00 00    lea    0x0(%rip),%rax        # 14 <main+0x14>
  14:   48 89 c1                mov    %rax,%rcx

  17:   e8 00 00 00 00          call   1c <main+0x1c>
  1c:   b8 00 00 00 00          mov    $0x0,%eax

  21:   48 83 c4 20             add    $0x20,%rsp
  25:   5d                      pop    %rbp
  26:   c3                      ret
  27:   90                      nop
  28:   90                      nop
  29:   90                      nop
  2a:   90                      nop
  2b:   90                      nop
  2c:   90                      nop
  2d:   90                      nop
  2e:   90                      nop
  2f:   90                      nop
```

## gcc 的參數

除了基本的編譯外，GCC還支援許多其他選項和參數，可以用來控制編譯行為。例如，可以使用`-Wall`選項來開啟所有警告信息，或使用`-O2`選項來優化程式碼。可以通過查閱GCC的官方文件來了解詳細的選項和參數。

如果需要連結非預設的函式庫，可以使用 `-l` 選項指定。例如，要連接 `libm` 函式庫，可以使用以下命令：

```
gcc -o hello hello.o -lm
```

注意，gcc 體系中，函式庫檔案名稱前面的 lib 是固定的，所以不需要寫，所以 libxxx 只要寫 `-lxxx` 就可以了。

## 動態連接

除了靜態連接，GCC還支援動態連接。動態連接意味著執行檔不包含完整的庫代碼，而是在運行時從指定的庫文件中加載代碼。動態連接可以減少可執行檔的大小，並允許不同的程式共享相同的庫。

要執行動態連接，需要使用`-shared`選項來生成共享庫文件。例如，假設我們有一個名為`libhello.c`的C程式碼，可以使用以下命令將它編譯成共享庫：

```
gcc -shared -o libhello.so libhello.c
```

這將會生成名為`libhello.so`的共享庫文件。`-shared`選項用於指定生成共享庫。

在連接時，需要使用`-l`選項指定共享庫文件的名稱。例如，要連接名為`libhello.so`的共享庫，可以使用以下命令：

```
gcc -o hello hello.o -L. -lhello
```

其中，`-L`選項用於指定庫文件搜索路徑。在這個例子中，使用`.`表示當前目錄。`-l`選項後面跟著的是共享庫文件的名稱，不需要指定文件後綴。

## 用 gdb 除錯

GCC還提供了用於除錯程式的工具。其中最常用的是GDB（GNU Debugger），它是一個功能強大的除錯器，可以用於追蹤程式的執行和檢查變數的值。

要使用GDB除錯程式，需要將`-g`選項添加到編譯命令中。例如，要除錯名為`hello.c`的程式碼，可以使用以下命令：

```bash
$ gcc -g hello.c -o hello # 加上 -g 參數才能產生可除錯的執行檔

$ gdb hello # 用 gdb 除錯 hello

...
This GDB was configured as "x86_64-w64-mingw32".
...

(gdb) r # r (run) -- 開始執行程式
Starting program: D:\ccc\{Hx\programmer\2024\01\c\code\00-hello\hello.exe
Hello! # 印出 Hello 
[Inferior 1 (process 7724) exited normally]

# 由於我們沒有設中斷點，所以會直接執行完

(gdb) b hello.c:4 # b (break) -- 設定 hello.c 的第 4 行中斷
Breakpoint 1 at 0x7ff6ae50145d: file hello.c, line 4.
(gdb) r # r (run) -- 開始執行
Starting program: D:\ccc\{Hx\programmer\2024\01\c\code\00-hello\hello.exe

Breakpoint 1, main () at hello.c:4 # 果然在第 4 行中斷了
Python Exception <class 'UnicodeDecodeError'>:
'utf-8' codec can't decode byte 0xb5 in position 7: invalid start byte
4         printf("Hello!\n");
(gdb) n # n (next) 執行下一行
Hello!
5       }
(gdb) p main # p (print) 印出 main 符號的值
$1 = {int (void)} 0x7ff6ae501450 <main>
(gdb) n
0x00007ff6ae5012ef in __tmainCRTStartup ()
(gdb) n
Single stepping until exit from function __tmainCRTStartup,
which has no line number information.
[Inferior 1 (process 9668) exited normally]
(gdb) quit # 離開
```

## 結語

在GDB中，可以使用各種命令來控制程式的執行，例如`run` (r) 命令用於啟動程式，`break` (b) 命令用於設置斷點，`print`命令用於顯示變數的值，等等。可以通過查閱GDB的官方文件來了解更多的命令和用法。

綜上所述，我們介紹了GCC工具鏈的一些常用用法，包括編譯程式碼、靜態連接、動態連接和除錯程式。這只是GCC的一部分功能，它還有更多強大的特性可以用於不同的開發需求。如有需要，建議查閱GCC的官方文件以獲取更詳細的信息和指導。