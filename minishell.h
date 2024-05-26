/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 12:11:40 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include<string.h> 
# include<sys/types.h> 
# include<sys/wait.h> 

# define MAXCOM 1000 // max number of letters to be supported 
# define MAXLIST 100 // max number of commands to be supported 

typedef struct t_lexer
{
	char			*str;
	int				num;
	int				index;
	struct t_lexer	*next;
	struct t_lexer	*prev;
}	t_lexer;

typedef struct t_parser
{
	char			**str;
	char			*infile;
	char			*outfile;
	struct t_parser	*next;
	struct t_parser	*prev;
}	t_parser;

// typedef struct s_lexer
// {
// 	int				position;
// }	t_lexer;

// error handler
void	exit_program(char *s);
void	create_prompt(char **env);

int		take_input(char *str);
void	print_dir(void);
int		process_string(char	*str, char	**parsed, char	**parsedpipe);
void	exec_args(char **parsed);
void	exec_args_piped(char **parsed, char **parsedpipe);
int		own_cmd_handler(char **parsed);

void	create_list(char const *str, t_lexer **lexer);
int		check_input(char const *str);
// void	parsing(t_lexer *lexer, t_parser **parser);
// void	parsing(t_lexer *lexer);


size_t	ft_strlen(const char *string);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif