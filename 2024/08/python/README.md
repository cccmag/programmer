# Python：程式與歷史 (8) -- 從語言到機器

有了馮紐曼架構，機器指令就能被放入記憶體執行了

但是人類很難直接寫二進位的機器指令，所以發展出了組合語言這樣的文字形式。

不過組合語言還是很難寫，因此人類繼續尋求更好的程式寫法，於是開始設計高階語言。

問題是、高階語言到底應該長得怎麼樣呢？

一個想法是，我們為何不用自然語言來寫程式呢？

## 用自然語言寫程式？

雖然喬姆斯基在 1956 年就已經提出了生成語法，但是人類設計出來的語法，卻很難掌握人類的語言。

要設計一套能 100% 描述人類語言的 BNF 語法，是非常困難的 ...

雖然我們可以用幾條語法就產生看來像人類寫的文章，但那些語法通常只在人造的小世界裡有效，在真實多變的世界裏，沒辦法完全掌握。

[COBOL]:https://en.wikipedia.org/wiki/COBOL

一種可能性是設計一種看來很像人類語言的《人造程式語言》，[COBOL] 差不多就是在這樣的背景下被設計出來的，但是這樣的語言看來有點冗長與囉嗦，打字也要打很多。

```cobol
ADD 1 TO x
ADD 1, a, b TO x ROUNDED, y, z ROUNDED

ADD a, b TO c
    ON SIZE ERROR
        DISPLAY "Error"
END-ADD

ADD a TO b
    NOT SIZE ERROR
        DISPLAY "No error"
    ON SIZE ERROR
        DISPLAY "Error"
```

## 用 λ-Calculus 寫程式？

那麼我們為何不用丘奇所構想的那種 λ-Calculus 來寫程式呢？λ-Calculus 理論上不是也具有圖靈機相等的威力嗎？

[LISP]:https://en.wikipedia.org/wiki/Lisp_(programming_language)

