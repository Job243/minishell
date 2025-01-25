/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:45 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/22 19:05:46 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] > 0)
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int	quotes_closed(char *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (s[i] == '\"' && s_quote % 2 == 0)
			d_quote++;
		i++;
	}
	if (s_quote == 0 && d_quote == 0)
		return (1);
	else if (s_quote % 2 == 0 && d_quote % 2 == 0)
		return (1);
	ft_printf(2, "bash: syntax error: unexpected end of file\n");
	return (0);
}

int	inside_quotes(char *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		if (s[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (is_separators(s[i]) && (!d_quote && !s_quote))
			break ;
		if (!s_quote && !d_quote && is_space(s[i + 1]))
			break ;
		i++;
	}
	if (!s[i] || is_separators(s[i]))
		i--;
	return (i);
}
