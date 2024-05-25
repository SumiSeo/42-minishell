/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 13:05:08 by ftanon           ###   ########.fr       */
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

typedef struct t_list
{
	char			*str;
	int				num;
	int				index;
	struct t_list	*next;
	struct t_list	*prev;
}	t_list;

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

void	create_list(char const *str, char c, t_list **lexer);
int		check_input(char const *str);

size_t	ft_strlen(const char *string);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif