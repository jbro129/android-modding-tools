@echo off
echo Amount of data to generate (1000 - 999999). 
echo.
echo The bigger the number, the more secure it gets but the more time it takes to complete. 5000-20000 is a suggested value.
echo.
echo.
echo If you need help, please see the official topic on iOSGods.
echo.
set /p iosgods="Your Value: "
set /p iosgods2="armv7 or arm64 or elfarmv7: "
start "" "cpad.exe" "%~f1" "%iosgods%" "%iosgods2%" 

REM If you want the .bat to automatically output the file to your desired location, use the command below instead of the command above.
REM start "" "%USERPROFILE%\Desktop\CPAD\cpad.exe" "%~f1" "%iosgods%" "%iosgods2%" "%USERPROFILE%\Desktop\OUTPUTFILENAME"

exit /b