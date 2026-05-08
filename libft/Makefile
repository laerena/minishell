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
	char/ft_isalnum.c \
	char/ft_isalpha.c \
	char/ft_isascii.c \
	char/ft_isdigit.c \
	char/ft_isprint.c \
	char/ft_tolower.c \
	char/ft_toupper.c \
	conv/ft_atoi.c \
	conv/ft_itoa.c \
	lst/ft_lstadd_back.c \
	lst/ft_lstadd_front.c \
	lst/ft_lstclear.c \
	lst/ft_lstdelone.c \
	lst/ft_lstiter.c \
	lst/ft_lstlast.c \
	lst/ft_lstmap.c \
	lst/ft_lstnew.c \
	lst/ft_lstsize.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	mem/ft_memset.c \
	put/ft_putchar_fd.c \
	put/ft_putendl_fd.c \
	put/ft_putnbr_fd.c \
	put/ft_putstr_fd.c \
	str/ft_split.c \
	str/ft_strchr.c \
	str/ft_strdup.c \
	str/ft_striteri.c \
	str/ft_strjoin.c \
	str/ft_strlcat.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c \
	str/ft_strmapi.c \
	str/ft_strncmp.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strtrim.c \
	str/ft_substr.c \
	added/ft_atoll.c \
	added/ft_isspace.c \
	added/ft_isvalid_base.c \
	added/ft_itoa_base.c \
	added/ft_llitoa.c \
	added/ft_llitoa_base.c \
	added/ft_llutoa.c \
	added/ft_llutoa_base.c \
	added/ft_split2.c \
	added/ft_strclen.c \
	added/ft_strjoin2.c \
	added/ft_strnjoin.c \
	added/ft_strset.c \
	added/ft_strswapchar.c \
	added/ft_utoa.c \
	added/ft_utoa_base.c \
	gnl/get_next_line.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_printf_parse_format.c \
	ft_printf/ft_printf_convert_and_print.c \
	ft_printf/ft_printf_utils.c \
	ft_printf/specifier/specifier_str.c \
	ft_printf/specifier/specifier_char.c \
	ft_printf/specifier/specifier_int.c \
	ft_printf/specifier/specifier_hex.c \
	ft_printf/specifier/specifier_ptr.c \
	ft_printf/specifier/specifier_uint.c \
	ft_printf/specifier/specifier_perc.c \
	ft_printf/format/format_precision.c \
	ft_printf/format/format_prefix.c \
	ft_printf/format/format_pads.c \
	ft_printf/format/format_assembler.c

# Object files
OBJS = $(FCN:.c=.o)
OBJS_BONUS = $(FCN_BONUS:.c=.o)

# --- Default Rule ---
# Builds library (main)
all: $(NAME)

# --- Main Rule ---
# Build static library from object files
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# --- Bonus Rule ---
# Build static library from object files(main + bonus)
bonus: $(NAME) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $^

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
