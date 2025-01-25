/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:23:59 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:22:17 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(t_cmd *cmd, t_data *data)
{
	int		i;
	t_env	*to_delete;

	i = 1;
	while (cmd->tab[i])
	{
		to_delete = find_var_in_env(cmd->tab[i], *(data->my_env));
		if (to_delete)
			delete_var(to_delete, data->my_env);
		i++;
	}
	i = 1;
	while (cmd->tab[i])
	{
		to_delete = find_var_in_env(cmd->tab[i], *(data->export_env));
		if (to_delete)
			delete_var(to_delete, data->export_env);
		i++;
	}
}

void	exec_echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd->tab[i] && data->fd_in != -1)
		printf("\n");
	else if (data->fd_in != -1)
	{
		if (!ft_strncmp(cmd->tab[1], "-n", 3))
		{
			flag = 1;
			i++;
		}
		while (cmd->tab[i])
		{
			printf("%s", cmd->tab[i]);
			if (cmd->tab[i + 1])
				printf(" ");
			i++;
		}
		if (!flag)
			printf("\n");
	}
}

void	exec_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		perror("pwd");
}

int	check_home_error(t_cmd *cmd, int home_len)
{
	if (!home_len)
	{
		cmd->exit_status = 1;
		return (0);
	}
	if (home_len == 5)
		return (0);
	if (cmd->tab[1] && cmd->tab[2])
	{
		ft_printf(2, "cd: trop d'arguments\n");
		cmd->exit_status = 1;
		return (0);
	}
	return (1);
}

void	exec_cd(t_cmd *cmd, t_data *data)
{
	int		home_len;
	char	*oldpwd;

	home_len = check_home(data);
	if (!check_home_error(cmd, home_len))
		return ;
	if (!cmd->tab[1])
		exec_cd_empty(data, cmd);
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (!oldpwd)
			return (perror("pwd"));
		if (chdir(cmd->tab[1]) == -1)
		{
			if (errno == EACCES)
				check_path_content(cmd->tab[1]);
			else
				perror(cmd->tab[1]);
			cmd->exit_status = 1;
			return ;
		}
		change_oldpwd_env(oldpwd, *data->my_env);
	}
}
