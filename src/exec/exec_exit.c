/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:56:53 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/23 23:01:46 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_array(int **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_all_tabs(t_cmd *cmd, t_data *data)
{
	ft_clear_cmd(cmd);
	free(data->process);
	ft_tabclear(data->path_tab);
	ft_tabclear(data->env_tab);
}

int	exit_argnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_parent(t_cmd *start, t_cmd *cmd, t_data *data, int exit_status)
{
	close_fd_pipe(data, 0);
	close_cmd_fds(start, 0, 0);
	wait(&data->process[0]);
	if (!cmd->tab[1])
		exit_status = 0;
	clear_all_tabs(start, data);
	ft_clear_env(*(data->my_env));
	ft_clear_env(*(data->export_env));
	if (exit_status < 0)
		exit(exit_status + 256);
	exit(exit_status);
}

void	exec_exit(t_cmd *start, t_cmd *cmd, t_data *data)
{
	int	exit_status;

	if (cmd->tab[1] && exit_argnum(cmd->tab[1]))
		exit_status = ft_atoi(cmd->tab[1]);
	else
		exit_status = 2;
	if (!cmd->redir || cmd->redir->fd != -1)
	{
		ft_printf(1, "exit\n");
		if (cmd->tab[1] && !exit_argnum(cmd->tab[1]))
		{
			ft_printf(2, "bash: exit: %s : ", cmd->tab[1]);
			ft_printf(2, "argument numérique nécessaire\n");
		}
		else if (cmd->tab[1] && cmd->tab[2])
			ft_printf(2, "bash: exit: trop d'arguments\n");
		if (!cmd->tab[1] || (cmd->tab[1] && !cmd->tab[2]) || (cmd->tab[1]
				&& !exit_argnum(cmd->tab[1])))
			exit_parent(start, cmd, data, exit_status);
		cmd->exit_status = 1;
	}
}
