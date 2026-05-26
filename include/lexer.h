#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token	*lexer_tokenize(const char *input);
void	token_clear(t_token **lst);

/* internal */
int		is_space(char c);
int		is_operator(char c);
void	skip_spaces(const char *input, int *i);
char	*read_word(const char *input, int *i);
char	*read_operator(const char *input, int *i, t_token_type *type);

t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **lst, t_token *new_node);

#endif