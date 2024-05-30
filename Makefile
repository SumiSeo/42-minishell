NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c handler/error_controler.c\
a_current_directory.c\
b_store_input.c\
c_parsing.c\
c_utils.c\
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
store_env/store_env.c

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