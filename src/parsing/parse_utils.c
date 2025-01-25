/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:28:37 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:28:54 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	count_separator(char *str)
{
	int	i;

	i = 0;
	if (is_pipe(str[0]))
		return (0);
	while (is_redir(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	while (!is_space(str[i]) && !is_separators(str[i]) && str[i])
	{
		if (is_quote(str[i]))
			i += inside_quotes(&str[i]);
		i++;
	}
	return (i - 1);
}

int	word_counting(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (is_separators(str[i]) && !s_quote && !d_quote)
			break ;
		if (is_space(str[i]) && !s_quote && !d_quote)
			break ;
		i++;
	}
	return (i - 1);
}

int	countwords(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (is_quote(str[i]))
			i += inside_quotes(&str[i]);
		else if (is_separators(str[i]))
			i += count_separator(&str[i]);
		else if (str[i])
			i += word_counting(&str[i]);
		if (str[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	check_parse_error(int parse, t_data *data)
{
	if (parse == 0)
		data->status = 2;
}
