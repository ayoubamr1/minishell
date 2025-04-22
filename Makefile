NAME = mini

CC = cc

SRC = parsing/token/mini.c parsing/token/tools.c tools/ft_malloc.c parsing/token/syntax_error.c parsing/token/token.c tools/tool_1.c #parsing/ft_malloc.c  tools/tool_1.c  builtins/cd.c  

OBJ		= $(SRC:.c=.o)

CFLAGS = #-g3 -fsanitize=address #`-Wall -Wextra -Werror #  


all : $(NAME)

%.o : %.c minishell.h gbc.h
		$(CC) $(CFLAGS) -c $< -o $@


$(NAME) : $(OBJ)
		$(CC) $(CFLAGS)  $(OBJ) -lreadline -o $(NAME) 


clean: 
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME) 

re: fclean all