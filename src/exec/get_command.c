/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:39:44 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:18:49 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_outredir(t_cmd *cmd, t_data *data, int process_number)
{
	int		fd;
	t_redir	*temp;

	fd = 1;
	temp = cmd->redir;
	while (temp)
	{
		if (temp->type == OUTREDIR || temp->type == APPOUTREDIR)
			fd = temp->fd;
		temp = temp->next;
	}
	if (process_number == data->cmd_count - 1)
		return (fd);
	if (fd == 1)
		return (data->fd_pipe[process_number][1]);
	return (fd);
}

int	get_inredir(t_cmd *cmd, t_data *data, int process_number)
{
	int		fd;
	t_redir	*temp;

	fd = 0;
	temp = cmd->redir;
	while (temp)
	{
		if ((temp->type == INREDIR || temp->type == HEREDOC) && temp->fd != -2)
			fd = temp->fd;
		temp = temp->next;
	}
	if (!process_number)
		return (fd);
	if (!fd)
		return (data->fd_pipe[process_number -1][0]);
	return (fd);
}

void	check_command_path(t_cmd *cmd)
{
	if (is_a_path(cmd->cmd) && access(cmd->cmd, F_OK | X_OK))
	{
		if (check_fd(cmd->redir))
			perror(cmd->cmd);
	}
	else if (!is_a_path(cmd->cmd) && check_fd(cmd->redir))
		ft_printf(2, "%s: commande introuvable\n", cmd->cmd);
}

void	check_command(t_cmd *cmd, char **env_tab)
{
	int		i;
	char	*temp;

	temp = cmd->cmd;
	i = 0;
	while (env_tab && env_tab[i])
	{
		cmd->cmd = ft_strjoin(env_tab[i], temp);
		if (!cmd->cmd)
		{
			free(temp);
			return ;
		}
		if (!access(cmd->cmd, F_OK))
			return (free(temp), check_command_path(cmd));
		free(cmd->cmd);
		cmd->cmd = NULL;
		i++;
	}
	cmd->cmd = temp;
	check_command_path(cmd);
}

void	get_command(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd[0])
	{
		if (!cmd->empty_var && (!cmd->redir
				|| (check_fd(cmd->redir) && !cmd->is_empty_cmd)))
			ft_printf(2, "%s: commande introuvable\n", cmd->cmd);
		return ;
	}
	if (is_builtin(cmd->cmd))
		return ;
	if (is_a_path(cmd->cmd))
		check_command_path(cmd);
	else
		check_command(cmd, data->path_tab);
}
