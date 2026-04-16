#include "minishell.h"

static char	*token_type_name(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type=%s, value=[%s]\n",
			token_type_name(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}
