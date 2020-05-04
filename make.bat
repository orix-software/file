@echo off

SET BINARYFILE=file
SET PATH_RELEASE=build\usr\share\%BINARYFILE%\
SET ORICUTRON="..\..\..\oricutron-iss2-debug\"
set VERSION=1.0.2
SET ORIGIN_PATH=%CD%
echo %osdk%
SET PATH=%PATH%;%CC65%

mkdir build\bin
mkdir build\usr\share\doc\
mkdir build\usr\share\file\
mkdir build\usr\share\doc\%BINARYFILE%
mkdir build\usr\share\man

IF NOT EXIST build\usr\share\ipkg mkdir build\usr\share\ipkg      


echo #define VERSION "%VERSION%" > src\version.h
rem  123456789012345678
echo | set /p dummyName=file      1.0.2  display file type > src\ipkg\%BINARYFILE%.csv
echo Copy README.md
copy README.md build\usr\share\doc\%BINARYFILE%\
copy src\ipkg\%BINARYFILE%.csv build\usr\share\ipkg 
copy src\man\%BINARYFILE%.hlp build\usr\share\man\


cl65 -o build\bin\file -ttelestrat src\file.c

IF "%1"=="NORUN" GOTO End
copy build\bin\file %ORICUTRON%\sdcard\bin
copy src\man\%BINARYFILE%.hlp %ORICUTRON%\usbdrive\usr\share\man\
copy data\stormld.wav %ORICUTRON%\usbdrive\

copy src\ipkg\%BINARYFILE%.csv %ORICUTRON%\usbdrive\usr\share\ipkg\

cd %ORICUTRON%
Oricutron -mt
cd %ORIGIN_PATH%
:End


