/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/30 19:32:26 by sumseo           ###   ########.fr       */
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
	int				pipefd[2];
	int				total_pipe;
	char			**cmd;
	char			*path;
	int				fdi;
	int				fdo;
	int				i;
	int				prev;
	char			*limiter;

}					t_pipe;

typedef struct t_lexer
{
	char			*str;
	int				num;
	int				index;
	struct t_lexer	*next;
	struct t_lexer	*prev;
}					t_lexer;

typedef struct t_parser
{
	char			**str;
	char			*infile;
	char			*outfile;
	char			*token_infile;
	char			*token_outfile;
	int				index;
	int				fd_infile;
	int				fd_outfile;
	char			*path;
	char			*builtin;
	int				num_redirections;
	struct t_parser	*next;
	struct t_parser	*prev;
}					t_parser;

typedef struct s_envp
{
	char			*str;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

// error handler
void				exit_program(char *s);
void				create_prompt(char **env);

// minishell
int					take_input(char *str);
void				print_dir(void);
int					process_string(char *str, char **parsed, char **parsedpipe);
void				exec_args(char **parsed);
void				exec_args_piped(char **parsed, char **parsedpipe);
int					own_cmd_handler(char **parsed);
int					count_arr_length(char **argv);
void				create_pipe(char *cmd, char **env, int total, int i);
void				execute_pipeline(char **parsed_args, char *path,
						char **env);
void				execute_cmds(char **parsed_args, char **env);
void				create_first_pipe(char *cmd, char **env);
void				create_last_pipe(char *cmd, char **env);

// execution
void				runtime_shell(t_parser *cmds_list);
void				exec_shell(t_parser *cmds_list, t_envp *env);
void				parse_path(char *first_cmd, t_envp *env);
char				**parse_cmd(char *cmd);
void				free_cmd_and_path(char *joined_cmd, char *joined_path);
void				free_array(char **line);
void				execute_cmd(char **cmds, char **arr);
int					is_builtin(t_parser *cmds);
void				execute_builtin(char **cmds);
int					is_echo(char *str);
int					is_pwd(char *str);
int					is_cd(char *str);
int					is_env(char *str);
int					is_exit(char *str);
int					is_export(char *str);
int					is_unset(char *str);
void				func_echo(t_parser *cmds);
void				func_pwd(t_parser *cmds);
void				func_cd(t_parser *cmds);
void				func_relative_cd(int path_int);
void				func_exit(t_parser *cmds);
void				create_list(char const *str, t_lexer **lexer);
int					check_input(char const *str);
void				store_env(char **envp, t_envp **env);

// void	parsing(t_lexer *lexer, t_parser **parser);
// void	parsing(t_lexer *lexer);

size_t				ft_strlen(const char *string);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

#endif