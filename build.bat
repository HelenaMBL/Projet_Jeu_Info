cls

mingw32-make CandyCrush.exe Test.exe

if ERRORLEVEL 1 (
    exit /b 1
) 
chcp 65001
CandyCrush.exe 


 

