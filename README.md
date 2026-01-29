funny readme 

poopoo

build

In MSYS2 MINGW64
curl -O https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-sfml-2.6.1-1-any.pkg.tar.zst
pacman -U mingw-w64-x86_64-sfml-2.6.1-1-any.pkg.tar.zst
pacman -S mingw-w64-x86_64-make

Add to enviromentvariable path  
C:\msys64\mingw64\bin

in vscode do Set-Alias make mingw32-make
then you can do make, make run, make clean
