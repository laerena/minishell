#ifndef INIT_H
# define INIT_H

#include "minishell.h"

//fts
int	init(t_ctx *ctx, char **envp);
int	update_shlvl(t_ctx *ctx);

#endif