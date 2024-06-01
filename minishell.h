/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 17:20:19 by ftanon           ###   ########.fr       */
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

/////////////////////////////////////////////////////////////////////////

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

typedef struct s_token
{
	char			*str;
	int				num;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*env_var;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char			**all_paths;
	int				has_pipe;	
	char			*input_string;
}	t_data;

typedef struct s_parse
{
	int				index;
	char			*infile_name;
	char			*infile_token;
	int				infile_exist;
	int				infile_access;
	char			**cmd_array;
	char			*outfile_name;
	char			*outfile_token;
	int				outfile_exist;
	int				outfile_access;
	char			*path;
	int				builtin;
	int				num_redirections;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

/////////////////////////////////////////////////////////////////////////

// error handler
void		exit_program(char *s);
void		create_prompt(char **env);

// minishell
int			take_input(t_data *data);
void		print_dir(void);
int			process_string(char *str, char **parsed, char **parsedpipe);
void		exec_args(char **parsed);
void		exec_args_piped(char **parsed, char **parsedpipe);
int			own_cmd_handler(char **parsed);
int			count_arr_length(char **argv);
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
void		func_pwd(char **cmds);
void		func_cd(char **cmds);
void		func_relative_cd(int path_int);

// 1. lexical analysis
int			check_input(char const *str);
void		create_token_list(char const *str, t_token **tok_list);
void		free_token_list(t_token	**tok_list);
void		display_token_list(t_token *tok_list);

// 2. parsing
void		create_parse_list(t_token *tok_list, t_parse **par_list);
void		free_parse_list(t_parse	**par_list);
void		display_parse_list(t_parse *par_list);
void		store_command(t_token *tok_list, t_parse *par_list);
void		check_outfile(t_parse *par_list);
void		check_infile(t_parse *par_list);
void		search_command(t_parse *par_list, t_data *data);

void		count_nb_pipe(t_token *tok_list, t_data *data);

// 3. store env
void		store_env_list(char **envp, t_env **env_list);
void		display_env_list(t_env *env_list);
void		store_path(t_env *env_list, t_data *data);
void		display_path(t_data *data);

// display
void		display_array(char **array);

// gnl
char		*get_next_line(int fd);

#endif