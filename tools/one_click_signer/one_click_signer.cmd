setlocal EnableDelayedExpansion
@ECHO off

SET /P rom=tell me the name and path of the apk/zip to sign?  

copy !rom! x!rom!

cd lib
rem sign the rom
java -Xmx512m -jar signapk.jar -w testkey.x509.pem testkey.pk8 ..\x!rom! ..\x!rom!

rem zip align
zipalign -f 4 ..\x!rom!  ..\signed-!rom!
cd ..\

del x!rom!