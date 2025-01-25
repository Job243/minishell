/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:01:06 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:29:43 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_export_env(char *str, t_cmd *cmd)
{
	int	i;
	int	equal_sign;

	i = 0;
	equal_sign = 0;
	while (str[equal_sign] && str[equal_sign] != '=')
		equal_sign++;
	while (i < equal_sign)
	{
		if ((!i && ft_isdigit(str[i])) || str[i] == '-'
			|| (!ft_isalnum(str[i]) && str[i] != '_'))
			break ;
		i++;
	}
	if (!equal_sign || i != equal_sign || !str[equal_sign])
	{
		if (!equal_sign || i != equal_sign)
			ft_printf(2, "export: « %s » : identifiant non valable\n", str);
		if (!equal_sign || (!str[equal_sign] && i != equal_sign)
			|| i != equal_sign)
			cmd->exit_status = 1;
		return (0);
	}
	return (1);
}

void	check_var_exist(char *str, t_env *my_env, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	while (my_env)
	{
		if (!ft_strncmp(str, my_env->var, i))
			return (delete_var(my_env, data->my_env));
		my_env = my_env->next;
	}
}

void	export_without_arg(t_env *env, char *index)
{
	char	*to_print;
	t_env	*temp;

	if (!env)
		return ;
	temp = env;
	if (index == NULL)
		to_print = env->var;
	else
		to_print = index;
	while (temp)
	{
		if (ft_strncmp(to_print, temp->var, ft_strlen(to_print)) > 0
			&& !temp->printed)
			export_without_arg(env, temp->var);
		temp = temp->next;
	}
	printf("export %s\n", to_print);
	actualise_env(env, to_print);
	if (index == NULL)
	{
		while (env && env->printed)
			env = env->next;
		export_without_arg(env, NULL);
	}
}

int	check_valid_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '-'
		&& (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (!str[i]);
}

int	exec_export(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd->tab[1])
		return (export_without_arg(*data->export_env, NULL),
			reset_env_print(*data->export_env), 0);
	while (cmd->tab[i])
	{
		if (check_valid_export_env(cmd->tab[i], cmd))
		{
			check_var_exist(cmd->tab[i], *(data->my_env), data);
			if (!ft_lstaddback_env(data->my_env, new_env(cmd->tab[i]))
				|| !ft_lstaddback_env(data->export_env, new_env(cmd->tab[i])))
				return (printf("Erreur malloc export\n"));
		}
		else if (check_valid_export(cmd->tab[i])
			&& !ft_lstaddback_env(data->export_env, new_env(cmd->tab[i])))
			return (printf("Erreur malloc export\n"));
		i++;
	}
	return (0);
}
