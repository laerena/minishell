/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:56:07 by leilai            #+#    #+#             */
/*   Updated: 2026/05/21 16:28:15 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "utils.h"

int				check_syntax(t_token *tokens);
t_cmd			*parse_or(t_token *start, t_token *end);
t_cmd			*parse_primary(t_token *start, t_token *end);
t_cmd			*parse_expression(t_token *tokens);
void			cmd_clear(t_cmd **cmd);

int				is_redirection(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);

t_token			*find_last_top_level(t_token *start, t_token *end, t_token_type type);
char			**tokens_to_argv(t_token *start, t_token *end);

t_cmd			*new_exec_node(char **argv);
t_cmd			*new_binop_node(t_node_type type, t_cmd *left, t_cmd *right);
t_cmd			*new_redir_node(t_cmd *child, char *file, t_redir_type type);
t_cmd			*new_subshell_node(t_cmd *child);

#endif