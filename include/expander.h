#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	*expand_str(t_ctx *ctx, char *s);
char	*expand_getenv(char **envp, char *key);
int		update_delimiter(t_redircmd *n_redir);
char	*append_char(char *res, char c);
char	*append_str(char *res, char *add);
int		expand_argv(t_ctx *ctx, char **argv);
int		is_quote(char c);
int		handle_quote(char c, char *quote);

#endif
