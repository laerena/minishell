NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -Iinclude -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LDFLAGS =

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
READLINE_DIR := $(shell brew --prefix readline)
INCLUDE += -I$(READLINE_DIR)/include
LDFLAGS += -L$(READLINE_DIR)/lib
endif

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
		src/utils/find_var_in_envp.c \
		src/utils/wrapper_cmd_ext.c \
		src/expander/expand_argv.c \
		src/expander/expand_env.c \
		src/expander/expand_append.c \
		src/expander/expand_heredoc.c \
		src/expander/expand_utils.c \
		src/executor/executor.c\
		src/executor/heredoc.c\
		src/executor/heredoc_create.c \
		src/executor/run_control_flow.c\
		src/executor/run_pipe.c \
		src/executor/run_redir.c \
		src/executor/run_redir_helper.c \
		src/executor/helper.c\
		src/executor/run_execve.c\
		src/executor/run_builtins.c \
		src/wildcards/wildcards.c \
		src/builtins/builtin_cd.c \
		src/builtins/builtin_echo.c \
		src/builtins/builtin_env.c \
		src/builtins/builtin_exit.c \
		src/builtins/builtin_export.c \
		src/builtins/builtin_export_p.c \
		src/builtins/builtin_pwd.c \
		src/builtins/builtin_unset.c \
		src/init/init.c \
		src/init/update_SHLVL.c \
		src/signals/signals.c \
		src/signals/signals_modes.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Debug build:
# Adds debug symbols and disables optimizations for easier debugging with gdb.
# Usage: make debug
debug: CFLAGS += -O0 -DDEBUG
debug: re

# Sanitizer build:
# Enables AddressSanitizer and UndefinedBehaviorSanitizer to detect memory errors,
# invalid accesses, use-after-free, and undefined behavior during execution.
# Usage: make sanitize
sanitize: CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined -O0
sanitize: LDFLAGS := -Wall -Wextra -Werror -g -fsanitize=address,undefined
sanitize: re


# Valgrind:
# Runs the program with Valgrind to check memory leaks and file descriptor leaks.
# Useful for detecting forgotten frees, open pipes, or heredoc file descriptors.
# Usage: make valgrind
VALGRIND_SUPP = readline.supp

valgrind: all
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--suppressions=$(VALGRIND_SUPP) \
		./$(NAME)

valgrind-fd: all
	valgrind \
		--track-fds=yes \
		./$(NAME)

.PHONY: all clean fclean re debug sanitize valgrind valgrind-fd
