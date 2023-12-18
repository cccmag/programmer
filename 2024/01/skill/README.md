# 套件安裝器

    本文為 ChatGPT 撰寫，經作者校閱修改
    prompt : 請寫一篇 1000 字的 gcc 工具鏈用法

> 不同系統的套件管理工具解析：Chocolatey、Homebrew、APT、Pacman、Yum

## 引言

在不同的作業系統中，套件管理工具是一個極為重要的元件，它們讓使用者可以輕鬆地安裝、更新、卸載軟體套件。本文將探討五種不同系統的套件管理工具，分別是Chocolatey（Windows）、Homebrew（macOS）、APT（Ubuntu/Debian）、Pacman（Arch Linux/Windows msys2）、以及Yum（Fedora/CentOS）。

## Chocolatey (Windows)：

Chocolatey是Windows平台上的套件管理工具，通常用於自動化軟體安裝與管理。

它使用PowerShell腳本來執行安裝、卸載和更新操作。

使用者可以透過命令列介面快速安裝軟體，例如 `choco install <package>`

在使用 Chocolatey 之前，你必須先用《系統管理員》身分進入《 Powershell》去《安裝 choco》，請參考下列網址

* https://chocolatey.org/install

其中有個指令很長，您必須複製後貼到 Powershell 上執行，然後就會安裝 Chocolatey 到您的電腦中

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

您可以到下列網址查詢，找到您需要的 choco 套件

* https://community.chocolatey.org/packages

接著您就可以使用下列指令安裝 mingw 來獲得 C 語言編譯器 gcc 工具鏈。

    choco install mingw

或者用下列指令安裝 deno 

    choco install deno

或者用下列指令安裝 python

    choco install python

雖然這些套件通常可以直接從網站上下載安裝，但是對程式人而言，用指令安裝套件還是比較快速好用的。

## Homebrew (macOS)：

Homebrew是macOS上的套件管理工具，使用Ruby語言編寫。

透過Homebrew，使用者能夠在終端機中輕鬆安裝、更新和卸載軟體。

在您的 iMac 上使用 Homebrew 之前，請參考 https://brew.sh/ 用下列指令安裝 Homebrew

    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

安裝軟體的命令為 `brew install <package>

## Linux 的安裝管理員

Linux 的各種發行版當中，都會內建安裝管理員，像是

1. (Ubuntu/Debian/WSL Ubuntu) 內建 apt
2. (Arch Linux / Windows MSYS2) 內建 pacman
3. (Fedora / CentOS) 內建 yum

因此您可以直接用，不需要另外安裝套件管理員。

## APT (Ubuntu/Debian)

APT（Advanced Package Tool）是Ubuntu和Debian等Linux發行版中的套件管理工具。

它使用.deb套件格式，並透過apt-get和apt等命令進行套件管理。
例如，要安裝軟體可以使用 `sudo apt-get install <package>`

## Pacman (Arch Linux / Windows msys2)

Pacman是 Arch Linux 與 Windows MSYS2 上的套件管理工具，被用來安裝、更新和卸載軟體。

使用者可以透過終端機中的命令 `pacman -S <package>` 來安裝軟體。

## Yum (Fedora/CentOS)

Yum（Yellowdog Updater, Modified）是用於Fedora和CentOS等Linux發行版的套件管理工具。

使用者可以透過 `yum install <package>` 的命令來安裝套件。

## 結論

不同的作業系統擁有各自獨特的套件管理工具，這些工具使得軟體的安裝、更新和卸載變得更加簡單和便捷。無論是 Windows、macOS、還是不同的 Linux 發行版，套件管理工具都是促進軟體管理的重要工具，提供了一致且方便的方式來處理軟體套件的安裝與管理。
