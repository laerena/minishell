NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_operator.c \
		src/lexer/token_list.c \
		src/utils/debug.c\
		src/parser/syntax_check.c\
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/ast_utils.c \
		src/parser/ast_free.c \
		src/utils/debug_ast.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re