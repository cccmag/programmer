# C4 編譯器 (1) -- 500 行的編譯器

c4 編譯器專案是一個極簡主義的 C 語言編譯器，由 Robert Swierczek 開發。該專案旨在實現一個極簡的 C 語言編譯器，總共只有五百多行，包含四個主要功能函數。這個編譯器提供了最基本的 C 語言特性，包括 char、int 和指標類型，以及if、while、return 和表達式語句等功能。它具有足夠的功能來實現自我編譯，同時保持極小的代碼量。

該編譯器的主要特點包括：

1. 支援 char、int 和指標類型
2. 支援 if、while、return 和表達式語句
3. 只包含四個主要功能函數，實現了極簡主義的編譯器
4. 具有足夠的功能來實現自我編譯和更多

## 使用方法：

```
gcc -o c4 c4.c
./c4 hello.c
./c4 -s hello.c

./c4 c4.c hello.c
./c4 c4.c c4.c hello.c
```

c4.c 文件包含了編譯器的主要邏輯，並且實現了 char、int 和指標類型，以及 if、while、return 等語句。這個編譯器的設計目的是讓代碼保持極小，同時能實現基本的 C 語言編譯功能。

c4 編譯器可以自我編譯，所以你可以看到 `./c4 c4.c hello.c` 這樣的指令，可以將 c4.c 編譯出來的那個編譯器，再拿來編譯 hello.c

c4 編譯器內含一個《堆疊機架構的虛擬機》，該虛擬機的指令集非常簡單，而且包含了 printf, malloc, exit 等函數，非常經典，我們會在本系列文章中介紹這個虛擬機。

該專案的 GitHub 頁面：https://github.com/rswier/c4

其授權許可證為：GPL-2.0 license

## 修改後的 c4

c4 寫得很好，但是其虛擬機沒有獨立成函數，另外沒有中文註解，所以我 fork 後修改了一版放在以下網址

* https://github.com/ccc-c/c4

並且寫了 C4 的設計與說明文件，請參考

* https://github.com/ccc-c/c4/wiki

## 編譯

```bash
ccckmit@asus MINGW64 /d/ccc/程式人雜誌/202401/01-c4
$ gcc c4.c -o c4
```

## 執行 hello.c

檔案: hello.c

```c
#include <stdio.h>

int main()
{
  printf("hello, world\n");
  return 0;
}
```

編譯執行 hello.c

```bash
ccckmit@asus MINGW64 /d/ccc/程式人雜誌/202401/01-c4
$ ./c4 hello.c
hello, world
exit(0) cycle = 9
```

印出 hello.c 的組合語言

```
ccckmit@asus MINGW64 /d/ccc/程式人雜誌/202401/01-c4
$ ./c4 -s hello.c
1: #include <stdio.h>
2:
3: int main()
4: {
5:   printf("hello, world\n");
    ENT  0
    IMM  5046432
    PSH
    PRTF
    ADJ  1
6:   return 0;
    IMM  0
    LEV
7: }
    LEV
```

## 費氏數列

檔案 test/fib.c

```c
#include <stdio.h>

int f(int n) {
  if (n<=0) return 0;
  if (n==1) return 1;
  return f(n-1) + f(n-2);
}

int main() {
  printf("f(7)=%d\n", f(7));
}
```

編譯執行 test/fib.c

```bash
$ ./c4 test/fib.c
f(7)=13
exit(8) cycle = 920
```

印出其 test/fib.c 的組合語言


```bash
ccckmit@asus MINGW64 /d/ccc/程式人雜誌/202401/01-c4
$ ./c4 -s test/fib.c
1: #include <stdio.h>
2:
3: int f(int n) {
4:   if (n<=0) return 0;
    ENT  0
    LLA  2
    LI
    PSH
    IMM  0
    LE
    BZ   0
    IMM  0
    LEV
5:   if (n==1) return 1;
    LLA  2
    LI
    PSH
    IMM  1
    EQ
    BZ   0
    IMM  1
    LEV
6:   return f(n-1) + f(n-2);
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    PSH
    JSR  4653208
    ADJ  1
    PSH
    LLA  2
    LI
    PSH
    IMM  2
    SUB
    PSH
    JSR  4653208
    ADJ  1
    ADD
    LEV
7: }
    LEV
8:
9: int main() {
10:   printf("f(7)=%d\n", f(7));
    ENT  0
    IMM  4915360
    PSH
    IMM  7
    PSH
    JSR  4653208
    ADJ  1
    PSH
    PRTF
    ADJ  2
11: }
    LEV
```

您可以看到上述的組合語言非常精簡，因為 c4 的虛擬機設計得很好，我們將在下期雜誌中介紹這個虛擬機的設計。






