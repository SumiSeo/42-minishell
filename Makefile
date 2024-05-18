NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c errors/error_controler.c
OBJS = $(SRCS:%.c=%.o)

#FLAGS 
CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
DEBUGGER = -g3

all : $(NAME)
%.o : %.CC
		$(CC) $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(DEBUGGER)
clean :
		rm -rf $(OBJS)
fclean : clean
		rm -rf $(NAME)
re : fclean all