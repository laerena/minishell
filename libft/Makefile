# --- Variables ---
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(HEADERS_DIR)

# Archiver and flags
AR = ar
ARFLAGS = rcs

# Project name
NAME = libft.a

# Headers dir
HEADERS_DIR = include

# Functions
FCN = \
	src/char/ft_isalnum.c \
	src/char/ft_isalpha.c \
	src/char/ft_isascii.c \
	src/char/ft_isdigit.c \
	src/char/ft_isprint.c \
	src/char/ft_isspace.c \
	src/char/ft_tolower.c \
	src/char/ft_toupper.c \
	src/conv/ft_atoi.c \
	src/conv/ft_itoa.c \
	src/conv/ft_atoll.c \
	src/conv/ft_itoa_base.c \
	src/conv/ft_llitoa.c \
	src/conv/ft_llitoa_base.c \
	src/conv/ft_llutoa.c \
	src/conv/ft_llutoa_base.c \
	src/conv/ft_utoa.c \
	src/conv/ft_utoa_base.c \
	src/conv/ft_isvalid_base.c \
	src/conv/ft_ptr_index.c \
	src/lst/ft_lstadd_back.c \
	src/lst/ft_lstadd_front.c \
	src/lst/ft_lstclear.c \
	src/lst/ft_lstdelone.c \
	src/lst/ft_lstiter.c \
	src/lst/ft_lstlast.c \
	src/lst/ft_lstmap.c \
	src/lst/ft_lstnew.c \
	src/lst/ft_lstsize.c \
	src/mem/ft_bzero.c \
	src/mem/ft_calloc.c \
	src/mem/ft_memchr.c \
	src/mem/ft_memcmp.c \
	src/mem/ft_memcpy.c \
	src/mem/ft_memmove.c \
	src/mem/ft_memset.c \
	src/mem/ft_realloc.c \
	src/put/ft_putchar_fd.c \
	src/put/ft_putendl_fd.c \
	src/put/ft_putnbr_fd.c \
	src/put/ft_putstr_fd.c \
	src/str/ft_split.c \
	src/str/ft_split2.c \
	src/str/ft_strchr.c \
	src/str/ft_strdup.c \
	src/str/ft_striteri.c \
	src/str/ft_strjoin.c \
	src/str/ft_strjoin2.c \
	src/str/ft_strlcat.c \
	src/str/ft_strlcpy.c \
	src/str/ft_strlen.c \
	src/str/ft_strmapi.c \
	src/str/ft_strncmp.c \
	src/str/ft_strnstr.c \
	src/str/ft_strrchr.c \
	src/str/ft_strtrim.c \
	src/str/ft_substr.c \
	src/str/ft_strclen.c \
	src/str/ft_strnjoin.c \
	src/str/ft_strset.c \
	src/str/ft_strswapchar.c \
	src/str/ft_strcmp.c \
	src/arr/ft_arrlen.c \
	src/arr/ft_strarr_free.c \
	src/gnl/get_next_line.c \
	src/ft_printf/ft_printf.c \
	src/ft_printf/ft_printf_fd.c \
	src/ft_printf/ft_printf_buf_static.c \
	src/ft_printf/ft_printf_buf_dyn.c \
	src/ft_printf/ft_printf_core.c \
	src/ft_printf/ft_printf_parse_format.c \
	src/ft_printf/ft_printf_convert.c \
	src/ft_printf/ft_printf_output.c \
	src/ft_printf/ft_printf_utils.c \
	src/ft_printf/specifier/specifier_str.c \
	src/ft_printf/specifier/specifier_char.c \
	src/ft_printf/specifier/specifier_int.c \
	src/ft_printf/specifier/specifier_hex.c \
	src/ft_printf/specifier/specifier_ptr.c \
	src/ft_printf/specifier/specifier_uint.c \
	src/ft_printf/specifier/specifier_perc.c \
	src/ft_printf/format/format_precision.c \
	src/ft_printf/format/format_prefix.c \
	src/ft_printf/format/format_pads.c \
	src/ft_printf/format/format_assembler.c

# Object files
OBJS = $(FCN:.c=.o)

# --- Default Rule ---
# Builds library (main)
all: $(NAME)

# --- Main Rule ---
# Build static library from object files
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# --- Pattern Rule ---
# Compile function files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Clean Rules ---
# rm object files (main + bonus)
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

# rm all generated files
fclean: clean
	rm -f $(NAME)

# Rebuil project from 0
re: fclean all

# --- Phony targets ---
# Declare virtual targets
.PHONY: all bonus clean fclean re
