/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 16:35:15 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

# define MAXCOM 1000 // max number of letters to be supported
# define MAXLIST 100 // max number of commands to be supported

// struct
typedef struct s_pipe
{
	int		pipefd[2];
	int		total_pipe;
	char	**cmd;
	char	*path;
	int		fdi;
	int		fdo;
	int		i;
	int		prev;
	char	*limiter;

}			t_pipe;

// error handler
void		exit_program(char *s);
void		create_prompt(char **env);

// minishell
int			take_input(char *str);
void		print_dir(void);
int			process_string(char *str, char **parsed, char **parsedpipe);
void		exec_args(char **parsed);
void		exec_args_piped(char **parsed, char **parsedpipe);
int			own_cmd_handler(char **parsed);
int			count_pipeline(char **argv);
void		create_pipe(char *cmd, char **env, int total, int i);
void		execute_pipeline(char **parsed_args, char *path, char **env);
void		execute_cmds(char **parsed_args, char **env);
void		create_first_pipe(char *cmd, char **env);
void		create_last_pipe(char *cmd, char **env);
void		runtime_shell(char **simple_cmds, char **pipe_cmds);
void		exec_shell(char **simple_cmds);

#endif