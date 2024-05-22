# Suminishell(42 Minishell project)
This project is first group project in 42 cursus(paris, France) to create bash based shell. Minishell is strongly connected with pipex project. So we highly recommend to do pipex mandatory part and even bonus.

## Overview

* What is bash ? 
[Bash manual page](https://www.gnu.org/software/bash/manual/bash.html)
* It should imitate eligible bash commands
* Unlikely pipex, minishell should control not only multiple commands but also shell-like behaviour such as creatnig env variables, ctrl-C, butilins, etc
* Interactive mode and uninteractive mode

## Plans
Lexing -> Parsing -> Executing -> Error handling

## To do list
- [x] Display a prompt 
- [x] Have a working history
- [ ] Search and launch the right executable(based on the PATH variable or using a relative or an absolute path)
- [ ] Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ;(semicolon)
- [ ] Handle '(single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence
- [ ] Handle "(double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)
- [ ] Implement redirections
    1. \> should redirect input
    2. \< should redirect output
    3. \>> should be give a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history !
    4. \>> should redirect ouput in append mode
- [ ] Implement pieps (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe
- [ ] Handle environment variables ($ followed by a sequence of characters) which should expand to their values
- [ ] Handle $? which should expand to the exit status of the most recently executed foreground pipeline
- [ ] Handle ctrl-C, ctrl-D, ctrl-\ which should behave like in bash
- [ ] In interactive mode 
    1. ctrl-C dislays a new prompts on a new line
    2. ctrl-D exits the shell
    3. ctrl-\ does nothing
- [ ] Your shell mush implement the following builtins
    1. echo with option -n
    2. cd with only a relative or absolute path
    3. pwd with no options
    4. export with no options
    5. unset with no options
    6. unset with no options
    7. env with no options or arguments
    8. exit with no options

