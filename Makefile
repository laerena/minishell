NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -Iinclude -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_operator.c \
		src/lexer/token_list.c \
		src/parser/syntax_check.c\
		src/parser/parse.c \
		src/parser/parser_imple.c \
		src/parser/parser_utils.c \
		src/parser/parser_utils_redir.c\
		src/parser/cmd_new.c \
		src/parser/cmd_free.c \
		src/utils/free_split.c\
		src/utils/error.c \
		src/expander/expand_ast.c \
		src/expander/expand_str.c \
		src/expander/expand_env.c \
		src/expander/expand_append.c \
		src/executor/executor.c\
		src/executor/op_io.c\
		src/executor/op_control_flow.c\
		src/executor/helper.c\
		src/executor/run_exec.c\
		src/executor/run_builtins.c \
		src/wildcards/wildcards.c \
		src/builtins/builtin_cd.c \
		src/builtins/builtin_echo.c \
		src/builtins/builtin_env.c \
		src/builtins/builtin_exit.c \
		src/builtins/builtin_export.c \
		src/builtins/builtin_pwd.c \
		src/builtins/builtin_unset.c \
		src/signals.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re