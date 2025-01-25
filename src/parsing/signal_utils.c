/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:14:35 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:18:00 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_sigint(int sig)
{
	g_recu = 128 + sig;
	rl_done = 1;
}

void	set_status_if_signal(t_data *data)
{
	if (g_recu == 130)
		data->status = g_recu;
	else
		data->status = 0;
	g_recu = 0;
}

void	print_signals(t_data *data)
{
	if (data->sigint == true)
		write(STDERR_FILENO, "\n", 1);
	if (data->sigquit == true)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	change_signal_status(t_data *data, t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	if (WIFSIGNALED(data->status))
	{
		data->status = 128 + WTERMSIG(data->status);
		if (data->status == 128 + SIGINT)
			data->sigint = true;
		else if (data->status == 128 + SIGQUIT)
			data->sigquit = true;
	}
	else if (WIFEXITED(data->status) && cmd->exit_status != 1)
		data->status = WEXITSTATUS(data->status);
	else if (WIFEXITED(data->status))
		data->status = 1;
	else if (WIFSTOPPED(data->status))
		data->status = 128 + WSTOPSIG(data->status);
}
