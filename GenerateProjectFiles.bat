echo off

echo Generating Visual Studio Solution...
"%~dp0/Binaries/premake5.exe" vs2019 --file="%~dp0/Scripts/premake_vs2019.lua"