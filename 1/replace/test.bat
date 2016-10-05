set PROGRAM="%~1"
@echo off

rem invalid number of arguments
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

rem no such file
%PROGRAM% no_such_file.txt %TEMP%\output.txt awe ee
IF NOT ERRORLEVEL 1 GOTO err

rem empty search string
%PROGRAM% multiline_text.txt %TEMP%\output.txt "" HEL
IF NOT ERRORLEVEL 1 GOTO err

rem multiline text
%PROGRAM% multiline_text.txt %TEMP%\output.txt Hel HEL
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\output.txt multiline_text_out.txt
IF ERRORLEVEL 1 GOTO err

rem recursive text
%PROGRAM% recursive.txt %TEMP%\output.txt 1231234 abcabcde
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\output.txt recursive_out.txt
IF ERRORLEVEL 1 GOTO err

rem recursive with delete out
%PROGRAM% recursive.txt %TEMP%\output.txt 1 ""
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\output.txt recursive_with_delete_out.txt
IF ERRORLEVEL 1 GOTO err

rem repeated text
%PROGRAM% repeated_text.txt %TEMP%\output.txt aa a
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\output.txt repeated_text_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Testing succeeded
EXIT /b

:err
ECHO Testing failed
EXIT /b
