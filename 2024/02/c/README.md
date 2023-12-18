# C 語言的新語法

    本文有使用 ChatGPT 撰寫，並剪貼維基百科的內容，經《陳鍾誠》校閱修改
    ChatGPT prompt : 請寫一篇 1000 字的 C 語言新語法 (C11 之後的改變)

## C99 -- 1999 年

* https://en.wikipedia.org/wiki/C99


* 增強了預處理功能。例如：
巨集支持取可變參數 #define Macro(...) __VA_ARGS__
使用巨集的時候，允許省略參數，被省略的參數會被擴展成空串。
* 支持//開頭的單行注釋（這個特性實際上在C89的很多編譯器上已經被支持了）
* 增加了新關鍵字restrict, inline, _Complex, _Imaginary, _Bool
* 支持long long, long double _Complex, float _Complex 等類型
* 支持不定長的數組，即數組長度可以在運行時決定，比如利用變量作為數組長度。聲明時使用 int a[var] 的形式。不過考慮到效率和實現，不定長數組不能用在全局，或 struct 與 union 。
* 變量聲明不必放在語句塊的開頭，for語句提倡寫成 `for(int i=0;i<100;++i)` 的形式，即i只在for語句塊內部有效。

範例 1.

```c
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
```

* 允許採用type-name{xx,xx,xx}這樣類似C++的構造函數的形式構造匿名的結構體，即複合文字特性。
初始化結構體的時候允許對特定的元素賦值，形式為：

範例 1

```c
struct test{int a[3]，b;} foo[] = { [0].a = {1}, [1].a = 2 };
struct test{int a, b, c, d;} foo = { .a = 1, .c = 3, 4, .b = 5 }; // 3,4 是对 .c,.d 赋值的
```

範例 2

```c
struct Point {
    int x;
    int y;
};

struct Point myPoint = {.x = 1, .y = 2};
```


* 格式化字符串中，利用 \u 支持 unicode 的字符。
* 支持 16 進位的浮點數的描述。
* printf, scanf 的格式化串增加了對 long long int 類型的支持。
* 浮點數的內部數據描述支持了新標準，可以使用 #pragma 編譯器指令指定。
* 除了已有的 __LINE__和__FILE__ 以外，增加了__func__得到當前的函數名。
* 允許編譯器化簡非常數的表達式。
* 修改了/和%處理負數時的定義，這樣可以給出明確的結果，例如在C89中-22 / 7 = -3, -22 % 7 = -1，也可以-22 / 7= -4, -22 % 7 = 6。 而C99中明確為 -22 / 7 = -3, -22 % 7 = -1，只有一種結果。
* 取消了函數返回類型默認為 int 的規定。
允許在 struct 的最後定義的數組不指定其長度，寫做 [](flexible array member)。
const const int i 將被當作 const int i 處理。
* 增加和修改了一些標準頭文件，比如定義 bool 的 `<stdbool.h>` ，定義一些標準長度的int的`<inttypes.h>`，定義複數的 `<complex.h>`，定義寬字符的 `<wctype.h>`，類似於泛型的數學函數`<tgmath.h>`，浮點數相關的 `<fenv.h>`。在`<stdarg.h>` 增加了va_copy用於複製...的參數。`<time.h>` 里增加了struct tmx，對struct tm做了擴展。
* 輸入輸出對寬字符以及長整數等做了相應的支持。

## C11 -- 2011 年

* https://en.wikipedia.org/wiki/C11_(C_standard_revision)

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

6. static_assert

參考 -- https://en.cppreference.com/w/c/language/_Static_assert

```c
#include <assert.h> // no longer needed since C23
 
int main(void)
{
    // Test if math works, C23:
    static_assert((2 + 2) % 3 == 1, "Whoa dude, you knew!");
    // Pre-C23 alternative:
    _Static_assert(2 + 2 * 2 == 6, "Lucky guess!?");
 
    // This will produce an error at compile time.
    // static_assert(sizeof(int) < sizeof(char), "Unmet condition!");
 
    constexpr int _42 = 2 * 3 * 2 * 3 + 2 * 3;
    static_assert(_42 == 42); // the message string can be omitted.
 
    // const int _13 = 13;
    // Compile time error - not an integer constant expression:
    // static_assert(_13 == 13);
}
```

