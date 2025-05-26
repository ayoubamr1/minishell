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
        execution/exec.c \
        execution/builtins.c \
        execution/redirection.c \
        execution/execution.c \
        execution/utils_execution.c \
        builtins/add_env.c \
        builtins/cd.c \
        builtins/echo.c \
        builtins/export.c \
        builtins/my_getenv.c \
        builtins/my_unset.c \
        builtins/update_env.c \
        builtins/my_pwd.c \
        builtins/my_env.c \
		parsing/cmd/heredoc.c \
		Get_Next_Line/get_next_line_utils.c \
		Get_Next_Line/get_next_line.c

OBJ = $(SRC:.c=.o)

# CFLAGS = -g3 -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS =  #-g3 -fsanitize=address #-Wall -Wextra -Werror

all: $(NAME) #clean  #########################

%.o: %.c minishell.h gbc.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
