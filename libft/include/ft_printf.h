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

//	struct
typedef struct s_printf_context
{
	//flags
	unsigned int	left_justify;
	unsigned int	alt_form;
	char			sign;
	int				precision;
	unsigned int	zero;
	int				width;
	char			speci;
	t_length		length;
	//format parts :
	//	(%i, %d, %u, %x, %X):	[pad(' ')][prefix(sign/alt)][pad('0')][digits]
	//							[prefix(sign/alt)][pad('0')][digits][pad(' ')]
	char			*arg;
	char			*prefix;
	char			*pad_0;
	char			*pad_width;
	char			*buffer;

	size_t			arg_len;
	size_t			prefix_len;
	size_t			pad_0_len;
	size_t			pad_w_len;
	size_t			buffer_len;
}	t_printf_context;

//ft
int		ft_printf(const char *format, ...);
int		ft_printf_parse_format(const char **format, t_printf_context *ctx);
int		ft_printf_convert_and_print(t_printf_context *ctx, va_list args,
			int *printed_char);
//utils
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

#endif
