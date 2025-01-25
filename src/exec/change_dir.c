/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:56:37 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/23 23:01:04 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_home(t_data *data)
{
	t_env	*temp;

	temp = *(data->my_env);
	while (temp)
	{
		if (!ft_strncmp(temp->var, "HOME=", 5))
			return (ft_strlen(temp->var));
		temp = temp->next;
	}
	ft_printf(2, "cd: « HOME » non défini\n");
	return (0);
}

char	*get_home(t_env *env)
{
	char	*home;

	while (ft_strncmp(env->var, "HOME=", 5))
		env = env->next;
	home = ft_strdup(env->var + 5);
	return (home);
}

void	change_pwd_env(t_env *env)
{
	char	*temp;
	char	*pwd;

	while (env && ft_strncmp(env->var, "PWD=", 4))
		env = env->next;
	if (env)
	{
		temp = env->var;
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (perror("pwd"));
		env->var = ft_strjoin("PWD=", pwd);
		free(pwd);
		if (!env->var)
		{
			env->var = temp;
			printf("Erreur Malloc PWD\n");
		}
		else
			free(temp);
	}
}

void	change_oldpwd_env(char *oldpwd, t_env *env)
{
	char	*temp;
	t_env	*start;

	start = env;
	if (!oldpwd)
		return ;
	while (env && ft_strncmp(env->var, "OLDPWD=", 7))
		env = env->next;
	if (env)
	{
		temp = env->var;
		env->var = ft_strjoin("OLDPWD=", oldpwd);
		free(oldpwd);
		if (!env->var)
		{
			env->var = temp;
			printf("Erreur Malloc OLDPWD\n");
		}
		else
			free(temp);
	}
	else
		free(oldpwd);
	change_pwd_env(start);
}

void	check_path_content(char *path)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (path[0] != '/')
		flag = 1;
	while (path[i])
	{
		if (path[i] == '/' && !flag)
			flag = 1;
		else if (path[i] == '/' && flag && path[i + 1])
		{
			ft_printf(2, "cd: %s: N'est pas un dossier\n", path);
			return ;
		}
		i++;
	}
	perror(path);
}
