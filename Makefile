NAME = mini

CC = cc
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
        tools/tool_1.c \
        tools/tool_2.c \
		Get_Next_Line/get_next_line_utils.c \
		Get_Next_Line/get_next_line.c \
        # parsing/expand/tools_2.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -g3 -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror

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
