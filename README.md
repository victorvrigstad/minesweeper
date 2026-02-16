# Minesweeper (SFML, C++)

Simple Minesweeper game built in C++ with SFML.

## Important version note

This project currently targets **SFML 2.6.1**.
It may not compile/run correctly with newer SFML 3.x versions without code changes.

## Requirements

- Windows
- MSYS2 (MinGW64 shell)
- `g++`
- `mingw32-make`
- SFML **2.6.1**

## Install dependencies (MSYS2 MinGW64)

1. Update packages:

```bash
pacman -Syu
```

2. Install compiler and make:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

3. Install SFML 2.6.1 explicitly:

```bash
curl -O https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-sfml-2.6.1-1-any.pkg.tar.zst
pacman -U mingw-w64-x86_64-sfml-2.6.1-1-any.pkg.tar.zst
```

## Add MinGW64 to PATH

Add this folder to your Windows `Path` environment variable:

```txt
C:\msys64\mingw64\bin
```

## Build and run

From project root:

```bash
mingw32-make clean
mingw32-make
mingw32-make run
```

## Optional PowerShell alias

If you want to type `make` instead of `mingw32-make`:

```powershell
Set-Alias make mingw32-make
```

Then you can run:

```bash
make
make run
make clean
```

## Project structure

- `include/` headers
- `src/` source files
- `resources/images/` tile textures
