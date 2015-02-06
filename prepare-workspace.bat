@echo off
::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR:~0,-1%
set WorkspaceDir=%ProjectHome%\workspace
set ArduinoTools=%ProjectHome%\..\Tools
set ThisProjTools=%ProjectHome%\tools

::-----------------------------------------------------------------------------
:: Load Script Environment / Configuration
::-----------------------------------------------------------------------------
for /f "delims=" %%x in (%ProjectHome%\env.config) do (set "%%x")


::-----------------------------------------------------------------------------
:: Configured Settings
::-----------------------------------------------------------------------------
:: Processing IDE (see https://www.processing.org/download/?processing) 
:: http://download.processing.org/processing-2.2.1-windows64.zip
:: http://download.processing.org/processing-2.2.1-windows32.zip
::set ProcessingDownloadUrl=http://download.processing.org ::to be set in env.config
::set ProcessingVer=2.2.1 ::to be set in env.config

:: Arduino IDE (see http://arduino.cc/en/Main/OldSoftwareReleases) 
::set ArduinoDownloadUrl=http://arduino.cc/download.php?f=
::set ArduinoVer=1.5.6-r2 ::to be set in env.config

:: Eclipse Arduino Workbench Bundle (see http://www.baeyens.it/eclipse/download.php)
::set EclipseArduinoDownloadUrl=http://www.baeyens.it/eclipse/download/product
::set EclipseArduinoVer=2015-01-13_02-06-58 ::to be set in env.config

:: Expected Project Location (Eclipse CDT cannot deal with relative paths)
:: set ArduinoProjects=C:\git\arduino-projects ::to be set in env.config
set ExpectedProjectHome=%ArduinoProjects%\%ProjectSubDir%

::-----------------------------------------------------------------------------
:: Get the OS Variant
::-----------------------------------------------------------------------------
IF "%PROCESSOR_ARCHITECTURE%;%PROCESSOR_ARCHITEW6432%"=="x86;" (
  set OsVariant=win32
) ELSE (
  set OsVariant=win64
)

::-----------------------------------------------------------------------------
:: Assert correct path
::-----------------------------------------------------------------------------
if not "%ExpectedProjectHome%"=="%ProjectHome%" (
  msg "%username%" Please install this project %ProjectHome% here: %ExpectedProjectHome% - otherwise you would not be able to compile.
  if not exist "%ArduinoProjects%" (
    md "%ArduinoProjects%"
  )
  goto end
)


::-----------------------------------------------------------------------------
:: Set the tools' paths
::-----------------------------------------------------------------------------
:: Processing
set ProcessingRevs=%ArduinoTools%\processing_revs
set CurProcessing=%ProcessingRevs%\processing-%ProcessingVer%

:: Arduino IDE
set ArduinoRevs=%ArduinoTools%\arduino_revs
set CurArduino=%ArduinoRevs%\arduino-%ArduinoVer%

:: Eclipse Arduino Workbench Bundle
set EclipseArduinoRevs=%ArduinoTools%\eclipseArduino_revs
set CurEclipseArduino=%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%\eclipseArduino

:: 7Zip
set Archiver=%ThisProjTools%\7za920\7za.exe

:: wget
set Wget=%ThisProjTools%\wget\wget.exe

:: git
if "%OsVariant%"=="win32" (
  set Git="%ProgramFiles%\Git\bin\git.exe"
) else (
  set Git="%ProgramFiles(x86)%\Git\bin\git.exe"
)

::-----------------------------------------------------------------------------
:: Assert untouched .project file
::-----------------------------------------------------------------------------
:: ensure that src/.project has not been changed
set statusResult=
for /f "delims=" %%a in ('%%Git%% status --porcelain %%ProjectHome%%\src\.project') do @set statusResult=%%a
echo "%statusResult%"
if not "%statusResult%"=="" (
  msg "%username%" The file %ProjectHome%\src\.project is already touched. This script shall only be run on a vanilla project just cloned before.
  goto end
)

::-----------------------------------------------------------------------------
:: Get the tools
::-----------------------------------------------------------------------------
:: Processing
if not exist "%CurProcessing%" (
  if not exist "%ProcessingRevs%" (
    md "%ProcessingRevs%"
  )
  if not exist "%ProcessingRevs%\processing-%ProcessingVer%-%OsVariantLong%.zip" (
    %Wget% --tries=0 --output-document="%ProcessingRevs%\processing-%ProcessingVer%-%OsVariantLong%.zip" "%ProcessingDownloadUrl%/processing-%ProcessingVer%-%OsVariantLong%.zip"
  )
  %Archiver% x -y -o%ProcessingRevs% %ProcessingRevs%\processing-%ProcessingVer%-%OsVariantLong%.zip
  if %errorlevel% == 0 (
    del %ProcessingRevs%\processing-%ProcessingVer%-%OsVariantLong%.zip
  )
)
:: create softlink (junction) for Processing in current project tools
rmdir %ThisProjTools%\processing
mklink /J %ThisProjTools%\processing %CurProcessing%

:: Arduino IDE
if not exist "%CurArduino%" (
  if not exist "%ArduinoRevs%" (
    md "%ArduinoRevs%"
  )
  if not exist "%ArduinoRevs%\arduino-%ArduinoVer%-windows.zip" (
    %Wget% --tries=0 --output-document="%ArduinoRevs%\arduino-%ArduinoVer%-windows.zip" "%ArduinoDownloadUrl%/arduino-%ArduinoVer%-windows.zip"
  )
  %Archiver% x -y -o%ArduinoRevs% %ArduinoRevs%\arduino-%ArduinoVer%-windows.zip
  if %errorlevel% == 0 (
    del %ArduinoRevs%\arduino-%ArduinoVer%-windows.zip
  )
)
:: create softlink (junction) for Arduino IDE in current project tools
rmdir %ThisProjTools%\arduino
mklink /J %ThisProjTools%\arduino %CurArduino%

:: Eclipse Arduino Workbench Bundle
if not exist "%CurEclipseArduino%" (
  if not exist "%EclipseArduinoRevs%" (
    md "%EclipseArduinoRevs%"
  )
  if not exist "%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz" (
    %Wget% --tries=0 --output-document="%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz" "%EclipseArduinoDownloadUrl%/%OsVariant%.%EclipseArduinoVer%.tar.gz"
  )
  %Archiver% x -y -o%EclipseArduinoRevs% %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz
  %Archiver% x -y -o%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer% %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar
  if %errorlevel% == 0 (
    del %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz
	del %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar
  )
)
:: create softlink (junction) for Eclipse Arduino Workbench Bundle in current project tools
rmdir %ThisProjTools%\eclipseArduino
mklink /J %ThisProjTools%\eclipseArduino %CurEclipseArduino%

:: unpack Eclipse metadata in workspace
if not exist "%WorkspaceDir%\.metadata" (
  %Archiver% x -y -o%WorkspaceDir% "%WorkspaceDir%\.metadata.zip"
)

::-----------------------------------------------------------------------------
:: Perform Workaround Eclipse Arduino Bug (removed Library links in .project file after first [failing] build)
::-----------------------------------------------------------------------------
:: run first build, would fail
call build.bat
if %errorlevel% == 0 goto end
:: revert src/.project that have been made dirty by the failing build
%Git% checkout -- %ProjectHome%\src\.project

:: run second build
call build.bat
if %errorlevel% == 0 goto end

:error
msg "%username%" An error occured!
::pause

:end
