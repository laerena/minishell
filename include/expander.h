#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int		expand_ast(t_ctx *ctx, t_cmd *cmd);
char	*expand_str(t_ctx *ctx, char *s);
char	*expand_getenv(char **envp, char *key);
char	*strip_heredoc_quotes(char *s, int *do_expand);
char	*append_char(char *res, char c);
char	*append_str(char *res, char *add);
int		expand_argv(t_ctx *ctx, char **argv);

#endif
