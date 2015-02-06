@echo off
::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR:~0,-1%
set WorkspaceDir=%ProjectHome%\workspace
set ThisProjTools=%ProjectHome%\tools


::-----------------------------------------------------------------------------
:: Load Script Environment / Configuration
::-----------------------------------------------------------------------------
for /f "delims=" %%x in (%ProjectHome%\env.config) do (set "%%x")


::-----------------------------------------------------------------------------
:: Build Target Name
::-----------------------------------------------------------------------------
::set buildTarget=arduino_6dof_test ::to be set in env.config

::-----------------------------------------------------------------------------
:: Get the OS Variant
::-----------------------------------------------------------------------------
IF "%PROCESSOR_ARCHITECTURE%;%PROCESSOR_ARCHITEW6432%"=="x86;" (
  ::set OsVariant=win32
  set Vm-args=-Xms40m -Xmx384m -XX:MaxPermSize=384m
) ELSE (
  ::set OsVariant=win64
  set Vm-args=-Xms40m -Xmx512m -XX:MaxPermSize=512m -XX:-UseCompressedOops
)

%ThisProjTools%\eclipseArduino\eclipsec.exe -data %WorkspaceDir% -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild %buildTarget% -vmargs -Dorg.eclipse.cdt.core.console=org.eclipse.cdt.core.systemConsole %Vm-args%

EXIT /B %ERRORLEVEL%
