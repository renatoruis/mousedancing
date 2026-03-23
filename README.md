<div align="center">

# Mouse Dancing

**Um toque no rato a cada 15 segundos — para o Windows não “dormir” à toa.**

[![CI](https://github.com/renatoruis/mousedancing/actions/workflows/build.yml/badge.svg)](https://github.com/renatoruis/mousedancing/actions/workflows/build.yml)
[![Release](https://img.shields.io/github/v/release/renatoruis/mousedancing?label=última%20release&logo=github)](https://github.com/renatoruis/mousedancing/releases)
[![Licença MIT](https://img.shields.io/badge/licença-MIT-3DA639.svg)](LICENSE)
[![Windows](https://img.shields.io/badge/Windows-x64-0078D6?logo=windows&logoColor=white)](https://www.microsoft.com/windows)
[![C](https://img.shields.io/badge/C-Win32-00599C?logo=c&logoColor=white)](https://github.com/renatoruis/mousedancing/blob/main/main.c)

</div>

---

Aplicação **mínima para Windows (64 bits)** que, em execução, **move o cursor um pixel de cada vez a cada 15 segundos** (ida e volta), para **atenuar o bloqueio automático** por inatividade.

Foi feita **só** para isso: leituras longas, chamadas, renders, ou qualquer tarefa em que o ecrã ou a sessão não devam bloquear por falta de “movimento”.

> **Aviso:** não contorna políticas de TI nem garante bloqueio zero — depende das definições do Windows, da rede e da organização.

## Funcionalidades

| | |
|---|---|
| **Bandeja do sistema** | Ícone junto ao relógio com tooltip *Mouse Dancing — em execução* |
| **Instalador** | `MouseDancing-Setup.exe` (NSIS): pasta em `%LOCALAPPDATA%`, **início automático**, entrada em *Aplicações instaladas* |
| **Portátil** | `mousedancing.exe` — um ficheiro, sem instalador |
| **Stack** | C, Win32 (`user32`, `shell32`), sem *runtime* extra |

## Download (recomendado)

Na **[Releases](https://github.com/renatoruis/mousedancing/releases)** descarrega o **`MouseDancing-Setup.exe`**.

- Instala em `%LOCALAPPDATA%\MouseDancing`
- **Adiciona à inicialização automática** (utilizador atual)
- Permite **desinstalar** em *Definições → Aplicações*
- No fim, **inicia** a app (ícone na bandeja)

O pacote de distribuição é um **instalador `.exe`** (NSIS). **Não há `.msi`** neste repositório.

### Publicar uma release (mantenedores)

Push para `main` **não** cria release nem anexa binários. Para publicar (ex.: `v0.0.1`):

```bash
git tag v0.0.1
git push origin v0.0.1
```

O workflow em Windows compila, gera o instalador e **cria a release no GitHub** com `mousedancing.exe` e `MouseDancing-Setup.exe`. Usa tags **`v*`** (`v1.0.0`, `v0.0.1`, …).

Podes também criar uma release na [página de Releases](https://github.com/renatoruis/mousedancing/releases) e publicar — o mesmo workflow anexa os ficheiros ao evento `release`.

## Versão portátil

Na mesma release: **`mousedancing.exe`** — copiar e executar; **não** regista início automático.

## Uso

1. **Ícone** na área de notificação → indica que está ativo  
2. **Botão direito** no ícone → **Sair**  
3. Instalação via Setup → **Desinstalar** em *Definições → Aplicações*

## Compilar (sem dependências em runtime)

Na raiz do projeto, no Windows:

```bat
build.bat
```

Gera `mousedancing.exe`. É preciso **Visual Studio** (`cl`) ou **MinGW-w64** (`gcc`), **64 bits**.

### Instalador local

1. Instalar [NSIS](https://nsis.sourceforge.io/Download)  
2. Copiar `mousedancing.exe` para `installer\`  
3. Correr `installer\build-installer.bat` (ajustar versão no `.bat` se quiseres)

## Licença

Este projeto está sob a **[licença MIT](LICENSE)** — uso livre, com o software “como está”.

O instalador é um script NSIS; o executável usa apenas APIs Win32.
