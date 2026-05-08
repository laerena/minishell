/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:07:34 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/21 13:49:58 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_specifier(const char c)
{
	if (c == 'c'
		|| c == 's'
		|| c == 'p'
		|| c == 'd'
		|| c == 'i'
		|| c == 'u'
		|| c == 'x'
		|| c == 'X'
		|| c == '%')
		return (1);
	return (0);
}

static int	parse_flag(const char c, t_printf_context *ctx)
{
	if (c == '-')
		ctx->left_justify = 1;
	else if (c == '+' || c == ' ')
	{
		if (c == '+' && ctx->sign != '-')
			ctx->sign = '+';
		else if (c == ' ' && !ctx->sign)
			ctx->sign = ' ';
	}
	else if (c == '#')
		ctx->alt_form = 1;
	else if (c == '0')
		ctx->zero = 1;
	else
		return (-1);
	return (0);
}

static void	parse_length(const char **format, t_printf_context *ctx)
{
	if (**format && **format == 'l')
	{
		(*format)++;
		if (**format && **format == 'l')
		{
			ctx->length = LEN_LL;
			(*format)++;
		}
		else
			ctx->length = LEN_L;
	}
	else if (**format && **format == 'z')
	{
		ctx->length = LEN_Z;
		(*format)++;
	}
	else
		ctx->length = LEN_NONE;
}

static int	parse_format_components(const char **format, t_printf_context *ctx)
{
	while (**format && !parse_flag(**format, ctx))
		(*format)++;
	while (**format && ft_isdigit(**format))
	{
		ctx->width = (ctx->width * 10) + (**format - '0');
		(*format)++;
	}
	if (**format == '.')
	{
		ctx->precision = 0;
		(*format)++;
	}
	while (**format && ft_isdigit(**format))
	{
		ctx->precision = (ctx->precision * 10) + (**format - '0');
		(*format)++;
	}
	parse_length(format, ctx);
	if (!is_specifier(**format))
		return (-1);
	ctx->speci = **format;
	return (0);
}

//format order %[flags][width][.precision]([length])specifier
int	ft_printf_parse_format(const char **format, t_printf_context *ctx)
{
	if (!*(*format + 1))
		return (-1);
	(*format)++;
	if (parse_format_components(format, ctx))
		return (-1);
	return (0);
}

//old ft
// static int	parse_format_components(const char **format,
//					t_printf_context *ctx)
// {
// 	while (**format && !parse_flag(**format, ctx))
// 		(*format)++;
// 	while (**format && ft_isdigit(**format))
// 	{
// 		ctx->width = (ctx->width * 10) + (**format - '0');
// 		(*format)++;
// 	}
// 	if (**format == '.')
// 	{
// 		ctx->precision = 0;
// 		(*format)++;
// 	}
// 	while (**format && ft_isdigit(**format))
// 	{
// 		ctx->precision = (ctx->precision * 10) + (**format - '0');
// 		(*format)++;
// 	}
// 	parse_length(format, ctx);
// 	if (!is_specifier(**format))
// 		return (-1);
// 	ctx->speci = **format;
// 	return (0);
// }

// //format order %[flags][width][.precision]([length])specifier
// int	ft_printf_parse_format(const char **format, t_printf_context *ctx)
// {
// 	if (!*(*format + 1))
// 		return (-1);
// 	(*format)++;
// 	if (parse_format_components(format, ctx))
// 		return (-1);
// 	return (0);
// }
