#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	handle_signals(void);
void	handle_heredoc_signals(void);
void	signals_reset(void);
void	signals_ignore(void);

#endif