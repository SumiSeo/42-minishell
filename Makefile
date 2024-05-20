NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c error_controler.c\
a_current_directory.c\
b_store_input.c\
c_parsing.c\
d_execution.c\

OBJDIR = obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

#FLAGS 
CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
DEBUGGER = -g3

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(DEBUGGER)

$(OBJDIR)/%.o : %.c
		mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re