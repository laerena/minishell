#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "utils.h"
# include "error.h"

int				check_syntax(t_token *tokens);
t_cmd			*parse_or(t_token *start, t_token *end);
t_cmd			*parse_primary(t_token *start, t_token *end);
t_cmd			*parse_expression(t_token *tokens, int *syntax_error);
void			cmd_clear(t_cmd **cmd);

int				is_redirection(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);

t_token			*find_last_top_level(t_token *start, t_token *end, t_token_type type);
char			**tokens_to_argv(t_token *start, t_token *end);

t_cmd			*new_exec_node(char **argv);
t_cmd			*new_binop_node(t_node_type type, t_cmd *left, t_cmd *right);
t_cmd			*new_redir_node(t_cmd *child, char *file, t_redir_type type);
t_cmd			*new_subshell_node(t_cmd *child);

int				is_builtin_cmd(char *cmd_name);

#endif