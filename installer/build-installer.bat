@echo off
setlocal
cd /d "%~dp0"

if not exist "mousedancing.exe" (
  echo ERRO: Coloque mousedancing.exe nesta pasta.
  echo Compile na raiz com build.bat e depois: copy ..\mousedancing.exe .
  exit /b 1
)

where makensis >nul 2>&1
if %ERRORLEVEL% neq 0 (
  echo ERRO: NSIS nao encontrado. Instale: https://nsis.sourceforge.io/
  exit /b 1
)

makensis /DAPP_VERSION=0.0.3 mousedancing.nsi
if %ERRORLEVEL% neq 0 exit /b 1
echo OK: MouseDancing-Setup.exe
exit /b 0
