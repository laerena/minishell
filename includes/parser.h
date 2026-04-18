/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:56:07 by leilai            #+#    #+#             */
/*   Updated: 2026/04/18 15:52:26 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_ast	*ast_new_node(t_node_type type); /* initialize */
t_token	*find_last_pipe(t_token *start, t_token *end);
char	**tokens_to_av(t_token *start, t_token *end);

#endif