/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:30:45 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/24 14:13:22 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// | Command   | Wildcard expansion? | Notes                                                      |
// |-----------|---------------------|------------------------------------------------------------|
// | `echo`    | Yes                 | `echo *.c` → `echo 1.c 2.c`                                |
// | `cd`      | Yes                 | `cd *` expands, but only the first match is used           |
// | `pwd`     | No                  | No arguments, so nothing to expand                         |
// | `env`     | Yes                 | If you do `env *.c`, it runs `env` with those filenames as args |
// | `export`  | Yes                 | But rarely useful; expands to matching filenames           |
// | `unset`   | Yes                 | But rarely useful; expands to matching filenames           |
// | `exit`    | Yes                 | `exit *` expands, but only the first match is used as the exit code (usually not meaningful) |

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "executor.h"

static int	builtin_export(t_ctx *ctx, char **args)
{
	char	**envp_vars;
	char	**tmp;

	while (*args)
	{
		envp_vars = ctx->envp;
		while (*envp_vars)
		{
			if (ft_strcmp(*args, *envp_vars) == 0)
				break ;
			else if (ft_strncmp(*args, *envp_vars, ft_strclen(*args, '=')) == 0)
			{
				*tmp = *envp_vars;
				*envp_vars = ft_strdup(*args);
				free(*tmp);
			}
			envp_vars++;
		}
		if (*envp_vars == NULL)
		{
			tmp = ft_realloc(envp, ft_strlen(envp), ft_strlen(envp) + 1);
		}
	}
}

static int	builtin_env(char **envp)
{
	while (*envp)
	{
		if (ft_printf("%s\n", *envp) == -1)
			return (1);
		envp++;
	}
	return (0);
}

static int	builtin_pwd(t_ctx *ctx)
{
	char	buf[256];

	if (getcwd(buf, 256) == NULL)
	{
		perror("pwd");
		return (ctx->last_exit_status = 1, 1);
	}
	if (write(1, buf, ft_strlen(buf)) == -1)
		return (ctx->last_exit_status = 1, 1);
	if (write(1, "\n", 1) == -1)
		return (ctx->last_exit_status = 1, 1);
	return (0);
}

static int	builtin_cd(t_ctx *ctx, char *path)
{
	// if (!path)
	// {
	// 	path =
	// }
	if (chdir(path) == -1)
	{
		perror("cd");
		return (ctx->last_exit_status = 1, 1);
	}
	return (ctx->last_exit_status = 0, 0);
}

//display a line of text on stdout
//option: -n: do not output the trailing newline
//as simple as possible for what we need
static int	builtin_echo(t_ctx *ctx, char **args)
{
	int		has_newline;

	has_newline = 1;
	while (*args)
	{
		if (ft_strncmp("-n", *args, 3) == 0)
			has_newline = 0;
		else
			break ;
		args++;
	}
	while (*args)
	{
		if (write(1, *args, ft_strlen(*args)) == -1)
			return (ctx->last_exit_status = 1, 1);
		if (write(1, " ", 1) == -1)
			return (ctx->last_exit_status = 1, 1);
		args++;
	}
	if (has_newline == 1)
			if (write (1, "\n", 1) == -1)
				return (ctx->last_exit_status = 1, 1);
	return (ctx->last_exit_status = 0, 0);
}

//main ft to handle builtin cmds
//expand wildcards then exec the correct builtin cmds
//propagate the error return;
int	run_builtin(t_ctx *ctx, t_cmd *ast_node)
{
	t_execmd	*exec;

	exec = &ast_node->u_cmd.exec;
	if (expand_wildcards(&exec->argv) == 1)
		return (ctx->last_exit_status = 1, 1);
	if (exec->builtin == BUILTIN_ECHO)
		return (builtin_echo(ctx, exec->argv + 1));
	else if (exec->builtin == BUILTIN_CD)
		return (builtin_cd(ctx, exec->argv[1]));
	else if (exec->builtin == BUILTIN_PWD)
		return (builtin_pwd(ctx));
	else if (exec->builtin == BUILTIN_EXPORT)
		return (builtin_export(ctx, exec->argv + 1))
	// else if (exec->builtin == BUILTIN_UNSET)

	else if (exec->builtin == BUILTIN_ENV)
		return (builtin_env(ctx->envp));
	// else if (exec->builtin == BUILTIN_EXIT)
	else
		return (1);
	return(0);
}
