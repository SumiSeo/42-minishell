/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/12 16:46:04 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
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

# define READEND 0
# define WRITEEND 1

typedef struct s_pipe
{
	int				pipefd[2];
	int				fdi;
	int				fdo;
	int				i;
	int				tmp_in;
	int				tmp_out;
	int				*pids;
	char			*limiter;
	int				infile;
	int				outfile;
	int				temp;
	int				total_cmds;
}					t_pipe;

typedef struct s_token
{
	char			*word;
	char			*operator;
	int				num;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*env_var;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_data
{
	char			**all_paths;
	int				has_pipe;
	int				position;
	char			*input_string;
}					t_data;

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
}					t_parse;

/////////////////////////////////////////////////////////////////////////

// error handler
void				exit_program(char *s);
void				create_prompt(char **env);

// minishell
int					take_input(t_data *data);
void				print_dir(void);
int					process_string(char *str, char **parsed, char **parsedpipe);
void				exec_args(char **parsed);
void				exec_args_piped(char **parsed, char **parsedpipe);
int					own_cmd_handler(char **parsed);
int					count_arr_length(char **argv);
void				execution(t_parse *cmds_list, char **env_copy,
						t_pipe *pipe_info);
void				execute_pipeline(t_parse *cmds_list, char **env_copy);
void				execute_cmds(char **parsed_args, char **env);
int					count_cmds(t_parse *cmds_list);

// execution
void				runtime_shell(t_parse *cmds_list, char **env_copy,
						t_data *data);
void				exec_shell(t_parse *cmds_list, char **env_copy);

// pipex
void				parse_path(t_parse *cmds, char **env_copy);
char				**parse_cmd(char *cmds);
void				free_cmd_and_path(char *joined_cmd, char *joined_path);
void				free_array(char **line);
void				execute_cmd(t_parse *cmds, char **env_copy);
void				create_list(char const *str, t_token **lexer);
int					check_input(char const *str);

// built-in
int					is_builtin(t_parse *cmds, t_env *env);
void				execute_builtin(char **cmds);
int					is_echo(char *str);
int					is_pwd(char *str);
int					is_cd(char *str);
int					is_env(char *str);
int					is_exit(char *str);
int					is_export(char *str);
int					is_unset(char *str);
void				func_echo(t_parse *cmds);
void				func_pwd(t_parse *cmds);
void				func_cd(t_parse *cmds);
void				func_path(int path_int, char *path);
void				func_relative_cd(int path_int);
void				func_exit(t_parse *cmds);
void				func_env(t_parse *cmds, t_env *env);
void				func_export(t_parse *parser, t_env *env);
void				func_unset(t_parse *parser, t_env *env);
void				func_absolute_cd(char *dir);
int					print_echo(t_parse *cmds, int i, int nextline_flag);

// redirection
void				redirection(t_parse *cmds_list, t_pipe *pipe_info);

//  lexical analysis
int					check_input(char const *str);
void				create_token_list(t_data *data, t_token **tok_list, t_env *env_list);
void				free_token_list(t_token **tok_list);

//  parsing
void				create_parse_list(t_token *tok_list, t_parse **par_list);
void				free_parse_list(t_parse **par_list);
void				display_parse_list(t_parse *par_list);
void				store_command(t_token *tok_list, t_parse *par_list);
void				check_outfile(t_parse *par_list);
void				check_infile(t_parse *par_list);
void				search_command(t_parse *par_list, t_data *data);
void				count_nb_pipe(t_token *tok_list, t_data *data);

//  env
void				store_env_list(char **envp, t_env **env_list);
void				store_path(t_env *env_list, t_data *data);
void				push_env_list(t_env **env_list, const char *str, int len);
void				delete_one_env(t_env **env_list, char *variable);
void				replace_one_env(t_env *env_list, char *env_val,
						char *variable, char *value);

// display
void				display_array(char **array);
void				display_path(t_data *data);
void				display_env_list(t_env *env_list);
void				display_token_list(t_token *tok_list);

// gnl
char				*get_next_line(int fd);

// utils
size_t				ft_strlen(const char *string);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

#endif