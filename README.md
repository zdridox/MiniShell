*This project has been created as part of the 42 curriculum by mamelnyk, mzdrodow.*

# Minishell

A small shell. A closer look at how Unix works.

## Description

Minishell is a 42 project about building a simple interactive shell in C. Its goal is to turn command lines into running processes while exploring parsing, environment variables, file descriptors, pipes, and signals.

The project follows the **Minishell subject, version 10.0**, with Bash as the reference when a required behavior is unclear. The scope is deliberately limited to the features specified by the subject.

### Mandatory scope

The following describes the subject's requirements, not a verified implementation checklist. Source code and a Makefile were not available when this README was prepared.

- **Interactive input:** a prompt and working command history.
- **Command execution:** executable lookup through `PATH`, plus relative and absolute paths.
- **Quoting:** single quotes preserve literal text; double quotes preserve literal text while allowing `$` expansion.
- **Expansion:** environment variables and `$?`, the exit status of the most recently executed foreground pipeline.
- **Pipelines:** `|` connects each command's output to the next command's input.
- **Redirections:** `<` for input, `>` for output, `>>` for appended output, and `<<` for a here-document read until its delimiter. Here-document input need not be added to history.
- **Interactive controls:** `Ctrl-C` displays a new prompt on a new line, `Ctrl-D` exits at an empty prompt, and `Ctrl-\` does nothing at the prompt. Signal behavior during command execution follows Bash.

Required built-ins:

| Command | Required scope |
| --- | --- |
| `echo` | Print text, with support for `-n`. |
| `cd` | Change directory using a relative or absolute path. |
| `pwd` | Print the working directory, without options. |
| `export` | Manage exported variables, without options. |
| `unset` | Remove variables, without options. |
| `env` | Display the environment, without options or arguments. |
| `exit` | Exit the shell, without options. |

Unclosed quotes and unrequired special characters, such as backslashes and semicolons, must not be interpreted as additional shell syntax. Logical operators `&&` and `||`, parentheses for precedence, and `*` wildcards in the current directory belong to the bonus scope; this README makes no claim that they are implemented.

The subject also requires compliance with the 42 Norm, proper cleanup of allocated memory, and at most one global variable containing only a received signal number. Readline's own leaks are exempt; leaks in project code are not.

## Instructions

### Prerequisites

Use a Unix-like development environment with:

- A C compiler available as `cc` and the `make` build tool.
- GNU Readline headers and libraries available to the build.
- Standard external commands such as `ls`, `cat`, and `wc` for the examples below.

Dependency locations and any platform-specific linker settings must match the project's Makefile. The build commands below follow the subject's required interface and have not been tested against this repository.

### Build and run

From the repository root:

```sh
make
./minishell
```

The required executable name is `minishell`. The subject requires compilation with `-Wall -Wextra -Werror` and no unnecessary relinking.

| Command | Purpose |
| --- | --- |
| `make` or `make all` | Build the project. |
| `make minishell` | Build the required executable target. |
| `make clean` | Remove compilation intermediates. |
| `make fclean` | Remove compilation intermediates and the executable. |
| `make re` | Rebuild from a clean state. |

### Usage examples

Enter these commands individually inside Minishell. They illustrate mandatory behavior and are not a record of successful tests.

```sh
pwd
echo "Hello from Minishell"
export MESSAGE=hello
echo "$MESSAGE"
echo '$MESSAGE'
ls | wc -l
echo "first line" > minishell-example.txt
echo "second line" >> minishell-example.txt
cat < minishell-example.txt
cat << END
here-document input
END
/bin/false
echo $?
unset MESSAGE
exit
```

The output redirection example creates or overwrites `minishell-example.txt` in the current directory. The two quoting examples illustrate the difference between variable expansion and literal text; `echo $?` immediately after `/bin/false` should print `1`.

### Validation

Compare required behavior with Bash, including quoting, variable expansion, pipelines, redirection order, failed commands, and interactive signal handling. Check the project's C files with Norminette and verify memory and file-descriptor cleanup. These are suggested checks; no build, runtime, leak, or Norm results are asserted here.

## Resources

- **42 Minishell subject, version 10.0** — the assignment's source of truth, especially Chapter IV (mandatory scope), Chapter V (README requirements), and Chapter VI (bonus scope).
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — shell syntax, quoting, expansion, redirections, pipelines, built-ins, and exit status.
- [GNU Readline](https://www.gnu.org/software/readline/) — interactive line editing and history.
- Local manual pages: `man fork`, `man execve`, `man waitpid`, `man pipe`, `man dup2`, and `man sigaction` — process creation, execution, descriptor management, and signal handling.
- [42 Norminette](https://github.com/42School/norminette) — the official code-style checker and its usage documentation.

### AI use

OpenAI's Codex was used to read the supplied subject PDF, extract its README and mandatory-feature requirements, and draft and organize this `README.md`, including its usage examples and resource list. No implementation files were available to Codex for this documentation task, so it did not verify the project's code or run the examples.

**Author confirmation required before submission:** document any other AI use during the project, naming the tasks and affected parts, or confirm that there was none. This disclosure currently covers only the preparation of this README.
