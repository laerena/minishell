/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:30:45 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/23 16:00:01 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// | Command   | Wildcard expansion? | Notes                                                      |
// |-----------|---------------------|------------------------------------------------------------|
// | `echo`    | Yes                 | `echo *.c` → `echo 1.c 2.c`                                |
// | `cd`      | Yes                 | `cd *` expands, but only the first match is used           |
// | `export`  | Yes                 | But rarely useful; expands to matching filenames           |
// | `unset`   | Yes                 | But rarely useful; expands to matching filenames           |
// | `env`     | Yes                 | If you do `env *.c`, it runs `env` with those filenames as args |
// | `exit`    | Yes                 | `exit *` expands, but only the first match is used as the exit code (usually not meaningful) |
// | `pwd`     | No                  | No arguments, so nothing to expand                         |

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "executor.h"

int	run_builtin(t_ctx *ctx, t_cmd *ast_node)
{
	(void)ctx;
	(void)ast_node;
	ft_printf("WORKING IN PROGRESS\n");
	return(0);
}