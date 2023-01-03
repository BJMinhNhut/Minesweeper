@echo off
mkdir resources
windres sources/sounds.rs -O coff -o resources/sounds.res
windres sources/icon.rc -O coff -o resources/icon.res
g++ sources/main.cpp resources/sounds.res resources/icon.res -o Minesweeper -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -static -static-libgcc -static-libstdc++ -O2 -lwinmm -mwindows
if %ERRORLEVEL% NEQ 0 (
	echo Compile error 
) else echo Compile successfull