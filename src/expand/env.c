/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:07:41 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:18:28 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path_in_env(t_env *my_env)
{
	while (my_env)
	{
		if (ft_strncmp(my_env->var, "PATH=", 5) == 0)
			return (my_env->var);
		my_env = my_env->next;
	}
	return (NULL);
}

char	**fix_path_tab(char **tab)
{
	int		i;
	char	*temp;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		temp = tab[i];
		tab[i] = ft_strjoin(tab[i], "/");
		if (!tab[i])
		{
			tab[i] = temp;
			ft_tabclear(tab);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (tab);
}

char	**get_env_tab(t_env *my_env)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_lstsize(my_env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (my_env)
	{
		tab[i] = ft_strdup(my_env->var);
		if (!tab[i])
		{
			ft_tabclear(tab);
			return (NULL);
		}
		i++;
		my_env = my_env->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**get_path_tab(t_env *my_env)
{
	char	*path;
	char	*path_line;
	char	**tab;

	path = check_path_in_env(my_env);
	if (!path)
		return (NULL);
	path_line = ft_strdup(&path[5]);
	if (!path_line)
		return (NULL);
	tab = ft_split(path_line, ':');
	free(path_line);
	return (fix_path_tab(tab));
}

int	set_up_data(t_data *data, t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	data->env_tab = get_env_tab(*(data->my_env));
	if (!data->env_tab)
		return (0);
	data->path_tab = get_path_tab(*(data->my_env));
	if (!data->path_tab && check_path_in_env(*(data->my_env)))
		return (ft_tabclear(data->env_tab), 0);
	data->cmd_count = 0;
	while (temp)
	{
		data->cmd_count++;
		temp = temp->next;
	}
	data->process = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->process)
		return (ft_tabclear(data->env_tab), ft_tabclear(data->path_tab), 0);
	data->fd_pipe = malloc(sizeof(int *) * data->cmd_count);
	if (!data->fd_pipe || !fill_data_pipe(data))
		return (ft_tabclear(data->path_tab),
			ft_tabclear(data->env_tab), free(data->process), 0);
	return (1);
}
