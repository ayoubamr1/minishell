NAME = mini

CC = cc

SRC = parsing/token/main.c parsing/token/tools.c tools/ft_malloc.c parsing/token/syntax_error.c parsing/token/token.c  \
	 tools/tool_1.c tools/tool_2.c parsing/token/cmd.c parsing/token/env.c parsing/token/cmd_tool.c #parsing/ft_malloc.c  tools/tool_1.c  builtins/cd.c  

OBJ		= $(SRC:.c=.o)

# CFLAGS = -g3 -fsanitize=address # -Wall -Wextra -Werror #` #  
CFLAGS = -Wall -Wextra -Werror #` #  


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