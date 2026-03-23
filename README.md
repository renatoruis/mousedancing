# Mouse Dancing

Aplicação **mínima para Windows (64 bits)** que, ao ser executada, **move o cursor do rato um pixel de cada vez a cada 15 segundos** (alternando a direção), para **reduzir o bloqueio automático** do Windows quando não há atividade.

Foi criada **apenas** com esse propósito: evitar que o PC entre em bloqueio/pausa por inatividade em situações em que isso atrapalha (por exemplo, leitura longa, chamadas ou tarefas em segundo plano).

**Aviso:** não substitui políticas de segurança da empresa nem garante que o ecrã ou a sessão nunca bloqueiem — depende das definições do Windows e da rede.

## Download (recomendado)

Na página **[Releases](https://github.com/renatoruis/mousedancing/releases)** faz download do **`MouseDancing-Setup.exe`**.

- Instala o programa em `%LOCALAPPDATA%\MouseDancing`
- **Adiciona à inicialização automática do Windows** (apenas para o teu utilizador)
- Regista entrada em **Definições → Aplicações → Aplicações instaladas** para desinstalar
- No fim da instalação, **inicia** a aplicação (ícone junto ao relógio)

O formato da release é um **instalador `.exe`** (NSIS). **Não há ficheiro `.msi`** neste repositório; o instalador `.exe` cumpre o mesmo papel para instalação e desinstalação.

## Versão portátil (sem instalador)

Na mesma release podes descarregar **`mousedancing.exe`** — executável único, sem registo na inicialização. Basta copiar e correr.

## Uso diário

1. Com o programa a correr, aparece um **ícone junto ao relógio**.
2. **Botão direito** no ícone → **Sair** para terminar.

Para remover a instalação feita pelo Setup: **Definições → Aplicações** → Mouse Dancing → **Desinstalar**.

## Compilar (sem dependências em runtime)

Na pasta do projeto, no Windows:

```bat
build.bat
```

Gera `mousedancing.exe`. É necessário **Visual Studio** (`cl` no PATH) ou **MinGW-w64** (`gcc` no PATH), ambos em modo 64 bits.

### Criar o instalador localmente

1. Instala o [NSIS](https://nsis.sourceforge.io/Download).
2. Coloca `mousedancing.exe` na pasta `installer\` (ou copia a partir da raiz após `build.bat`).
3. Executa `installer\build-installer.bat` (ajusta `APP_VERSION` no `.bat` se quiseres).

## Licença

Uso livre. O código da aplicação é simples e autónomo (apenas APIs Win32); o instalador é um script NSIS.
