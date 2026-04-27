@echo off
echo ============================================
echo     STC32G144K246 Cleanup Script
echo ============================================
echo.

set SCRIPT_DIR=%~dp0
echo Working Directory: %SCRIPT_DIR%
echo.

cd /d "%SCRIPT_DIR%"

echo [1/3] Cleaning bulid directories...
for /d /r %%d in (bulid) do @if exist "%%d" echo Deleting: %%d && rd /s /q "%%d" 2>nul

echo.
echo [2/3] Cleaning *.uvopt files...
for /r %%f in (*.uvopt) do @if exist "%%f" echo Deleting: %%f && del /f /q "%%f" 2>nul

echo.
echo [3/3] Cleaning *.uvgui.* files...
for /r %%f in (*.uvgui.*) do @if exist "%%f" echo Deleting: %%f && del /f /q "%%f" 2>nul

echo.
echo ============================================
echo     Cleanup Complete!
echo ============================================
echo.

pause
