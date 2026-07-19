#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_split(char **arr);

void	print_tokens(t_token *tokens);
void	print_ast(t_cmd *cmd);

char	**find_var_in_envp(char **envp, char *args);

int 	my_dup2(int oldfd, int newfd);

void	malloc_error_exit(t_ctx *ctx);

#endif