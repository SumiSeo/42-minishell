/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 20:30:09 by sumseo           ###   ########.fr       */
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

// execution
void		runtime_shell(char **simple_cmds, char **pipe_cmds);
void		exec_shell(char **simple_cmds, char *path, char **env);
void		parse_path(char *first_cmd, char *path, char **env);
char		**parse_cmd(char *cmd);
void		free_cmd_and_path(char *joined_cmd, char *joined_path);
void		free_array(char **line);
void		execute_cmd(char **cmds, char **arr, char **env);
int			is_builtin(char **cmds);
void		execute_builtin(char **cmds);
int			is_echo(char *str);
int			is_pwd(char *str);
int			is_cd(char *str);
int			is_env(char *str);
int			is_exit(char *str);
int			is_export(char *str);
int			is_unset(char *str);
void		func_echo(char **cmds);
#endif