NAME = mini

CC = cc #-g3 -fsanitize=address
RM = rm -f

SRC =   parsing/token/main.c \
        parsing/token/tools.c \
        parsing/token/syntax_error.c \
        parsing/token/token.c \
        parsing/token/env.c \
        parsing/cmd/cmd.c \
        parsing/cmd/tools_1.c \
        parsing/expand/expand.c \
        parsing/expand/tools_1.c \
        tools/ft_malloc.c \
        tools/tools_1.c \
        tools/tools_2.c \
        tools/tools_3.c \
        execution/check_path_cmd.c \
        execution/execution.c \
        # parsing/expand/tools_2.c \

OBJ = $(SRC:.c=.o)

CFLAGS = #-Wall -Wextra -Werror #-g3 -fsanitize=address

all: $(NAME)

%.o: %.c minishell.h gbc.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
