/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:40:22 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/28 13:47:43 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigs_main(int signum);
static void	replace_line(const char *text, int clear_undo);

int			rl_kill_text(int start, int end);
int			rl_insert_text(const char *text);

static void	replace_line(const char *text, int clear_undo)
{
	(void)clear_undo;
	rl_kill_text(0, rl_end);
	rl_insert_text(text);
}

void	handle_signals(void)
{
	signal(SIGINT, sigs_main);
	signal(SIGQUIT, SIG_IGN);
}

static void	sigs_main(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
