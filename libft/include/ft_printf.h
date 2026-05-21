/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:53:31 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/08 11:53:31 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//	include
# include "libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

// macro
typedef enum e_length
{
	LEN_NONE,
	LEN_L,
	LEN_LL,
	LEN_Z
}	t_length;

typedef enum e_printf_output_mode
{
	PRINTF_FD,
	PRINTF_BUFFER
}	t_printf_output_mode;

//	struct
typedef struct s_printf_output
{
	t_printf_output_mode	mode;
	int						fd;
	char					*buffer;
	int						dynamic;
	size_t					size;
	size_t					pos;
}	t_printf_output;

//flags
typedef struct s_printf_format
{
	unsigned int	left_justify;
	unsigned int	alt_form;
	char			sign;
	int				precision;
	unsigned int	zero;
	int				width;
	char			speci;
	t_length		length;
}	t_printf_format;
//format parts :
//	(%i, %d, %u, %x, %X):	[pad(' ')][prefix(sign/alt)][pad('0')][digits]
//							[prefix(sign/alt)][pad('0')][digits][pad(' ')]

typedef struct s_printf_buffers
{
	char		*arg;
	char		*prefix;
	char		*pad_0;
	char		*pad_width;
	char		*buffer;

	size_t		arg_len;
	size_t		prefix_len;
	size_t		pad_0_len;
	size_t		pad_w_len;
	size_t		buffer_len;
}	t_printf_buffers;

typedef struct s_printf_context
{
	t_printf_format		fmt;
	t_printf_buffers	buf;
	//output for all printfs
	int					alloced;
	char				charbuffer[2];
	t_printf_output		output;
}	t_printf_context;
//alloced is here prevent freeing buffer if its on heap,
//	could be more precise by setting alloced == 1 after each malloc.

//ft
int		printf_core(t_printf_context *ctx, const char *format, va_list args);
int		ft_printf_parse_format(t_printf_context *ctx, const char **format);
int		ft_printf_convert(t_printf_context *ctx, va_list args);
int		ft_printf_output(t_printf_context *ctx);
//utils (ft_printf_utils.c)
int		is_int_speci(char speci);
//	/speci
int		specifier_str(t_printf_context *ctx, va_list args);
int		specifier_char(t_printf_context *ctx, va_list args);
int		specifier_int(t_printf_context *ctx, va_list args);
int		specifier_hex(t_printf_context *ctx, va_list args);
int		specifier_ptr(t_printf_context *ctx, va_list args);
int		specifier_uint(t_printf_context *ctx, va_list args);
int		specifier_perc(t_printf_context *ctx);
//	/format
int		format_precision(t_printf_context *ctx);
int		format_prefix(t_printf_context *ctx);
int		format_pads(t_printf_context *ctx);
int		format_assembler(t_printf_context *ctx);
//wrappers
//	ft_printf.c
/**
 * @brief Printf to stdout.
 * 
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_printf(const char *format, ...);

/**
 * @brief Printf to stdout with a va_list.
 * 
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_vprintf(const char *format, va_list ap);

//	ft_printf_fd.c
/**
 * @brief Printf to a file descriptor.
 * 
 * @param fd     The file descriptor.
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_dprintf(int fd, const char *format, ...);

/**
 * @brief Printf to a file descriptor with a va_list.
 * 
 * @param fd     The file descriptor.
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_vdprintf(int fd, const char *format, va_list ap);

/**
 * @brief Printf to stderr.
 * 
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_eprintf(const char *format, ...);

/**
 * @brief Printf to stderr with a va_list.
 * 
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters printed, or a negative value on error.
 */
int		ft_veprintf(const char *format, va_list ap);

//	ft_printf_buf_static.
/**
 * @brief Printf to a buffer (unsafe, no size check).
 * 
 * @param str    The buffer to write to.
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters written, or a negative value on error.
 */
int		ft_sprintf(char *str, const char *format, ...);

/**
 * @brief Printf to a buffer with a va_list (unsafe, no size check).
 * 
 * @param str    The buffer to write to.
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters written, or a negative value on error.
 */
int		ft_vsprintf(char *str, const char *format, va_list ap);

/**
 * @brief Printf to a buffer with size check (safe).
 * 
 * @param str    The buffer to write to.
 * @param size   The size of the buffer.
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters written (excluding null byte),
 * or a negative value on error.
 */
int		ft_snprintf(char *str, size_t size, const char *format, ...);

/**
 * @brief Printf to a buffer with size check and va_list (safe).
 * 
 * @param str    The buffer to write to.
 * @param size   The size of the buffer.
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters written (excluding null byte),
 * or a negative value on error.
 */
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);

//	ft_printf_buf_dyn.c
/**
 * @brief Printf to a dynamically allocated buffer (like asprintf).
 * 
 * @param strp   Pointer to the output string (allocated inside).
 * @param format The format string.
 * @param ...    Variable arguments.
 * @return Number of characters written (excluding null byte), or -1 on error.
 */
int		ft_asprintf(char **strp, const char *format, ...);

/**
 * @brief Printf to a dynamically allocated buffer with va_list (like vasprintf).
 * 
 * @param strp   Pointer to the output string (allocated inside).
 * @param format The format string.
 * @param ap     The va_list of arguments.
 * @return Number of characters written (excluding null byte), or -1 on error.
 */
int		ft_vasprintf(char **strp, const char *format, va_list ap);

#endif
