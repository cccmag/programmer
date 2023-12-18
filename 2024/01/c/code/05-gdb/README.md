# gdb

## 用法

```
$ gcc -g fact.c -o fact.o
$ gdb fact.o
```

gdb 指令

```
r: run
n: next  (空白也行)
p: print (p x=1 會把 x 設成 1 後再印出)
```

## 進階用法

* https://stackoverflow.com/questions/6121094/how-do-i-run-a-program-with-commandline-arguments-using-gdb-within-a-bash-script

```
$ gdb --args executablename arg1 arg2 arg3
```

範例

```
$ gdb --args c6.exe -u test/sum.o
```

## 參考文獻

* [不要急著印出位址，善用 GDB](https://hackmd.io/@sysprog/c-standards?type=view#%E4%B8%8D%E8%A6%81%E6%80%A5%E8%91%97%E5%8D%B0%E5%87%BA%E4%BD%8D%E5%9D%80%EF%BC%8C%E5%96%84%E7%94%A8-GDB)
    * [introduction to GDB a tutorial - Harvard CS50](https://www.youtube.com/watch?v=sCtY--xRUyI)

