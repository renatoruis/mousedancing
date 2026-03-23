# Mouse Dancing

Aplicação **mínima para Windows (64 bits)** que, ao ser executada, **move o cursor do rato um pixel de cada vez a cada 15 segundos** (alternando a direção), para **reduzir o bloqueio automático** do Windows quando não há atividade.

Foi criada **apenas** com esse propósito: evitar que o PC entre em bloqueio/pausa por inatividade em situações em que isso atrapalha (por exemplo, leitura longa, chamadas ou tarefas em segundo plano).

**Aviso:** não substitui políticas de segurança da empresa nem garante que o ecrã ou a sessão nunca bloqueiem — depende das definições do Windows e da rede.

## Como usar

1. Compila no Windows (ver abaixo) ou faz download do **ficheiro da [Releases](https://github.com/renatoruis/mousedancing/releases)**.
2. Executa `mousedancing.exe`.
3. Aparece um **ícone junto ao relógio** (área de notificação) a indicar que está em execução.
4. Clica com o **botão direito** no ícone e escolhe **Sair** para terminar.

## Compilar (sem dependências em runtime)

Na pasta do projeto, no Windows:

```bat
build.bat
```

É necessário **Visual Studio** (`cl` no PATH) ou **MinGW-w64** (`gcc` no PATH), ambos em modo 64 bits.

## Licença

Uso livre. O código é simples e autónomo (apenas APIs Win32).
