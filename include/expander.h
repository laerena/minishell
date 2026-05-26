#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int		expand_ast(t_ctx *ctx, t_cmd *cmd);
char	*expand_str(t_ctx *ctx, char *s);
char	*expand_getenv(char **envp, char *key);

#endif