## C17 (也稱 C18) -- 2017 年

* https://en.wikipedia.org/wiki/C17_(C_standard_revision)

C17 沒有引入新的語言特性，只對C11進行了補充和修正。

## C23 -- 2023 年

* https://en.wikipedia.org/wiki/C23_(C_standard_revision)

C23是C語言的下一個標準，預計將取代C17（標準ISO/IEC 9899:2018），並有望於2024年成為ISO/IEC 9899:2024標準。C23最初於2016年以C2x的非正式名稱啟動，並且預計於2024年公開發布。截至2023年4月1日，C23的最新工作草案已公開。

以下是整合到C23最新工作草案的一些變更和新特性：

1. 標準庫
	* 新增memset_explicit()函數，用於在<string.h>中擦除敏感數據，不受優化影響。
	* 新增memccpy()函數，用於有效地串聯字符串，與POSIX和SVID C擴展類似。
	* 新增strdup()和strndup()函數，用於分配字符串的副本，與POSIX和SVID C擴展類似。
	* 新增memalignment()函數，用於確定指針的字節對齊。
	* 在新的標頭 `<stdbit.h>` 中新增位元工具函數、宏和類型，用於檢查許多整數類型的位元。所有這些都以stdc_開頭，以最小化與舊代碼和第三方庫的衝突。

2. 預處理器
	* 新增#elifdef和#elifndef指令，本質上相當於#elif defined和#elif !defined。
	* 新增#embed指令，用於包含二進制資源，以及__has_embed用於通過預處理器指令檢查資源的可用性。
	* 新增#warning指令，用於診斷。
	* 新增__has_include指令，用於通過預處理器指令檢查標頭的可用性。
	* 新增__has_c_attribute指令，用於通過預處理器指令檢查屬性的可用性。

3. 類型
	* 新增nullptr_t，一種空指針類型。
	* 新增_BitInt(N)和unsigned _BitInt(N)類型，用於位精確整數。新增BITINT_MAXWIDTH宏，用於最大位寬度。
	* 可變修改類型（但不包括自動變量）成為強制性功能。
	* 對於使用const的數組提供更好的支持。
	* 對typeof(...)運算符進行標準化。
	* 改變auto關鍵字的含義，使其在對象定義中引發類型推斷，同時保留其舊的存儲類別修飾符的含義。

4. 常量
	* 新增nullptr常量，用於nullptr_t類型。
	* 新增wb和uwb整數字面值後綴，用於_BitInt(N)和unsigned _BitInt(N)類型。
	* 新增0b和0B二進制字面值常量前綴。
	* 新增以'分隔的字面值常量，例如299'792'458。

5. 關鍵字
	* 新增true和false關鍵字。
	* 新增alignas、alignof、bool、static_assert、thread_local關鍵字，舊的關鍵字變成替代拼寫形式。
	* 新增_BitInt、typeof、typeof_unqual、nullptr、constexpr、_Decimal32、_Decimal64、_Decimal128關鍵字。

6. 語法
	* 標籤可以出現在聲明之前和復合語句的末尾。
	* 函數定義中可以有未命名的參數。
	* 使用{}進行零初始化（包括VLA的初始化）。
	* 變參數函數不再需要省略號之前的命名參數，va_start宏不再需要第二個參數，並且如果存在，不再評估任何第一個參數之後的參數。

7. 其他特性
	* 支援IEEE 754標準的新特性，包括擴展二進制浮點運算和（可選的）十進制浮點運算。
	* 對於對象的constexpr修飾符，不支持函數。
	* 新增char8_t類型，用於存儲UTF-8編碼的數據。改變u8字符常數和字符串字面值的類型為char8_t。
	* 明確指出所有char16_t字符串和字面值應該是UTF-16編碼的，而所有char32_t字符串和字面值應該是UTF-32編碼的，除非另有明確指定。
	* 允許存儲類別修飾符出現在復合字面量定義中。
