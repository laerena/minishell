/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:11:21 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 12:47:08 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int		is_space(char c);
int		is_operator(char c);
void	skip_spaces(const char *input, int *i);
char	*read_word(const char *input, int *i);
char	*read_operator(const char *input, int *i, t_token_type *type);

t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **lst, t_token *new_node);

#endif