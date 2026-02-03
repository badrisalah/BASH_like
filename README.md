🐚 MyShell — A Simple UNIX-like Shell

MyShell is a lightweight, interactive command-line interpreter written in C , it mimics the behavior of a traditional UNIX shell. It supports built-in commands, process creation, I/O redirection, and more.

🚀 Features

Interactive mode — Read and execute user commands.

Non-interactive mode — Execute commands from a file or a pipeline.

Built-in commands:

cd — Change the current working directory.

exit — Exit the shell.

env — Display the environment variables.

Command execution — Executes external programs using fork, execve, and wait.

Path resolution — Searches for executables in the PATH environment variable.

Error handling — Displays appropriate error messages for invalid commands or syntax.

Memory management — Cleans up dynamically allocated memory to avoid leaks.
