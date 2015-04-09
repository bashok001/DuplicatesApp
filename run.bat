echo off
cls
echo Demonstrating Requirement 3,4,8
echo --------------------------------
echo Cataloging recursively
Executive Test /s *.* 
pause

cls
echo Demonstrating Requirement 3,4,8
echo --------------------------------
echo Cataloging files with no recursion
Executive Test *.*
pause

cls
echo Demonstrating Requirement 3,5,8
echo --------------------------------
echo Cataloging and displaying duplicate Files
Executive Test /d /s *.*
pause

cls
echo Demonstrating Requirement 6,8
echo ------------------------------
echo Searching files with search text AVL
Executive Test /s *.* /f AVL
pause

cls
echo Demonstrating Requirement 7,8
echo ------------------------------
echo No input parameters are specified
Executive
pause

cls
echo Demonstrating Requirement 3,6,8
echo -------------------------------
echo Searching files with search text and multiple patterns
Executive Test /s /f AVL *.h *.c?
pause