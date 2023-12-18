# Deno (1): 比 node.js 更新的 JavaScript server 執行環境

    本文為 ChatGPT 撰寫，經作者校閱修改
    prompt : 請寫一篇 1000 字的 gcc 工具鏈用法


## 導論

Deno 是一個現代、安全且具有高度簡潔設計的運行時環境，用於執行 JavaScript 和 TypeScript 代碼。它是由 Node.js 的創始人 Ryan Dahl 領導的開源項目，目的是解決 Node.js 中的一些問題，同時引入新的特性和安全機制。Deno 的名字是 "Node" 的字母重新排列，代表著 Node.js 的進化。

## 特點

1. 安全性

    Deno 被設計成一個安全的運行時環境，充分考慮了在執行 JavaScript 代碼時的安全問題。與 Node.js 不同，Deno 默認情況下禁用了文件系統和網絡的訪問權限，需要額外的權限參數才能啟用。這使得 Deno 在預防潛在威脅方面更為堅固，提供了更高的安全性。

2. TypeScript 集成

    Deno 對 TypeScript 的支持是內置的，無需額外的配置。開發者可以直接使用 TypeScript 來編寫代碼，享受強大的類型檢查和編輯器支持。這種內置的 TypeScript 集成使得 Deno 成為開發現代 JavaScript 和 TypeScript 應用的理想選擇。

3. 面向 ES 標準

    Deno 采用了面向 ECMAScript（ES）標準的設計理念，遵從現代 JavaScript 和 Web API 標準。這使得 Deno 與瀏覽器和其他 JavaScript 運行時更為一致，並提供了更加一致的開發體驗。

4. 高度簡潔

    Deno 的代碼庫被設計為模組化和簡潔，使得整個運行時環境變得易於理解和擴展。這種簡潔的設計有助於提高性能和減少潛在的 bug，同時使 Deno 成為一個開發者友好的工具。

5. 內置工具

    Deno 包含了一系列內置工具，如運行時文件檢查器（runtime file checker）和格式化工具。這些工具使得代碼的測試、調試和維護更加方便，提高了開發流程的效率。

## 安裝 Deno

Deno 提供了一個簡單的安裝過程，支持多種操作系統。開發者可以通過官方提供的安裝腳本或包管理器來安裝 Deno。以下是一個基本的安裝示例：

```bash
curl -fsSL https://deno.land/x/install/install.sh | sh
```

安裝完成後，你可以使用以下命令來確認 Deno 是否成功安裝：

```
deno --version
```

## 使用 Deno

Deno 提供了一個簡單而直觀的 API，開發者可以用來運行 JavaScript 和 TypeScript 代碼。以下是一個簡單的 "Hello, Deno!" 程序示例：

檔案: hello.ts

```js
console.log("Hello, Deno!");
```

執行結果：

```
deno run hello.ts
```

## 生態系統

Deno 生態系統在不斷發展，支持豐富的第三方模組。開發者可以使用 Deno 的內置模組系統或通過 URL 直接引入模組。這使得 Deno 生態系統更加靈活和現代化。

雖然 Deno 是一個強大的運行時環境，但相較於 Node.js 仍然有一些缺點。以下是一些可能影響開發者選擇的 Deno 的缺點：

1. 生態系統相對較小： 相較於 Node.js，Deno 的生態系統相對較小。在 Node.js 中，有豐富的第三方模組和工具，而 Deno 的生態系統仍在不斷發展。這可能導致在使用 Deno 開發時需要自行實現某些功能，或者面臨缺少成熟解決方案的情況。

2. 不完全兼容 Node.js： Deno 在一些方面與 Node.js 不完全兼容。例如，Deno 中使用的模組系統是 ECMAScript 模組（ESM），與 Node.js 中的 CommonJS 不同。這可能需要進行一些調整，尤其是當遷移現有的 Node.js 專案到 Deno 時。

3. 社區支持： Node.js 擁有一個龐大且活躍的社區，這使得開發者可以輕鬆找到解決問題的資源和支持。相對而言，Deno 的社區規模還在擴大，可能在某些情況下難以找到相應的支持。

4. 成熟度和穩定性： Deno 是一個相對較新的項目，相較於 Node.js 的成熟度和穩定性可能還有差距。開發者在選擇使用 Deno 時需要考慮到這點，特別是對於需要在生產環境中運行的應用。

5. 遷移成本： 如果你已經有一個基於 Node.js 的項目，將其遷移到 Deno 上可能需要一些額外的工作。這包括對代碼的修改，以適應 Deno 的模組系統、API 差異等。

## 總結

Deno 是一個開發者友好、安全、簡潔的 JavaScript 和 TypeScript 運行時環境。其安全機制、內置 TypeScript 集成、面向 ES 標準的設計和簡潔的代碼庫使其在現代 Web 開發中具有競爭力。

Deno 的執行速度比 node.js 更快一些，但是卻比 node.js 的另一個執行環境 bun 更慢一些。

* https://bun.sh/

所以在決定要使用 deno 還是 node.js 的時候，或許您會心裡有點掙扎。

我從 2020 年開始使用 deno ，最喜歡的部分如下：

1. deno 刻意將函式庫做得和 web 版本一樣，像是 fetch API 等等
2. deno 指令的瑞士刀設計，可以用 deno xxx 來調用，例如 deno run / deno compile / deno test 等等
3. deno 可以直接支援 typescript ，不需要再安裝其他編譯轉換工具
4. deno 有 deno deploy 可以讓你透過 github 專案，直接佈署並上線。(但缺點是 deno deploy 沒有提供資料庫功能，得使用其他廠商，像是 Amazon 的 DynamoDB，Fauna 的 FaunaDB 或 Google Firebase，MongoDB Atlas 等等)。

接下來的幾期雜誌中，我們會對 deno 進行更深入的介紹。



