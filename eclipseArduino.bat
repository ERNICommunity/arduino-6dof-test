::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR%
set WorkspaceDir=%ProjectHome%\workspace
set ThisProjTools=%ProjectHome%\tools

:: Run the workbench
start %ThisProjTools%\eclipseArduino\eclipseArduinoIDE.exe -data %WorkspaceDir%
