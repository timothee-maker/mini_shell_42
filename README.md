**A POSIX-compliant shell — 42 School Project**

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Shell](https://img.shields.io/badge/Shell-bash_--posix-4EAA25?style=for-the-badge&logo=gnubash&logoColor=white)](https://www.gnu.org/software/bash/)
[![Docker](https://img.shields.io/badge/Docker-ready-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)

*By [Timothée Nolent](https://github.com/tnolent) & [Louis de Guillebon](https://github.com/ldeguill)*

</div>

---

## 📖 About

**Minishell** is a 42 School system programming project that re-implements a Unix shell from scratch, modeled after `bash --posix`. The goal is to deeply understand how a shell works under the hood — from raw input parsing to process execution, piping, and I/O redirection.

> *"To understand the shell, you must become the shell."*

---

## ✨ Features

| Feature | Status |
|---|---|
| Command execution | ✅ |
| Pipes `\|` | ✅ |
| Input redirection `<` | ✅ |
| Output redirection `>` | ✅ |
| Append redirection `>>` | ✅ |
| Here-doc `<<` | ✅ |
| Environment variables `$VAR` | ✅ |
| Exit status `$?` | ✅ |
| Built-in commands | ✅ |
| Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) | ✅ |

### Built-in Commands

```
echo    cd    pwd    export    unset    env    exit
```

---

## 🚀 Getting Started

### Prerequisites

- **Linux** — nothing to install
- **Other OS** — [Docker](https://www.docker.com/get-started) required

---

### 🐧 Linux

```bash
# Clone the repository
git clone https://github.com/tnolent/minishell.git
cd minishell

# Build and run
make
./minishell
```

---

### 🐳 Docker (macOS / Windows)

```bash
# Build the Docker image
docker build -t minishell .

# Run the shell interactively
docker run -it --rm minishell
```

---

## 🏗️ Architecture

Minishell is built around two distinct modules that work in sequence.

```
User Input
    │
    ▼
┌─────────────┐
│   LEXER     │  Tokenizes raw input into meaningful units
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   PARSER    │  Builds a linked list of commands with tokens
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  EXECUTOR   │  Forks, pipes, redirects and executes
└──────┬──────┘
       │
       ▼
   Output / Next prompt
```

---

### 🔍 Parsing

The parser transforms a raw input string into an exploitable data structure:

- Splits the line by `|` into a **linked list**, one node per command
- Assigns a **token** (`CMD`, `ARG`, `INFILE`, `OUTFILE`, ...) and an **argument** to each node
- Returns the structured list ready for execution

---

### ⚡ Execution

The executor processes the parsed list and runs each command through a file-based pipeline:

```
.infile  ──►  STDIN  ──►  [ execve ]  ──►  STDOUT  ──►  .outfile
```

**Step by step:**

1. Creates a structure for each command line
2. Spawns one subprocess per pipe segment
3. Funnels all arguments and input files into `.infile`
4. Redirects `.infile` → `STDIN` at `execve` time
5. Redirects `STDOUT` → `.outfile` at `execve` time
6. Executes the command via `execve`
7. Prints `.outfile` if no pipe follows
8. Clears `.infile`
9. Appends `.outfile` → `.infile` if a pipe follows
10. Clears `.outfile`

---

## 📁 Project Structure

```
minishell/
├── src/
│   ├── parsing/        # Lexer, parser, token handling
│   ├── execution/      # Command execution, pipes, redirections
│   ├── builtins/       # Built-in command implementations
│   └── utils/          # Helper functions
├── include/
│   └── minishell.h     # Main header
├── Dockerfile
├── Makefile
└── README.md
```

---

## 👥 Authors

<div align="center">

| <img src="https://github.com/tnolent.png" width="80" style="border-radius:50%"/> | <img src="https://github.com/ldeguill.png" width="80" style="border-radius:50%"/> |
|:---:|:---:|
| **Timothée Nolent** | **Louis de Guillebon** |
| [@tnolent](https://github.com/tnolent) | [@ldeguill](https://github.com/ldeguill) |

</div>

---

<div align="center">

*42 School — System Programming · 2024*

</div>
