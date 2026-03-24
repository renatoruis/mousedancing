; Instalador Mouse Dancing — NSIS 3.x (Unicode)
; Instala em AppData do utilizador, regista na inicialização do Windows e cria entrada em "Adicionar ou remover programas".

Unicode true
RequestExecutionLevel user

!ifndef APP_VERSION
  !define APP_VERSION "0.0.4"
!endif

!define APP_NAME "Mouse Dancing"
!define APP_EXE "mousedancing.exe"
!define REG_UNINST "Software\Microsoft\Windows\CurrentVersion\Uninstall\MouseDancing"

Name "${APP_NAME} ${APP_VERSION}"
OutFile "MouseDancing-Setup.exe"
InstallDir "$LOCALAPPDATA\MouseDancing"
InstallDirRegKey HKCU "${REG_UNINST}" "InstallLocation"

!include "MUI2.nsh"

!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "English"

Section "Instalar"
  SetOutPath $INSTDIR
  File "${APP_EXE}"

  ; Inicialização automática (sessão do utilizador atual)
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "MouseDancing" "$INSTDIR\${APP_EXE}"

  ; Desinstalador e registo "Adicionar ou remover programas"
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  WriteRegStr HKCU "${REG_UNINST}" "DisplayName" "${APP_NAME}"
  WriteRegStr HKCU "${REG_UNINST}" "DisplayVersion" "${APP_VERSION}"
  WriteRegStr HKCU "${REG_UNINST}" "Publisher" "renatoruis"
  WriteRegStr HKCU "${REG_UNINST}" "InstallLocation" "$INSTDIR\"
  WriteRegStr HKCU "${REG_UNINST}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKCU "${REG_UNINST}" "QuietUninstallString" "$INSTDIR\Uninstall.exe /S"

  ; Arrancar já após instalar
  Exec "$INSTDIR\${APP_EXE}"
SectionEnd

Section Uninstall
  Delete "$INSTDIR\${APP_EXE}"
  Delete "$INSTDIR\Uninstall.exe"
  DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "MouseDancing"
  DeleteRegKey HKCU "${REG_UNINST}"
  RMDir "$INSTDIR"
SectionEnd
