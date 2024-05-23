/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/23 13:32:24 by ftanon           ###   ########.fr       */
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

// error handler
void	exit_program(char *s);
void	create_prompt(char **env);

int		take_input(char *str);
void	print_dir(void);
int		process_string(char	*str, char	**parsed, char	**parsedpipe);
void	exec_args(char **parsed);
void	exec_args_piped(char **parsed, char **parsedpipe);
int		own_cmd_handler(char **parsed);

char	**ft_split(char const *s, char c);

#endif