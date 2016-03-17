Lab2-1.exe input.txt output.txt
IF ERRORLEVEL 1 GOTO err

Lab2-1.exe input2.txt output2.txt
IF ERRORLEVEL 1 GOTO err

Lab2-1.exe input3.txt output3.txt
IF ERRORLEVEL 1 GOTO err

Lab2-1.exe input4.txt output4.txt
IF ERRORLEVEL 1 GOTO err

Lab1.exe output.tx output.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
PAUSE
EXIT

:err
ECHO Programtestingfailed :-(
PAUSE