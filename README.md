*This project has been created as part of the 42 curriculum by leilai, vabisco.*

# Minishell

A Unix shell implementation written in C, inspired by Bash.

Minishell is a project from the 42 School curriculum. Its purpose is to recreate the core behavior of a command-line shell while learning about lexical analysis, parsing, process creation, pipes, redirections, signals, environment variables, and file descriptor management.

---

## Table of Contents

- [Description](#description)
- [Instructions](#instructions)
- [Usage](#usage)
- [Features](#features)
- [Architecture](#architecture)
- [Parsing and AST](#parsing-and-ast)
- [Expansion](#expansion)
- [Execution](#execution)
- [Builtins](#builtins)
- [Signals](#signals)
- [Testing and Debugging](#testing-and-debugging)
- [Project Structure](#project-structure)
- [Design Decisions](#design-decisions)
- [Learning Outcomes](#learning-outcomes)
- [42 Project Constraints](#42-project-constraints)
- [Resources](#resources)
- [Authors](#authors)

---

## Description

Minishell is a command-line shell written in C as part of the 42 curriculum.

Its goal is to reproduce the core behavior of Bash required by the subject while developing a practical understanding of processes, file descriptors, pipes, redirections, signals, environment variables, lexical analysis, parsing, expansion, and command execution.

A shell does more than launch programs. It must first understand the command entered by the user, validate its syntax, expand variables and wildcards, build the correct execution order, and then manage the required processes and file descriptors.

This implementation follows a multi-stage architecture:

```text
User input
    |
    v
Lexer
    |
    v
Parser
    |
    v
Abstract Syntax Tree
    |
    v
Expansion
    |
    v
Executor
    |
    v
Builtins / execve / pipes / redirections
```

Each stage has a separate responsibility:

- **Lexer:** converts the input string into tokens.
- **Parser:** validates token order and builds the command structure.
- **AST:** represents commands, pipelines, redirections, logical operators, and subshells.
- **Expander:** processes environment variables, exit status, quotes, heredocs, and wildcards.
- **Executor:** traverses the AST and performs the required system calls.

---

## Instructions

### Evaluated repository

The evaluated version of this project is submitted through the Git repository assigned by 42.

Clone the repository using the URL provided through the 42 Intra, then enter the project directory:

```bash
cd minishell
```

### Compilation

Compile the project:

```bash
make
```

Run the shell:

```bash
./minishell
```

Remove object files:

```bash
make clean
```

Remove object files and the executable:

```bash
make fclean
```

Rebuild the project:

```bash
make re
```

### Public GitHub mirror

The public GitHub repository is provided as a reference copy of the project. It is not the repository used for the 42 submission or evaluation.

Because the GitHub mirror stores `libft` as a Git submodule, clone it with:

```bash
git clone --recurse-submodules https://github.com/laerena/minishell.git
cd minishell
```

If it was cloned without the submodule:

```bash
git submodule update --init --recursive
```

---

## Usage

Start Minishell:

```bash
./minishell
```

Example session:

```text
minishell$ echo "hello world"
hello world

minishell$ export USERNAME=Leia
minishell$ echo "$USERNAME"
Leia

minishell$ printf "hello\nworld\n" | grep hello
hello

minishell$ echo test > output.txt
minishell$ cat < output.txt
test

minishell$ echo $?
0
```

Exit the shell:

```bash
exit
```

---

## Features

### Mandatory part

| Feature | Status |
|---|:---:|
| Interactive prompt | ✓ |
| Command history | ✓ |
| Executable search using `PATH` | ✓ |
| Relative and absolute executable paths | ✓ |
| Single quotes | ✓ |
| Double quotes | ✓ |
| Environment variable expansion | ✓ |
| Previous exit status expansion with `$?` | ✓ |
| Pipes with `\|` | ✓ |
| Input redirection with `<` | ✓ |
| Output redirection with `>` | ✓ |
| Append redirection with `>>` | ✓ |
| Heredoc with `<<` | ✓ |
| Builtin commands | ✓ |
| Interactive signal handling | ✓ |

### Bonus part

| Feature | Status |
|---|:---:|
| Logical operators with `&&` and `\|\|` | ✓ |
| Parentheses for command priority | ✓ |
| Wildcard expansion with `*` | ✓ |

---

## Architecture

### Lexer

The lexer reads the raw command line and converts it into a doubly linked list of tokens.

Example input:

```bash
echo "hello world" > output.txt
```

Possible token representation:

```text
T_WORD       echo
T_WORD       "hello world"
T_REDIR_OUT  >
T_WORD       output.txt
```

The lexer recognizes:

- words
- pipes
- input and output redirections
- append redirections
- heredocs
- logical operators
- parentheses
- quoted sections

Quote information is preserved long enough for the expansion stage to apply the correct shell rules.

---

### Parser

The parser validates the token sequence and transforms it into an Abstract Syntax Tree.

Instead of executing commands immediately, the shell first creates a structured representation of the complete command line.

The parser supports AST nodes for:

```text
N_EXEC
N_PIPE
N_REDIR
N_AND
N_OR
N_SUBSHELL
```

This separation makes it easier to represent precedence and execution order.

---

## Parsing and AST

Example command:

```bash
cat input.txt | grep hello > result.txt
```

A simplified AST representation could look like:

```text
                 PIPE
                /    \
             EXEC    REDIR
              |        |
      cat input.txt   EXEC
                       |
                 grep hello
                       |
                  result.txt
```

The AST allows the executor to process each operation according to its node type instead of relying on one large execution function.

The main node categories are:

- **Execution nodes:** contain the argument vector and builtin information.
- **Binary operator nodes:** connect a left and right command.
- **Redirection nodes:** wrap another command and store redirection metadata.
- **Subshell nodes:** contain a child AST executed in a separate shell context.

---

## Expansion

Expansion is performed after parsing and before command execution.

### Environment variables

```bash
echo $HOME
```

The variable name is searched in the shell environment and replaced with its value.

### Previous exit status

```bash
echo $?
```

`$?` expands to the exit status of the previously executed command.

### Single quotes

Characters inside single quotes are treated literally:

```bash
echo '$HOME'
```

Output:

```text
$HOME
```

### Double quotes

Environment variables are expanded inside double quotes while spaces remain part of the same argument:

```bash
echo "$HOME"
```

### Wildcards

Unquoted wildcard patterns are expanded against matching directory entries:

```bash
echo *.c
```

### Heredoc expansion

The heredoc delimiter determines whether environment variables inside the heredoc body should be expanded.

Quoted delimiters disable expansion, while unquoted delimiters allow it.

---

## Execution

The executor traverses the AST and dispatches behavior according to the current node type.

Its responsibilities include:

- identifying builtins
- resolving external command paths
- creating child processes with `fork`
- executing programs with `execve`
- creating pipes with `pipe`
- replacing standard input and output with `dup2`
- opening redirection files with `open`
- closing unused file descriptors
- waiting for child processes with `waitpid`
- propagating exit statuses
- cleaning up heredoc resources

### External commands

External commands are resolved using the `PATH` environment variable unless the user provides an absolute or relative path.

Example:

```bash
ls -la
```

The shell searches each directory in `PATH` until an executable file is found.

### Pipelines

Example:

```bash
cat input.txt | grep hello | wc -l
```

Each command runs in its own process. The standard output of one command becomes the standard input of the next command.

### Redirections

Input redirection:

```bash
cat < input.txt
```

Output redirection:

```bash
echo hello > output.txt
```

Append redirection:

```bash
echo hello >> output.txt
```

Heredoc:

```bash
cat << EOF
hello
EOF
```

---

## Builtins

The following builtins are implemented:

| Builtin | Description |
|---|---|
| `echo` | Prints arguments, including support for the `-n` option |
| `cd` | Changes the current working directory |
| `pwd` | Prints the current working directory |
| `export` | Adds or updates environment variables |
| `unset` | Removes environment variables |
| `env` | Prints the environment |
| `exit` | Exits the shell |

Builtins that modify the shell state must run in the main shell process when they are not part of a pipeline.

For example:

```bash
cd ..
export NAME=value
unset NAME
exit
```

Running these commands only in a child process would not modify the state of the parent shell.

---

## Signals

The shell handles interactive signals differently depending on its current execution mode.

### At the prompt

- `Ctrl-C` cancels the current input and displays a new prompt.
- `Ctrl-\` is ignored.
- `Ctrl-D` exits when the input line is empty.

### During command execution

Signals are handled in a way that follows Bash behavior as closely as required by the project.

### During heredoc input

Heredoc input uses its own signal behavior so that `Ctrl-C` can interrupt heredoc collection without terminating the main shell.

---

## Testing and Debugging

### Standard compilation

```bash
make
```

### Rebuild

```bash
make re
```

### Debug build

The debug target adds debug symbols, disables optimization, and includes optional debug source files:

```bash
make debug
```

### AddressSanitizer and UndefinedBehaviorSanitizer

```bash
make sanitize
```

This build can help detect:

- invalid memory accesses
- use-after-free errors
- buffer overflows
- undefined behavior

### Valgrind

Run the shell with full leak checking:

```bash
make valgrind
```

Check open file descriptors:

```bash
make valgrind-fd
```

Readline may keep allocations until process termination. A suppression file can be used to separate Readline-owned memory from leaks caused by the project.

### Suggested manual tests

Simple commands:

```bash
echo hello
pwd
env
/bin/echo hello
```

Quotes and expansion:

```bash
echo '$USER'
echo "$USER"
echo "$?"
echo "a   b"
echo 'a   b'
```

Redirections:

```bash
echo hello > test.txt
cat < test.txt
echo world >> test.txt
cat test.txt
```

Pipes:

```bash
printf "one\ntwo\nthree\n" | grep two
cat test.txt | wc -l
```

Builtins:

```bash
export TEST=value
echo "$TEST"
unset TEST
echo "$TEST"
cd ..
pwd
```

Heredoc:

```bash
cat << EOF
hello $USER
EOF
```

Quoted heredoc delimiter:

```bash
cat << 'EOF'
hello $USER
EOF
```

Exit statuses:

```bash
false
echo $?
true
echo $?
command_that_does_not_exist
echo $?
```

Signals should also be tested at the prompt, during foreground commands, inside pipelines, and during heredoc input.

---

## Project Structure

```text
minishell/
├── include/
│   ├── struct.h
│   └── ...
├── libft/
├── src/
│   ├── builtins/
│   ├── executor/
│   ├── expander/
│   ├── init/
│   ├── lexer/
│   ├── parser/
│   ├── signals/
│   ├── utils/
│   ├── wildcards/
│   └── main.c
├── Makefile
├── README.md
└── readline.supp
```

Main modules:

```text
src/lexer       Token creation and operator recognition
src/parser      Syntax validation and AST construction
src/expander    Variables, quotes, heredocs, and argument expansion
src/executor    AST traversal, processes, pipes, and redirections
src/builtins    Shell builtin implementations
src/wildcards   Filename pattern expansion
src/signals     Interactive and execution signal modes
src/init        Shell context and environment initialization
src/utils       Shared utilities and cleanup helpers
```

---

## Design Decisions

### Why use an AST?

A shell command can contain several operations with different precedence rules.

Example:

```bash
cat file.txt | grep hello && echo found
```

Executing tokens directly from left to right would make it difficult to preserve the relationship between the pipeline and the logical operator.

An AST separates:

- lexical analysis
- syntax validation
- command representation
- expansion
- execution

This also allows each executor function to focus on one node type.

### Why preserve quotes until expansion?

Quotes change whether variables and wildcards should be expanded.

These commands must behave differently:

```bash
echo '$HOME'
echo "$HOME"
echo $HOME
```

Removing quotes too early would destroy the information required to distinguish the three cases.

### Why distinguish parent-shell and child-shell builtins?

Commands such as `cd`, `export`, `unset`, and `exit` modify the state of the shell itself.

When used as a standalone command, they must run in the main process.

When used inside a pipeline, they run in a child process because each pipeline stage requires its own process context.

### Why wrap commands in redirection nodes?

Representing redirections as AST nodes keeps file descriptor setup separate from the command itself.

A redirection node can:

1. open the required file
2. replace the relevant standard file descriptor
3. execute its child command
4. restore or clean up resources when required

---

## Learning Outcomes

This project develops practical understanding of:

- Unix process creation
- `fork`, `execve`, and `waitpid`
- pipes and file descriptors
- input and output redirection
- environment variable management
- lexical analysis
- recursive parsing
- Abstract Syntax Trees
- shell quoting rules
- signal handling
- memory ownership
- cleanup across parent and child processes
- debugging with sanitizers and Valgrind
- collaborative development with Git and GitHub

---

## 42 Project Constraints

The project is written in C and follows the 42 coding standard.

The implementation is restricted to the functions authorized by the Minishell subject and must provide behavior consistent with Bash for the features required by the project.

The shell should not interpret unsupported syntax that is outside the project scope unless it is explicitly implemented as a bonus feature.

---

## Resources

### Documentation and references

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Linux manual pages](https://man7.org/linux/man-pages/)
- Local manual pages used during development:
  - `man 2 fork`
  - `man 2 execve`
  - `man 2 pipe`
  - `man 2 dup2`
  - `man 2 open`
  - `man 2 waitpid`
  - `man 2 sigaction`
  - `man 3 readline`
- The Minishell subject provided by 42
- Bash, used as the behavioral reference for the features required by the subject

### AI usage

AI tools were used as learning and support tools for:

- Understanding Unix concepts related to processes and signals
- discussing expansion behavior
- reviewing design choices and identifying possible edge cases
- suggesting manual tests and debugging strategies
- drafting project documentation

AI-generated explanations and suggestions were reviewed, discussed, and tested by the team. The authors remain responsible for understanding, creating and validating the final implementation.

---

## Authors

- `leilai`
- `vabisco`
