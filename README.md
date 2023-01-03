# Minesweeper
Author: Dang Minh Nhut - 22125071 - 22TT1 - HCMUS

This is a game made for the CS161 final project based on 
Microsoft's Minesweeper game using C++ and graphics.h 
library. It was developed from October 2022 to January 2023.

## Features
- 5 game modes: Weak, Fit, Strong, Superhero, Custom 
- Continue unfinished game in previous session
- Save best finished play time
- Game sound 

## Youtube demo
[![Watch the video](https://img.youtube.com/vi/4dfjIGfTMjc/default.jpg)](https://youtu.be/4dfjIGfTMjc)

## Compile instruction for Windows
### a. Clone git repository
```cmd
git clone https://github.com/BJMinhNhut/Minesweeper.git
cd Minesweeper
```
### b. Build resources
```cmd
windres sounds.rs -O coff -o sounds.res
windres icon.rc -O coff -o icon.res
```
### c. Compile 
```cmd
g++ main.cpp include\sounds.res include\icon.res -o Minesweeper -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -static -static-libgcc -static-libstdc++ -O2 -lwinmm -mwindows
```
### d. Run game
#### i.	On Windows Powershell
```cmd
.\Minesweeper
```
#### ii.	On Command Prompt
```
Minesweeper
```
