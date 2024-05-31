/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/31 17:19:06 by ftanon           ###   ########.fr       */
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

typedef struct s_lexer
{
	char			*str;
	int				num;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_envp
{
	char			*str;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_env
{
	char			**str;
}	t_env;

typedef struct s_parser
{
	char			**str;
	char			*infile;
	char			*outfile;
	char			*token_infile;
	char			*token_outfile;
	int				infile_exist;
	int				outfile_exist;
	int				has_here_doc;
	int				infile_access;
	int				outfile_access;
	int				index;
	char			*path;
	char			*builtin;
	int				num_redirections;
	char			**paths_array;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

// typedef struct s_lexer
// {
// 	int				position;
// }	t_lexer;

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

// lexical analysis

int		check_input(char const *str);
void	create_tokenized_list(char const *str, t_lexer **lexer);
void	free_tokenised_list(t_lexer	**stack_a);

// parsing
void	create_parsed_list(t_lexer *lexer, t_parser **parser);
void	free_parsed_list(t_parser	**stack_a);
void	display_parser(t_parser *begin);
void	store_command(t_lexer *lexer, t_parser *parser);
void	check_outfile(t_parser *parser);
void	check_infile(t_parser *parser);
void	search_command(t_parser *parser, t_env *path);
void	store_path(t_envp *env, t_env *path);

// store env
void	store_env(char **envp, t_envp **env);

// display

void	display_str(char **array);
void	display_lexer(t_lexer *begin);
void	display_array(char **array);
void	display_env(t_envp *begin);

// gnl
char	*get_next_line(int fd);

#endif