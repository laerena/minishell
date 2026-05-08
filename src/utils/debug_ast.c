#include "minishell.h"

/* p indentation */
static void	print_indent(int depth)
{
	while (depth > 0)
	{
		printf("  ");
		depth--;
	}
}

/* p one av array on one line */
static void	print_av(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		printf("[%s]", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
}

static char	*redir_mode_name(t_redir_mode mode)
{
	if (mode == R_INPUT)
		return ("IN");
	if (mode == R_OUTPUT)
		return ("OUT");
	if (mode == R_APPEND)
		return ("APPEND");
	if (mode == R_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

/*
** recursively prints the AST
** supports(for now):
** - N_EXEC
** - N_PIPE
**
** REDIR / AND / OR / SUBSHELL need to be added later
*/
static void	print_ast_node(t_cmd *cmd, int depth)
{
	if (!cmd)
		return ;
	print_indent(depth);
	if (cmd->type == N_EXEC)
	{
		printf("EXEC ");
		print_av(cmd->u_cmd.exec.av);
		printf("\n");
	}
	else if (cmd->type == N_PIPE)
	{
		printf("PIPE\n");
		print_ast_node(cmd->u_cmd.binop.left, depth + 1);
		print_ast_node(cmd->u_cmd.binop.right, depth + 1);
	}
	else if (cmd->type == N_REDIR)
	{
		printf("REDIR %s file=[%s]\n",
			redir_mode_name(cmd->u_cmd.redir.mode),
			cmd->u_cmd.redir.file);
		print_ast_node(cmd->u_cmd.redir.cmd, depth + 1);
	}
	else
		printf("UNKNOWN NODE\n");
}

/* public */
void	print_ast(t_cmd *cmd)
{
	print_ast_node(cmd, 0);
}
