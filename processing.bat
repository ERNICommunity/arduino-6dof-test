::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR:~0,-1%
set ThisProjTools=%ProjectHome%\tools

:: Run the workbench
start %ThisProjTools%\processing\processing.exe
