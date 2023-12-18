# Deno (2) -- 程式基礎 (JavaScript)

    本文為 ChatGPT 撰寫，經《陳鍾誠》校閱修改
    prompt : 請寫一篇 1000 字的 Deno 程式基礎

Deno 是一個用於執行 JavaScript 和 TypeScript 的運行時環境。它與 Node.js 相似，但具有更好的安全性和設計。在本文中，我們將介紹 Deno 的基礎知識，包括安裝 Deno、執行腳本以及使用內置模組等。

## Deno 腳本

Deno 支持執行 JavaScript 和 TypeScript 腳本。下面是一個簡單的示例腳本，創建一個 `hello.js` 文件，並添加以下代碼：

```javascript
console.log("Hello, Deno!");
```

要在 Deno 中執行該腳本，只需在終端機中輸入以下命令：

```bash
$ deno run hello.js
```

終端機將輸出 "Hello, Deno!"，這表示你已經成功執行了一個 Deno 腳本。

## 模組和依賴管理

與 Node.js 類似，Deno 也支持模組化編程。Deno 使用 URL 來引入模組，例如：

```javascript
import { sayHello } from "https://deno.land/x/mymodule/mod.ts";

sayHello("Deno");
```

上述代碼將從 "https://deno.land/x/mymodule/mod.ts" 引入模組中的 `sayHello` 函數，然後將其應用於 "Deno" 字符串。你可以將這段代碼保存在一個名為 `app.js` 的文件中，然後使用以下命令執行它：

```bash
$ deno run app.js
```

Deno 首次執行時，會自動下載並緩存模組。對於具有依賴關係的模組，Deno 會自動管理它們，以確保每個模組都是根據其標識符進行版本控制的。

## 權限管理

Deno 有一套完整的權限系統，可以幫助我們控制程式所擁有的權限。默認情況下，Deno 只允許訪問文件系統、網絡以及一些基本的運行時特性。當腳本需要更高的權限時，我們需要在執行時提供相應的權限。

例如，如果我們的腳本需要訪問文件系統，可以使用 `--allow-read` 參數：

```bash
$ deno run --allow-read app.js
```

如果需要網絡訪問權限，可以使用 `--allow-net` 參數：

```bash
$ deno run --allow-net app.js
```

這樣，Deno 將獲得相應的權限並執行腳本。

## 運行測試

Deno 內置了測試運行器，可以自動執行指定路徑下的測試文件。只需創建測試文件，並在其中添加適當的測試代碼即可。

例如，創建一個名為 `test.js` 的文件，包含以下測試代碼：

```javascript
Deno.test("Add function should return sum of two numbers", () => {
  const sum = add(2, 3);

  assertEquals(sum, 5);
});

function add(a, b) {
  return a + b;
}
```

然後在終端機中運行以下命令，執行測試：

```bash
$ deno test test.js
```

Deno 將運行 `test.js` 文件中的所有測試，並輸出測試結果。

以上是 Deno 的一些基礎知識，包括安裝 Deno、執行腳本、使用模組和管理權限。希望本文對你瞭解 Deno 程式基礎有所幫助！
