/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:55:36 by leilai            #+#    #+#             */
/*   Updated: 2026/05/21 15:04:25 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*redir_type_name(t_redir_type type)
{
	if (type == R_INPUT)
		return ("IN");
	if (type == R_OUTPUT)
		return ("OUT");
	if (type == R_APPEND)
		return ("APPEND");
	if (type == R_HEREDOC)
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
			redir_type_name(cmd->u_cmd.redir.type),
			cmd->u_cmd.redir.file);
		print_ast_node(cmd->u_cmd.redir.cmd, depth + 1);
	}
	else if (cmd->type == N_AND)
	{
		printf("AND\n");
		print_ast_node(cmd->u_cmd.binop.left, depth + 1);
		print_ast_node(cmd->u_cmd.binop.right, depth + 1);
	}
	else if (cmd->type == N_OR)
	{
		printf("OR\n");
		print_ast_node(cmd->u_cmd.binop.left, depth + 1);
		print_ast_node(cmd->u_cmd.binop.right, depth + 1);
	}
	else if (cmd->type == N_SUBSHELL)
	{
		printf("SUBSHELL\n");
		print_ast_node(cmd->u_cmd.subshell.child, depth + 1);
	}
	else
		printf("UNKNOWN NODE\n");
}

/* public */
void	print_ast(t_cmd *cmd)
{
	print_ast_node(cmd, 0);
}
