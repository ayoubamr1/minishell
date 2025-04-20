NAME = mini

CC = cc

SRC = token/mini.c token/tools.c token/ft_malloc.c  token/token.c #parsing/ft_malloc.c parsing/syntax_error.c tools/tool_1.c  builtins/cd.c  

OBJ		= $(SRC:.c=.o)

CFLAGS = #-g3 -fsanitize=address #-Wall -Wextra -Werror 


all : $(NAME)

%.o : %.c minishell.h
		$(CC) $(CFLAGS) -c $< -o $@


$(NAME) : $(OBJ)
		$(CC) $(CFLAGS)  $(OBJ) -lreadline -o $(NAME) 


clean: 
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME) 

re: fclean all