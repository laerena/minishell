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

/* p one ast node and its children */
static void	print_ast_node(t_ast *root, int depth)
{
	if (!root)
		return ;
	print_indent(depth);
	if (root->type == NODE_PIPE)
		printf("PIPE\n");
	else
	{
		printf("CMD ");
		print_av(root->av);
		printf("\n");
	}
	print_ast_node(root->left, depth + 1);
	print_ast_node(root->right, depth + 1);
}

void	print_ast(t_ast *root)
{
	print_ast_node(root, 0);
}
