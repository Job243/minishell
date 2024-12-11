/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_synthax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:32:06 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/10 21:37:23 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int error_pipe(char *s)
{
	int i;
	int flag;

	i = 0;
	while (s[i])
	{
		flag = 0;
		while (s[i] && !is_pipe(s[i]))
		{
			if (!is_space(s[i]) && !is_redir(s[i]))
				flag = 1;
			if (is_redir (s[i]) && flag)
				flag = 0;
			i++;
		}
		if (!flag)
		{
			printf("bash: synthax error near unexpected token `|'\n");
			return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}

int error_redir(char *s)
{
	int i;
	i = 0;
	while (s[i])
	{
		while (s[i] && !is_redir(s[i]))
			i++;
		if (!s[i])
			return (0);
		i++;
		if (is_redir(s[i]))
		{
			i++;
			if (!double_redir(&s[i]))
				return (1);
		}
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i] || is_redir(s[i]))
			break ;
	}
	printf("bash: synthax error near unexpected token `newline'\n");
	return (1);
}

int	double_redir(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (!s[i])
	{
		printf("bash: synthax error near unexpected token `newline'\n");
		return (0);
	}
	if (is_redir(s[i]))
	{
		if (s[i] == '>')
			printf("bash: syntax error near unexpected token `>'\n");
		if (s[i] == '<')
			printf("bash: syntax error near unexpected token `<'\n");
		return (0);
	}
	return (1);
}

int	parse_error(char *s)
{
	if (!s || is_empty(s))
		return (0);
	if (!quotes_closed(s))
		return (0);
	if (error_redir(s))
		return (0);
	if (error_pipe(s))
		return (0);
	return (1);
}


