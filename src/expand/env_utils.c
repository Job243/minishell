/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:19:20 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 20:11:20 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_var_in_env(char *var, t_env *my_env)
{
	while (my_env)
	{
		if (!ft_strncmp(var, my_env->var, ft_strlen(var)))
			return (my_env);
		my_env = my_env->next;
	}
	return (NULL);
}

void	delete_var(t_env *to_delete, t_env **my_env)
{
	t_env	*temp;

	free(to_delete->var);
	if ((*my_env) == to_delete)
	{
		(*my_env) = (*my_env)->next;
		free(to_delete);
		return ;
	}
	temp = *my_env;
	while (temp->next != to_delete)
		temp = temp->next;
	temp->next = to_delete->next;
	free(to_delete);
}

t_env	*copy_empty_env(t_env **env)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	path = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!path)
		return (NULL);
	*env = new_env(path);
	if (!*env)
		return (NULL);
	if (!ft_lstaddback_env(env, new_env("SHLVL=1"))
		|| !ft_lstaddback_env(env, new_env("_=/usr/bin/env")))
	{	
		ft_clear_env(*env);
		return (NULL);
	}
	return (*env);
}

t_env	*copy_env(void)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	if (!__environ[i])
		return (copy_empty_env(&env));
	while (__environ[i])
	{
		if (!i)
			env = new_env(__environ[i]);
		else if (!env || !ft_lstaddback_env(&env, new_env(__environ[i])))
		{
			ft_clear_env(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
