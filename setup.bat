@echo off
windres sources/sounds.rs -O coff -o sounds.res
windres sources/icon.rc -O coff -o icon.res
g++ sources/main.cpp sounds.res icon.res -o Minesweeper -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -static -static-libgcc -static-libstdc++ -O2 -lwinmm -mwindows
if %ERRORLEVEL% NEQ 0 (
	echo Compile error 
) else echo Compile successful
del sounds.res
del icon.res