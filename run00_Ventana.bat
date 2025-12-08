@echo off
cd /d "%~dp0"
if not exist bin\00_Ventana.exe (
    echo Compilando 00_Ventana.cpp...
    C:\msys64\mingw64\bin\g++.exe src\00_Ventana.cpp -o bin\00_Ventana.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude
)
if exist bin\00_Ventana.exe (
    echo Ejecutando 00_Ventana.exe...
    bin\00_Ventana.exe
) else (
    echo Error: No se pudo compilar 00_Ventana.exe
)
pause
