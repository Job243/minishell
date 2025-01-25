/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:55:32 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/23 23:00:28 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd_empty(t_data *data, t_cmd *cmd)
{
	char	*home;
	char	*oldpwd;

	(void)cmd;
	home = get_home(*data->my_env);
	if (!home)
		return ;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd && errno == ENOENT)
		perror("chdir: error retrieving current directory"
			": getcwd: cannot access parent directories");
	if (chdir(home) == -1)
	{
		printf("%d\n", errno);
		if (errno == EACCES)
			check_path_content(home);
		else
			perror(home);
		cmd->exit_status = 1;
		return (free(home));
	}
	change_oldpwd_env(oldpwd, *data->my_env);
	free(home);
}

void	exec_env(t_env *my_env)
{
	while (my_env)
	{
		printf("%s\n", my_env->var);
		my_env = my_env->next;
	}
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	exec_buildin_parent(t_cmd *start, t_cmd *cmd, t_data *data)
{
	if (!cmd->index && !cmd->next)
	{
		if (!ft_strncmp(cmd->cmd, "unset", 6))
			exec_unset(cmd, data);
		if (!ft_strncmp(cmd->cmd, "exit", 5))
			exec_exit(start, cmd, data);
		if (!ft_strncmp(cmd->cmd, "export", 7))
			exec_export(cmd, data);
		if (!ft_strncmp(cmd->cmd, "cd", 3))
			exec_cd(cmd, data);
	}
}

void	exec_buildin_child(t_cmd *start, t_cmd *cmd, t_data *data, int process)
{
	if (!ft_strncmp(cmd->cmd, "echo", 5))
		exec_echo(cmd, data);
	if (!ft_strncmp(cmd->cmd, "pwd", 4))
		exec_pwd();
	if (!ft_strncmp(cmd->cmd, "env", 4))
		exec_env(*(data->my_env));
	exit_pipex_child(start, data, process, 0);
}
