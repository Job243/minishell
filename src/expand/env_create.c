/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:17 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 17:56:07 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*ft_lstlast_env(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

int	ft_lstaddback_env(t_env **env, t_env *new)
{
	if (!env || !new)
		return (0);
	if (*env)
		ft_lstlast_env(*env)->next = new;
	else
		*env = new;
	return (1);
}

t_env	*new_env(char *var)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->var = ft_strdup(var);
	if (!new->var)
		return (free(new), NULL);
	new->printed = 0;
	return (new);
}

void	ft_clear_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->var);
		free(env);
		env = temp;
	}
}
