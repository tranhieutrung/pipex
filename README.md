# Pipex Project

## Overview
The Pipex project is a program that mimics the behavior of the shell command:
    <infile cmd1 | cmd2 >outfile

The goal is to implement this functionality in C, leveraging pipes and process management to execute commands in sequence and redirect input/output streams.

### Command Execution:

The program takes the following format: ./pipex infile cmd1 cmd2 outfile.
It performs the equivalent of the shell command: <infile cmd1 | cmd2 >outfile.

## Project Structure and Approach
### Concept
#### Pipes: 
A pipe is created to facilitate communication between two commands.
The pipe() system call creates a pair of file descriptors: pipe_id[0] for reading and pipe_id[1] for writing.
The output of cmd1 is written to pipe_id[1], and cmd2 reads this output from pipe_id[0].

#### Fork and Execve:
fork() is used to create child processes.
execve() executes the commands. If successful, execve() does not return to the calling program.
Each command (cmd1, cmd2) requires a separate child process to execute concurrently.

#### Environment Variables:
Extract the PATH variable from envp to locate the executable files for the commands.
Use this path information to construct the full path for execve().



## Result
Actual Status : finished.

https://github.com/tranhieutrung/images/blob/06caf65ec6c95c3abaca19caa980069a3a4b0a39/pipex_result.png

## Contribution
If you'd like to contribute to the project, please create a pull request on GitHub. Please adhere to the contribution guidelines outlined in the CONTRIBUTING.md file.

## License
This project is distributed under the MIT License.