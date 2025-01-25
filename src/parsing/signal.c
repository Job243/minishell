/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:40:58 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/18 16:28:18 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal_parent(int sig)
{
	g_recu = 128 + sig;
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	set_parent_signals(void)
{
	struct sigaction	sa;

	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = if_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	set_exec_parent_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal_parent;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = handle_signal_parent;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

void	set_child_signals(void)
{
	rl_event_hook = sig_event;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}
