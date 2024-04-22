
# Minishell

## Description
Minishell is a simple Unix shell implementation developed as part of the 42 curriculum. The project aims to provide a lightweight and minimalistic command-line interface similar to traditional Unix shells like Bash or Zsh. Minishell runs executables from an absolute, relative, or environment PATH, including arguments or options. It supports various shell features such as environment variables, command separation with semicolons, input/output redirections, and piping. Additionally, Minishell handles signal management, allowing users to interrupt processes using Ctrl-C, quit programs using Ctrl-\, and throw an EOF using Ctrl-D, similar to Bash.

<img width="1448" alt="Screen Shot 2024-04-22 at 7 36 05 PM" src="https://github.com/wzakkabi/minishell/assets/114888333/ab7b3353-7ec5-4511-95ef-480dd2eb096b">

## Features
- **Command Execution:** Minishell runs executables from an absolute, relative, or environment PATH, including arguments or options. Both single and double quotes work the same as Bash, except for multiline commands.
- **Command Separation:** Commands can be separated by semicolons (`;`), allowing users to execute multiple commands on a single line.
- **Redirections:** Minishell supports input/output redirections (`>`, `>>`, `<`), allowing users to redirect the standard input and output streams of commands.
- **Piping:** Minishell supports piping (`|`), enabling users to chain commands together, with the output of one command serving as the input to another command.
- **Environment Variables:** Minishell handles environment variables, including standard variables like `$HOME`, as well as special variables like `$?` (return code).
- **Signal Handling:** Minishell handles interrupt signals (Ctrl-C), quit signals (Ctrl-\), and EOF signals (Ctrl-D), allowing users to control processes and terminate programs as needed.
- **Built-in Commands:** Minishell includes built-in commands such as `echo`, `pwd`, `cd`, `env`, `export`, `unset`, and `exit`, which are implemented directly within the shell for improved performance and functionality.

## Getting Started
To use Minishell, follow these steps:

## install
Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install libreadline-dev
```
macOS (Homebrew):
```shell
brew install readline
```

1. Clone the repository to your local machine:
```shell
git clone https://github.com/wzakkabi/minishell.git
```
2. Compile the source files:
```shell
make
```

3. Run the executable:
```shell
./minishell
```

## Usage
Here are some example commands you can run in Minishell:

- Execute a command:
```shell
ls -l | wc
```
- Change directory:
cd /path/to/directory

- Set environment variables:
```shell
export MY_VAR=value
```
print variable
```shell
echo $MY_VAR
```
- Redirect input/output:
```shell
cat Makefile > test
```
```shell
cat test
```
### credits
This two-person project was done with [walid zakkabi](https://github.com/wzakkabi) and [Mouad Bousbaa](https://github.com/mou4d)

-using [Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) node for parsing

## Contact
If you have any questions, suggestions, or issues regarding Minishell, feel free to contact us by opening an issue on the GitHub repository.
