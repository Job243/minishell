/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_synthax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:32:06 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/22 19:11:24 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_after_pipe(char *s, int len)
{
	while (is_space(s[len]))
		len--;
	if (is_pipe(s[len]))
	{	
		ft_printf(2, "bash: synthax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	error_pipe(char *s, int flag)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && !is_pipe(s[i]) && !is_quote(s[i]))
		{
			if (!is_space(s[i]) && !is_redir(s[i]))
				flag = 1;
			if (is_redir(s[i]) && flag)
				flag = 0;
			i++;
		}
		if (is_quote(s[i]))
			return (error_pipe(&s[i + inside_quotes(&s[i]) + 1], 1));
		if (!flag)
		{
			ft_printf(2, "bash: synthax error near unexpected token `|'\n");
			return (1);
		}
		if (s[i])
			i++;
	}
	return (check_after_pipe(s, i - 1));
}

int	error_redir(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		while (s[i] && !is_redir(s[i]) && !is_quote(s[i]))
			i++;
		if (is_quote(s[i]))
			return (error_redir(&s[i + inside_quotes(&s[i]) + 1]));
		if (!s[i])
			return (0);
		if (is_redir(s[++i]))
		{
			if (!double_redir(&s[++i]))
				return (1);
		}
		while (s[i] && is_space(s[i]))
			i++;
		if (!s[i] || is_redir(s[i]))
			break ;
	}
	ft_printf(2, "bash: synthax error near unexpected token `newline'\n");
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
		ft_printf(2, "bash: synthax error near unexpected token `newline'\n");
		return (0);
	}
	if (is_redir(s[i]))
	{
		if (s[i] == '>')
			ft_printf(2, "bash: syntax error near unexpected token `>>'\n");
		if (s[i] == '<')
			ft_printf(2, "bash: syntax error near unexpected token `<<'\n");
		return (0);
	}
	return (1);
}

int	parse_error(char *s)
{
	if (!s || is_empty(s))
		return (-1);
	if (!quotes_closed(s))
		return (0);
	if (error_redir(s))
		return (0);
	if (error_pipe(s, 0))
		return (0);
	return (1);
}
