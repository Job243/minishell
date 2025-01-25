/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:29:56 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 18:38:18 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_question_mark(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		if (str[i] == '?')
			return (i);
		i++;
	}
	return (-1);
}

char	*chech_variable_in_env(char *variable, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->var, variable, ft_strlen(variable)) == 0)
			return (env->var);
		env = env->next;
	}
	return (NULL);
}

char	*get_variable_name(char *str)
{
	int		i;
	int		j;
	char	*variable;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	variable = malloc(sizeof(char) * i + 2);
	if (!variable)
		return (NULL);
	j = 0;
	while (str[j] && j < i)
	{
		variable[j] = str[j];
		j++;
	}
	variable[i] = '=';
	variable[i + 1] = '\0';
	return (variable);
}

void	error_expand(t_token *token, char *var_name)
{
	free(token->str);
	token->str = NULL;
	if (var_name)
		free(var_name);
}

void	expand_var2(t_token *token, int dollar, char *var, char **new)
{
	char	*temp;
	char	*env_var;

	env_var = chech_variable_in_env(var, token->env);
	if (env_var)
	{
		temp = (*new);
		(*new) = ft_strjoin((*new), &env_var[ft_strlen(var)]);
		free(temp);
		if (!(*new))
			return ;
	}
	if (token->str[dollar + ft_strlen(var) - 1])
	{
		temp = (*new);
		(*new) = ft_strjoin((*new), token->str + dollar + ft_strlen(var) - 1);
		free(temp);
		if (!(*new))
			return ;
	}
}
