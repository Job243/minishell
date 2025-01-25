/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:12:48 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:29:49 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_env_print(t_env *env)
{
	while (env)
	{
		env->printed = 0;
		env = env->next;
	}
}

int	is_a_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	index_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd->index = i;
		i++;
		cmd = cmd->next;
	}
}

void	actualise_env(t_env *env, char *var)
{
	while (env->var != var)
		env = env->next;
	env->printed = 1;
}
