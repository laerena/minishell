/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:50:21 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:56:37 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "utils.h"
# include "error.h"

//fts
//	parse_imple.c
t_cmd			*parse_expression(t_token *tokens, int *syntax_error);
t_cmd			*parse_or(t_token *start, t_token *end);
//	parse.c
t_cmd			*parse_command(t_token *start, t_token *end);
t_cmd			*parse_primary(t_token *start, t_token *end);
//		parse_utils.c
t_token			*range_last(t_token *start, t_token *end);
t_token			*find_matching_rparen(t_token *start);
t_token			*get_subshell_end(t_token *start);
//	syntax_check.c
int				check_syntax(t_token *tokens);
//	cmd_free.c
void			cmd_clear(t_cmd **cmd);
//	parser_utils_redir.c
int				is_redirection(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);
//	parser_utils.c
t_token			*find_last_top_level(t_token *start,
					t_token *end, t_token_type type);
char			**tokens_to_argv(t_token *start, t_token *end);
int				is_builtin_cmd(char *cmd_name);
//	cmd_new.c
t_cmd			*new_exec_node(char **argv);
t_cmd			*new_binop_node(t_node_type type, t_cmd *left, t_cmd *right);
t_cmd			*new_redir_node(t_cmd *child, char *file, t_redir_type type);
t_cmd			*new_subshell_node(t_cmd *child);

#endif