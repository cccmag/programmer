# ld -- Gcc Linker

## 直接編譯連結

```
$ gcc main.c sum.c -o run
$ ./run
```

## 產生組合語言

```
$ gcc -S main.c -o main.s
$ gcc -S sum.c -o sum.s
```

## 組譯後連結

```
$ gcc main.c sum.s -o run
$ ./run
sum(10)=55
```

## 產生目的檔

```
$ gcc -c sum.c -o sum.o
$ gcc -c main.c -o main.o
```

## 連結目的檔

```
$ gcc main.o sum.o -o run
$ ./run
```
