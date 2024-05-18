NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c 
OBJS = $(SRCS:%.c=%.o)

#FLAGS 
CC = clang
CFLAGS = -Wall -Werror -Wextra 
DEBUGGER = -g3

all : $(NAME)
%.o : %.CC
		$(CC) $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(DEBUGGER)
clean :
		rm -rf $(OBJS)
flcean :
		rm -rf $(NAME)
re : fclean all