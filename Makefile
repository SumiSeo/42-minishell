NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c handler/error_controler.c\
a_current_directory.c\
b_store_input.c\
c_parsing.c\
d_execution_builtin.c\
e_execution_system.c\
execution/pipe_init.c\
execution/pipe_utils.c\
execution/runtime.c\
execution/exec_utils.c\
builtin/echo.c\
builtin/pwd.c\
builtin/cd.c\
builtin/exit.c\
builtin/export.c\
builtin/unset.c\
builtin/env.c\
builtin/find_builtin.c\
lexical_analysis/check_input.c\
lexical_analysis/create_token_list.c\
lexical_analysis/count_nb_pipe.c\
lexical_analysis/free_token_list.c\
parsing/create_parse_list.c\
parsing/check_infile.c\
parsing/check_outfile.c\
parsing/free_parse_list.c\
parsing/search_command.c\
parsing/store_command.c\
store_env/store_env_list.c\
store_env/store_path.c\
utils_display/display.c\
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\


INCLUDES = libft/
OBJDIR = obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

#FLAGS 
CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
CLIB = -L libft/ -l libft
DEBUGGER = -g3

all : $(NAME)

$(NAME) : $(OBJS)
		make -C libft
		$(CC) $(OBJS) -I $(INCLUDES) -o $(NAME) $(CLIB) $(LDFLAGS) $(DEBUGGER)

$(OBJDIR)/%.o : %.c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		rm -rf $(OBJDIR)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re