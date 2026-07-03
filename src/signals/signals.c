/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:40:22 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/03 12:45:31 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_signals.h"

volatile sig_atomic_t	g_signal = 0;

//int			rl_kill_text(int start, int end);
//int			rl_insert_text(const char *text);
void		rl_replace_line(const char *text, int clear_undo);

// ctrl + c handler
static void	sigs_main(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sigs_main);
	signal(SIGQUIT, SIG_IGN);
}

// child
void	signals_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
