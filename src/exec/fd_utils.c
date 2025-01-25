/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:21:22 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/09 18:06:23 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->fd == -1)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	close_fd_pipe(t_data *data, int i)
{
	while (data->fd_pipe[i])
	{
		close(data->fd_pipe[i][0]);
		close(data->fd_pipe[i][1]);
		i++;
	}
	clear_array(data->fd_pipe);
}

void	close_remaining_fds(t_data *data, int process_number)
{
	if (process_number && (data->fd_in == data->fd_pipe[process_number -1][0]))
		close(data->fd_pipe[process_number - 1][0]);
	if ((process_number != data->cmd_count -1)
		&& (data->fd_out == data->fd_pipe[process_number][1]))
		close(data->fd_pipe[process_number][1]);
}

void	close_fds(t_data *data, int process_number)
{
	int	i;

	i = 0;
	while (i <= data->cmd_count - 2)
	{
		if (i == process_number - 1)
		{
			close(data->fd_pipe[i][1]);
			if (data->fd_in != data->fd_pipe[i][0])
				close(data->fd_pipe[i][0]);
		}
		else if (i == process_number)
		{
			close(data->fd_pipe[i][0]);
			if (data->fd_out != data->fd_pipe[i][1])
				close(data->fd_pipe[i][1]);
		}
		else
		{
			close(data->fd_pipe[i][0]);
			close(data->fd_pipe[i][1]);
		}
		i++;
	}
}

void	close_cmd_fds(t_cmd *cmd, int fd_in, int fd_out)
{
	t_redir	*temp;

	while (cmd)
	{
		temp = cmd->redir;
		while (temp)
		{
			if (temp->fd != -1 && temp->fd != fd_in && temp->fd != fd_out)
				close(temp->fd);
			temp = temp->next;
		}
		cmd = cmd->next;
	}
}
