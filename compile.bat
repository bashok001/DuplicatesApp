echo off
cls
echo "Building Duplicates App"
echo ----------------------------------------------
devenv DuplicatesApp.sln /rebuild debug
copy Debug\Executive.exe .