@echo off
setlocal
cd /d "%~dp0"

REM Gera mousedancing.exe (64-bit) — precisa de MSVC (cl) OU MinGW-w64 (gcc) no PATH.
REM shell32: ícone na bandeja (Shell_NotifyIcon).

where cl >nul 2>&1
if %ERRORLEVEL%==0 (
  echo [build] Usando MSVC cl...
  cl /nologo /O2 /W3 /Fe:mousedancing.exe main.c /link /SUBSYSTEM:WINDOWS user32.lib shell32.lib
  if %ERRORLEVEL% neq 0 exit /b 1
  del main.obj 2>nul
  echo OK: mousedancing.exe
  exit /b 0
)

where gcc >nul 2>&1
if %ERRORLEVEL%==0 (
  echo [build] Usando MinGW-w64 gcc...
  gcc -O2 -mwindows -o mousedancing.exe main.c -luser32 -lshell32 -m64
  if %ERRORLEVEL% neq 0 exit /b 1
  echo OK: mousedancing.exe
  exit /b 0
)

echo ERRO: Nao encontrei cl ^(Visual Studio^) nem gcc ^(MinGW-w64^) no PATH.
exit /b 1
