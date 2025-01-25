/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:14:15 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/20 18:44:25 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_hdoc(t_redir *temp, t_data *data)
{
	create_hdoc_file(temp);
	if (!temp->hdoc_name)
		return (0);
	temp->fd = open(temp->hdoc_name, O_WRONLY | O_CREAT | O_EXCL
			| O_TRUNC, 0600);
	if (temp->fd == -1)
		return (0);
	if (get_hdoc(temp->fd, temp->file, data) == 1)
	{
		close(temp->fd);
		temp->fd = open(temp->hdoc_name, O_RDONLY);
		return (1);
	}
	return (0);
}

int	open_files_outr(t_cmd *cmd, t_redir *temp)
{
	if (access(temp->file, F_OK))
		temp->fd = open(temp->file, O_CREAT | O_WRONLY, 0664);
	else if (temp->type == OUTREDIR)
		temp->fd = open(temp->file, O_WRONLY | O_TRUNC);
	else
		temp->fd = open(temp->file, O_WRONLY | O_APPEND);
	if (temp->fd == -1)
	{
		cmd->exit_status = 1;
		perror(temp->file);
		return (0);
	}
	return (1);
}

int	open_inredir(t_cmd *cmd, t_redir *redir)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		cmd->exit_status = 1;
		perror(redir->file);
		return (0);
	}
	return (1);
}

int	open_files(t_cmd *cmd, t_data *data)
{
	t_redir	*temp;

	while (cmd)
	{
		temp = cmd->redir;
		while (temp)
		{
			if (temp->type == HEREDOC && !open_files_hdoc(temp, data))
				return (0);
			else if (temp->type == INREDIR && !open_inredir(cmd, temp))
				break ;
			else if ((temp->type == OUTREDIR || temp->type == APPOUTREDIR)
				&& !open_files_outr(cmd, temp))
				break ;
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	fill_data_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		data->fd_pipe[i] = malloc(sizeof(int) * 2);
		if (!data->fd_pipe[i])
			return (clear_array(data->fd_pipe), 0);
		i++;
	}
	data->fd_pipe[i] = NULL;
	while (i > 0)
	{
		i--;
		if (pipe(data->fd_pipe[i]) == -1)
		{
			perror("pipe");
			close_fd_pipe(data, i + 1);
			return (0);
		}
	}
	return (1);
}
