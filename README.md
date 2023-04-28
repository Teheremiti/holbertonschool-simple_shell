![Holberton School logo](https://user-images.githubusercontent.com/120781178/229278297-98c6e4b7-f15f-4788-a893-15cb97f10351.png)

# :mortar_board: C - Simple Shell
This is a simple shell implementation that can execute commands from the command line, similar to the standard Unix/Linux shell.

## Installation

1.  Clone the repository from [https://github.com/Teheremiti/holbertonschool-simple_shell.git](https://github.com/Teheremiti/holbertonschool-simple_shell.git)
2.  Compile the program using `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
3.  Run the program using `./hsh`

## Man Page

To display the [man page](https://github.com/Teheremiti/holbertonschool-simple_shell/blob/master/man_1_simple_shell.1), simply run the command `man ./man_1_simple_shell.1`.

## Usage

The shell will not display a prompt when it is ready to accept commands. Simply enter the command you wish to execute and press Enter. The shell will then execute the command and display the output.

### Examples

Here are some examples of how to use the simple shell:

	[$ ./hsh
	[ls
	file1 file2 file3
	[echo  Hello, world!
	Hello, world!
	[cat  file1
	This is the content of file1.

The shell also supports some built-in commands, such as `exit`.

### Built-in Commands

-   `exit`: Exit the shell. Usage: `exit` (note that this built-in does not handle arguments).
-   `env` : Print the current environnment. Usage `env`.

## Files

Here is a brief overview of the files in this repository:

-   `main.h`: Header file containing function prototypes and macros.
-   `func.c`: Helper functions for the main program.
-   `which.c`: Additional functions for the main program.
-   `shell.c`: Main program file.

## Flowchart

![Flowchart drawio](https://user-images.githubusercontent.com/124586557/235101592-57d5f073-7b22-47b9-8a52-41f8afd26f54.png)


## AUTHORS

This shell was created by **Teheremiti Tuiaiho** and **Tristan Duchamp**
