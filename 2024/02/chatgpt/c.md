## 請寫一篇 1000 字的 C 語言新語法 (C11 之後的改變)

自從C11標準之後，C語言引入了一些新的語法和功能，這些改變使得C語言更加現代和易於使用。在本篇文章中，我將介紹一些C11之後的主要新語法。讓我們一起來看看這些新特性吧！

1. `_Bool` 布爾數據類型：
C語言一直缺乏原生的布爾數據類型，但C11引入了`_Bool`類型，用來表示`true`和`false`。這個類型只佔據一個字節大小，並且能夠直接進行邏輯運算。

```c
#include <stdbool.h>

_Bool flag = true;
if (flag) {
    printf("flag is true\n");
}
```

2. `static_assert` 斷言：
C11引入了`static_assert`關鍵字，用於在編譯時檢查一些常數的真偽。這可以幫助開發者捕捉到在編譯時期就可以解決的錯誤。

```c
static_assert(sizeof(int) == 4, "int should be 4 bytes");
```

3. 匿名結構和匿名聯合：
C11允許聲明匿名結構和匿名聯合，這意味著結構或聯合類型可以直接聲明而無需定義一個具體的名字。這樣可以更加方便地在需求中使用。

```c
struct {
    int x;
    int y;
} point;

union {
    int num;
    float fnum;
} number;
```

4. 泛型選擇表達式（Generic Selections）：
C11引入了泛型選擇表達式，可以根據不同的類型來執行不同的代碼塊。這樣可以減少代碼重複和提高代碼的可讀性。

```c
#define get_max(x, y) _Generic((x), \
    int: max_int, \
    float: max_float)(x, y)

int max_int(int a, int b) {
    return (a > b) ? a : b;
}

float max_float(float a, float b) {
    return (a > b) ? a : b;
}

int main() {
    int a = 5, b = 10;
    float c = 5.0, d = 10.0;

    int max1 = get_max(a, b);
    float max2 = get_max(c, d);

    printf("Max(int): %d\n", max1);
    printf("Max(float): %.2f\n", max2);

    return 0;
}
```

5. `_Generic` 通用選擇運算符：
`_Generic`是一個通用的選擇運算符，根據給定的類型選擇對應的表達式或值。這裡的`_Generic`與前面的泛型選擇表達式中的`_Generic`不同，前者是運算符，後者是控制結構。

```c
#define stringize(x) _Generic((x), \
    int: "integer", \
    float: "float", \
    char: "character", \
    default: "unknown type")

int main() {
    int a = 5;
    float b = 5.0;
    char c = 'A';

    printf("Type of a: %s\n", stringize(a));
    printf("Type of b: %s\n", stringize(b));
    printf("Type of c: %s\n", stringize(c));

    return 0;
}
```

這些只是C11之後的一些新語法的介紹，還有很多其他的特性和改進。這些新的語法和功能使得C語言更加現代且更容易使用，提供了更多的彈性和表達能力。我們鼓勵開發者學習和使用這些新特性，以便在項目開發中更好地發揮C語言的優勢。