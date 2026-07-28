/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:49:47 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:49:48 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	handle_signals(void);
void	handle_heredoc_signals(void);
void	signals_reset(void);
void	signals_ignore(void);

#endif