其實也不是沒有人這樣做，像是 [LISP] 這個語言，雖然沒有採用 λ 這個詞，設計上卻和 λ-Calculus 非常類似，所以在 LISP 程式語言的經典名著 [Structure and Interpretation of Computer Programs](https://web.mit.edu/6.001/6.037/sicp.pdf) 當中，幾乎把整套 λ-Calculus 搬了過來，只是保留了《整數、布林、浮點，字串》這些基本型態而已。

```lisp
(defun factorial (n)
    (if (zerop n) 1
        (* n (factorial (1- n)))))
```

## 用數學語言寫程式？

對於數學家而言，如果有個程式語言可以模仿《一階邏輯》的寫法，那是否能幫助數學家發現更多更好的數學定理呢？

PROLOG 基本上就是這樣一個程式語言，

```prolog
father_child(john, mary).
father_child(john, sally).
 
sibling(X, Y)      :- parent_child(Z, X), parent_child(Z, Y).
 
parent_child(X, Y) :- father_child(X, Y).
parent_child(X, Y) :- mother_child(X, Y).
```

然後你就可以用邏輯語句問 Prolog，他會拿去推理得到答案後在回答體，像是這樣

```
?- sibling(sally, erica).
Yes
?- sibling(X, Y).
sibling(mary, sally).
```

## 從高階語言到組合語言

目前受歡迎的高階語言，有些採用編譯技術，有些採用解譯技術。

* 編譯式語言： 像是 C / C++ / Java / C# / ... 等等
* 解譯式語言： 像是 Python / JavaScript / Ruby / .. 等等

編譯式語言還有區分成，編譯為虛擬機的機器碼 (Java/C#)，或者直接編譯為目標機的機器碼 (C/C++)。

目前的編譯器支援的功能通常較多，你可以選擇編譯為機器碼，或者是編譯為組合語言。(像是 gcc 加上 -S 參數就可以輸出組合語言)

對於解譯式的語言，為了增快速度，也可能會採用立即編譯 JIT 的技術來加速。

而這些編譯解譯技術的發展，基本上就是沿襲《喬姆斯基生成語法》的那一套機制，例如採用 《遞迴下降法》 的方式來撰寫剖析器 Parser，剖析完成之後再進行《程式碼產生、或者是直接計算模擬》等動作。

## 編譯器

以下是一個簡易的運算式編譯器的 Python 程式碼

```py
from random import *

"""
E = F ([+-] F)*
F = [0-9] | (E)
"""

def newTemp():
    global tempTop
    tempTop += 1
    return f"T{tempTop}"

def E():
    f = F()
    while isNext("+-"):
        op = next("+-")
        f2 = F()
        t = newTemp()
        print(f"{t} = {f} {op} {f2}")
        f = t
    return f

def F():
    if isNext("("):
        next("(")
        e = E()
        next(")")
        return e
    else:
        return next("0123456789")

def isNext(array):
    global ti, tokens
    if ti>=len(tokens): return False
    return tokens[ti] in array

def next(array):
    global ti
    if isNext(array):
        token = tokens[ti]
        ti += 1
        return token
    else:
        print('======== error ===========')
        print(''.join(tokens))
        print(f"{ti*' '}^")
        print(f'錯誤: 位置 {ti} 應該是 {array} 的元素，但卻發現 {tokens[ti]}')
        raise

def compile(code):
    global ti, tokens, tempTop
    ti, tokens, tempTop = 0, list(code), 0
    print(code)
    E()

compile("3+(5-8)+7")
```

執行結果

```
$ python expCompiler.py
3+(5-8)+7
T1 = 5 - 8
T2 = 3 + T1
T3 = T2 + 7
```

在上述範例中，我們只將運算式這樣的高階語法，轉換成較低階的中間碼，但是還沒有轉換成組合語言。

不過從中間碼轉換成組合語言的過程是比較容易理解的，我們就不進一步作示範了。

## 解譯器

如果不將高階語言轉換成組合語言或機器碼，那麼也可以採用解譯的方式，直接執行高階語言。

舉例而言， λ-Calculus 就是一個設計很精簡的語言。

那麼我們能不能設計一個程式去執行 λ-Calculus 程式呢？

我在 github 上面發現 ElliotPenson 寫了以下專案

* https://github.com/ElliotPenson/Nameless

不過該專案的語法是 Python 2，我把它 fork 後改成了 Python 3 如下：

* https://github.com/ccc-py/Nameless

然後我們就可以在其中執行 λ-Calculus 的程式了，以下是一個執行範例

```
$ python nameless
nameless!
Type 'quit' to exit.
> (λm.((m λt.λf.t) λx.λt.λf.f) λz.λs.z)
(λm.((m λt.λf.t) λx.λt.λf.f) λz.λs.z)
((λz.λs.z λt.λf.t) λx.λt.λf.f)
(λs.λt.λf.t λx.λt.λf.f)
λt.λf.t
> (λx.λy.(x y) y)
(λx.λy.(x y) y)
λa.(y a)
> quit
```

你可以看到上述的 nameless 解譯器，會不斷將 λ-Calculus 的算式用下列法則代換

1. α-conversion (更改名稱)
    * $(\lambda x.M[x])\rightarrow (\lambda y.M[y]) $
2. β-reduction (參數替換)
    * $(\lambda x.M)\ N\rightarrow M[x:=N]$

而這就是 λ-Calculus 語言的完整運作法則了 

所以， λ-Calculus 也可以成為一個高階語言，只是我們可能會很不適應而已，畢竟有 Python 和 C ，我們應該不會想用 λ-Calculus 來寫程式。

不過如果將 λ-Calculus 的觀念現代化，讓它更好用，就能發展出能和 Python 同樣好用的語言，這就是所謂的 Functional Programming Language 了，除了前述的 LISP 之外，現在還有 Clojure 和 Haskell 這些語言

1. Clojure -- https://clojure.org/
2. Haskell -- https://www.haskell.org/

這些函數式編程語言，其實也有不少支持愛用者 ...

## 結語

對於寫程式的人來說，語言和機器的能力相同，其實是非常自然的

因為我們用《電腦》來執行《程式》，其中的電腦就是機器，程式就是語言

程式能做到的，電腦就能做到，電腦能做到的，程式就能做到，這是我們每天寫程式一直在體會的事情，但是卻很少被意識到或說出來。

一階邏輯是個語言， Lambda Calculus 也是個語言，這些語言基本上都可以用《喬姆斯基的生成語法表示》

有限狀態機、堆疊自動機、圖靈機、甚至是真正的電腦，都是機器。

但是這些機器，如果從數學上看，又都是一堆符號，例如：

1. 輸入、輸出都是符號
2. 狀態可以用符號表示
3. 狀態的轉移可以用《符號形成的字串》表示
4. 磁帶上的資訊也可以用符號表示
5. 甚至 CPU 裏的暫存器與電路，也可以用《符號形成的字串》表示 (Verilog 這種硬體描述語言也是一個字串)

所以《機器、語言、數學、Calculus、Logic、Algebra》這些模型，最後都能表達一個《系統》，如果把這樣的系統給抽象化之後，又都變成了《字串》，然後被存在檔案當中。

於是機器變成了數學，數學變成了文字，這些文字又可以被拿來轉換建構成機器。

不管是《實體系統》還是《形式系統》，只要講清楚運作方法，都可以成為字串而儲存起來，而且也經常可以被放在電腦上執行。

這大概就是本書的標題：

> 數學、語言、機器與程式 -- 從希爾伯特到圖靈的那些故事

所想表達的事情。

至於到底是《數學比較重要，還是工程比較重要》這種永遠沒有結論的問題，就留給辯論家去爭論好了。

理論和實務，通常是一體兩面，而且相輔相成的。理論可以給實務一些啟發指引，而理論的正確性也得經由實驗來驗證，然後經由工程師根據理論與經驗，轉化為現實世界的作品。

可惜的是，實務經常和現實世界結合緊密，所以一旦環境改變，那些實務經常就無法再被實踐了。

例如程式語言有千百種，而且一直在更新，換了又換，舊的程式就不能跑了。

CPU 的架構也是琳瑯滿目，想要從一種處理器換到另一種，通常是艱鉅的工程。

但是理論有個好處，就是不太隨時間而變化，因此希爾伯特、哥德爾、丘奇、圖靈、庫克、喬姆斯基的那些理論，才能經過這個多年，還能讓我們了解，而且還可以用 python 實作出來，這大概就是我們這本書想要達到的目的。

用一個現代的語言，讓你清楚的了解一百年來的那些和程式密切相關的理論，到底是怎麼一回事

透過程式的實作，你可以穿越時空，掌握千百年來的那些奧秘

用現代人的角度，去體會古代人的思想體系。

或許、那些數學與理論，並不是那麼的枯燥，而是在你的電腦上可以實際展現出來的。

電腦、程式、數學和語言，經常只是系統的不同表達形式而已，是一體多面的，理解了這些載體之間的相關性，或許我們有機會在巨人的肩膀上，看得更高更遠也說不定 ...


1900 年，當時聲望如日中天的希爾伯特 (David Hilbert) ，在巴黎舉行的第二屆國際數學家大會上作了題為《數學問題》的演講，提出了 23 道最重要的數學問題。

![](./img/Hilbert23Question.png)

其中的第 2 問題《算術公理之相容性》對程式領域產生了重大的影響，但是要了解這個問題，我們得先從《數學領域中的公理系統》開始講起。

## 何謂定理證明

歐洲在文藝復興前期，從穆斯林手上翻譯回了原本失落的《幾何原本》，這本《歐幾里得》的數學著作，成為文藝復興的重要數學典籍。

透過幾何原本，歐洲人發現原來古希臘就有這麼高的數學成就，整個幾何學可以透過《點線面圓》等基本定義，以及一些簡單的公理系統，透過明確的推論法則，一步一步建構出來。

這種透過公理系統建構定理的手法，基本上就是數學家最重要的任務。

問題是，我們能不能將這樣的數學推論給自動化，形式化呢？

這大概就是希爾伯特第 2 問題想要知道的事情了！

要更清楚的說明這個問題，用幾何學描述比較不好說，希爾伯特更想要的是從邏輯學開始的那種描述。

而這種邏輯學的描述，源自於《亞里斯多德》的三段式論。

[亞里斯多德]:https://zh.wikipedia.org/zh-tw/%E4%BA%9A%E9%87%8C%E5%A3%AB%E5%A4%9A%E5%BE%B7
[蘇格拉底]:https://zh.wikipedia.org/zh-tw/%E8%8B%8F%E6%A0%BC%E6%8B%89%E5%BA%95

[亞里斯多德] 曾用 [蘇格拉底] 為例說明三段式論：

1. 大前提：人都會死
2. 小前提：蘇格拉底是人
3. 結論：蘇格拉底會死

但是這樣的邏輯還是有點不精確，也有點複雜，如果我們用現代的 [一階邏輯] 表達，那就可以寫成下列邏輯式

1. ∀x People(x) => Mortal(x)  # Mortal 代表會死的，∀x 代表對於所有的 x。所以這句是說只要 x 是人， x 就會死
2. People(Socrates) 
3. Mortal(Socrates)

[一階邏輯](https://zh.wikipedia.org/zh-tw/%E4%B8%80%E9%98%B6%E9%80%BB%E8%BE%91)

除了 ∀ 代表《對於所有》 之外，還有 ∃ 這個符號代表《存在》，這是一階邏輯的基本符號。

這種一階邏輯，是現代數學企圖將古希臘的邏輯公理化的嘗試。

[布林邏輯]:https://zh.wikipedia.org/zh-tw/%E5%B8%83%E5%B0%94%E4%BB%A3%E6%95%B0

但是一階邏輯還是有點複雜，如果用更簡單的 [布林邏輯] 來示範公理系統與推論法則，那麼會更容易理解。

假如我們有下列事實與規則庫：

    事實： A, B
    規則庫：
        C => G
        A => E
        B => F
        E&F => H

那麼請問我們能推論出 H 嗎？

[肯定前件]:https://zh.wikipedia.org/wiki/%E8%82%AF%E5%AE%9A%E5%89%8D%E4%BB%B6

關於這個問題，我們可以採用 Modus Ponuns ( [肯定前件] ) 推論法則進行

Modus Ponuns 推論法則如下

    P
    P => Q
    -------
    Q

於是我們可以有下列推論

    A
    A => E
    -------
    E

    B
    B => F
    -------
    F

    E&F=>H
    E
    F
    -------
    H

經由《事實+規則庫》，透過  Modus Ponuns 法則，我們可以一步一步推論出 H 是對的。

這就是布林邏輯的一個嚴格推論法範例。

針對這種推論方法，我們寫了一個 Python 的推論引擎範例

```py
def satisfy(exp, facts): # 檢查 facts 是否滿足邏輯式 exp
    vars = exp.split("&")
    for var in vars:
        if not var.strip() in facts:
            return False
    return True

def gen(facts, rules): # 嘗試推論出新的事實
    gen_new = False
    for rule in rules:
        left, right = rule.split("=>")
        if satisfy(left, facts):
            gens = right.split("&")
            for g in gens:
                if not g in facts:
                    print("facts=", facts)
                    facts.add(g)
                    print(f"inference:\n\t{left}\n\t{rule}\n\t-------\n\t{g}\n\n")
                    gen_new = True

    return gen_new

def inference(facts, rules): # 推論引擎
    i=1
    while True:
        print(f"=========gen {i}============")
        if not gen(facts, rules): # 反覆推論，直到失敗為止
            print('沒有新的結果產生 ... ，推論完畢！')
            break
        i = i+1

def load(file):
    facts = set()
    rules = []

    with open(file, "r", encoding="utf-8") as f:
        text = f.read().replace(" ", "")

    for line in text.split("\n"):
        if line.find("=>") != -1:
            rules.append(line)
        elif len(line)>0:
            facts.add(line)
            
    return facts, rules

import sys
facts, rules = load(sys.argv[1]) # 載入知識庫
inference(facts, rules) # 開始推論
```

然後，我們先寫一個簡單的邏輯知識庫 test.kb 當作輸入

檔案: test.kb

```
E&F=>H
A=>E
C=>G
B=>F
A
B
```

用 inference.py 推論執行結果如下

```
$ python inference.py test.kb
=========gen 1============
facts= {'A', 'B'}
inference:
        A
        A=>E
        -------
        E


facts= {'A', 'B', 'E'}
inference:
        B
        B=>F
        -------
        F


=========gen 2============
facts= {'A', 'B', 'E', 'F'}
inference:
        E&F
        E&F=>H
        -------
        H


=========gen 3============
沒有新的結果產生 ... ，推論完畢！
```

這個測試顯示 inference.py 透過知識庫 test.kb 可以經由 A 與 A=>E 推出 E, 由 B 與 B=>F 推論出 F，最後再由 E, F 與 E&F=>H 推論出 H。

接著讓我們引入動物世界的資料庫，對於 《會飛+生蛋+長腿》這樣的事實，推論看看到底會是甚麼動物？

知識庫: animal.kb

```
有毛 => 哺乳類
泌乳 => 哺乳類
有羽毛 => 鳥類 
會飛 & 生蛋 => 鳥類
哺乳類 & 吃肉 => 食肉類
有爪 & 利齒 & 兩眼前視 => 食肉類
哺乳類 & 有蹄 => 有蹄類
哺乳類 & 反芻 => 偶蹄類
哺乳類 & 吃肉 & 斑點 => 獵豹
哺乳類 & 吃肉 & 條紋 => 老虎
有蹄類 & 長腿 & 斑點 => 長頸鹿
有蹄類 & 條紋 => 斑馬
鳥類 & 長腿 => 鴕鳥

會飛
生蛋 
長腿
```

然後再用 inference.py 推論執行結果如下

```
$ python inference.py animal.kb
=========gen 1============
facts= {'生蛋', '會飛', '長腿'}
inference:
        會飛&生蛋
        會飛&生蛋=>鳥類
        -------
        鳥類


facts= {'生蛋', '鳥類', '會飛', '長腿'}
inference:
        鳥類&長腿
        鳥類&長腿=>鴕鳥
        -------
        鴕鳥


=========gen 2============
沒有新的結果產生 ... ，推論完畢！
```

## 希爾伯特想要甚麼？

現在，我們可以清楚的說明希爾伯特的第二問題想要甚麼了 ...

希爾伯特問的是，有沒有可能透過像上述這樣的形式化推論，讓數學定理透過機械化的方式自動被證明出來

而且更重要的是，這樣的機械化方式，是否能證明所有的定理 (完備性)，這大概就是希爾伯特第二問題的想法。

但是、我們上述的推論方法，稱為前向推論方法，基本上就是採用 Modus Ponuns ( [肯定前件] ) 推論法則進行的。


說明：

1. 上述的系統並不能推論出所有的定理，例如我們的系統無法推論出 [笛摩根定律] ，因為我們的系統只會推論出單一的布林變數，而不是邏輯法則。
2. 但是若我們引入一些 [公理] [Axioms] ，搭配 Modus Ponuns ，就有可能推論出像 [笛摩根定律] 這樣的邏輯法則，例如以下的公理系統
    1. $p\to (q\to p)$
    2. $(p\to (q\to r))\to ((p\to q)\to (p\to r))$
    3. $(\neg p\to \neg q)\to (q\to p)$

關於進一步的推論法則，請參考 [Propositional Calculus] ，像是 [Simple axiom system] 或 [Natural deduction system] 。

[Simple axiom system]:https://en.wikipedia.org/wiki/Propositional_calculus#Example_1._Simple_axiom_system
[Natural deduction system]:https://en.wikipedia.org/wiki/Propositional_calculus#Example_2._Natural_deduction_system

[Gödel's completeness theorem]:https://en.wikipedia.org/wiki/G%C3%B6del%27s_completeness_theorem

[Gödel's incompleteness theorems]:https://en.wikipedia.org/wiki/G%C3%B6del%27s_incompleteness_theorems

[Propositional Calculus]:https://en.wikipedia.org/wiki/Propositional_calculus

[笛摩根定律]:https://zh.wikipedia.org/zh-tw/%E5%BE%B7%E6%91%A9%E6%A0%B9%E5%AE%9A%E5%BE%8B

問題是，有沒有甚麼方法可以推論出所有為真的邏輯法則，也就是所有的《定理》呢？

這大概就是希爾伯特想知道的答案了！

[希爾伯特計劃]:https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E4%BC%AF%E7%89%B9%E8%AE%A1%E5%88%92

為了這個想法，希爾伯特除了將其放在 23 個問題中的第二個之外，還於 1920 年提出了 [希爾伯特計劃] (Hilbert Program) ，企圖為為全部的數學提供一個堅實穩固的理論基礎。

具體來說，這個基礎應該包括：

1. 所有數學的形式化。意思是，所有數學應該用一種統一的嚴格形式化的語言，並且按照一套嚴格的規則來使用。
2. 完備性。我們必須證明以下命題：在形式化之後，數學裡所有的真命題都可以被證明（根據上述規則）。
3. 一致性。我們必須證明：運用這一套形式化和它的規則，不可能推導出矛盾。
4. 保守性。我們需要證明：如果某個關於「實際物」的結論用到了「假想物」（如不可數集合）來證明，那麼不用「假想物」的話我們依然可以證明同樣的結論。
5. 確定性。應該有一個算法，來確定每一個形式化的命題是真命題還是假命題。

[希爾伯特綱領]:https://zhuanlan.zhihu.com/p/372622407

而這個計畫的核心理念，也被稱為 [希爾伯特綱領] 。

## 結語

希爾伯特的第 2 問題《算術公理之相容性》，換做電腦的語言，可以想成是否能寫一個程式，自動證明所有算術方面的定理呢？

這個問題，後來被《哥德爾、丘奇、圖靈》等人分別用不同的手法，在不同的領域問過類似的問題，但可惜答案都是否定的。
