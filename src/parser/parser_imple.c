/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_imple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:35 by leilai            #+#    #+#             */
/*   Updated: 2026/05/08 15:37:43 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* public parser entry point */
t_cmd	*parse_expression(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_or(tokens, NULL));
}
