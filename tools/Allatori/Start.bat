@echo off
title Allatori-Obfuscator
color a
java -Xms2G -Xmx2G -jar AllatoriGetter.jar
color b
del o.jar
del renaming-log.xml
cls
echo [INFO] Obfuscating...
java -Xms2G -Xmx2G -jar lib\allatori.jar config.xml
color D
echo [INFO] DONE!
timeout 5