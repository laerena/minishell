/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_modes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 12:41:50 by leilai            #+#    #+#             */
/*   Updated: 2026/07/03 15:23:15 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_signals.h"

static void	sigs_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, sigs_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
