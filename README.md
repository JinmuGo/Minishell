# Minishell

A minimal custom UNIX-style shell written in C, **Minishell** implements core shell behaviors—prompt input, tokenization, parsing, built-in commands, pipelines, redirections, environment variable expansion, and signal handling—according to the 42cursus specifications

## Features

* **Interactive prompt** with command history (via GNU Readline)
* **Lexing & parsing**: full support for quotes (`'`, `"`), escapes (`\`), and environment variable expansion (`$VAR`)
* **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* **Pipelines** (`|`) connecting multiple processes with correct file-descriptor management
* **Redirections**: input (`<`), output overwrite (`>`), append (`>>`), and heredoc (`<<`)
* **Signal handling** for `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+) to mimic Bash
* **Exit status** propagation (`$?`) across commands

## Installation

Ensure you have **GCC** or **Clang**, **Make**, and the **Readline** library installed on your UNIX-like system.

### Mac OS

```bash
brew install readline
```

### Ubuntu

```bash
sudo apt-get install libreadline-dev
```

---

```bash
git clone https://github.com/JinmuGo/Minishell.git
cd Minishell
make
```

## Usage

Launch the shell executable and start entering commands:

```bash
$ ./minishell
minishell$ echo "Hello, world!"
Hello, world!
minishell$ ls -la | grep minishell > files.txt
```

* Exit the shell with `exit` or `Ctrl+D`.
* Use arrow keys to navigate command history.

## Project Structure

```text
Minishell/
├── lib/                   # Custom utility library (libft-like)
├── src/                   # Core implementation
│   ├── built_in/          # Built-in commands
│   ├── data_structure/    # Data structure
│   ├── envp_command/      # Environment variable command
│   ├── executor/          # Command execution
│   ├── expander/          # Expander
│   ├── meta_command/      # Meta command
│   ├── parser/            # Parser
│   ├── signal_controller/ # Signal management
│   ├── tokenize/          # Tokenization
│   ├── utils/             # Helper functions
├── Makefile               # Build rules
└── README.md
```

## Makefile Targets

* `make`: compile `minishell` with `-Wall -Wextra -Werror`
* `make clean`: remove object & archive files
* `make fclean`: `clean` + remove `minishell` executable
* `make re`: `fclean` + `make`

---
