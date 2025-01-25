/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:31:25 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 18:07:24 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_quote(const char *str)
{
	size_t	i;
	size_t	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == -34 || str[i] == -39)
			quote++;
		i++;
	}
	return (i - quote);
}

void	mark_quotes(t_token *token)
{
	int	i;
	int	flag_squote;
	int	flag_dquote;

	flag_dquote = 0;
	flag_squote = 0;
	while (token)
	{
		i = 0;
		while (token->str[i])
		{
			if (token->str[i] == '\'' && !flag_dquote)
			{
				flag_squote = !flag_squote;
				token->str[i] = -34;
			}
			if (token->str[i] == '"' && !flag_squote)
			{
				flag_dquote = !flag_dquote;
				token->str[i] = -39;
			}
			i++;
		}
		token = token->next;
	}
}

void	trim_quotes(char *new, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == -34 || str[i] == -39)
			i++;
		if (str[i])
			new[j++] = str[i++];
	}
	new[j] = '\0';
}

int	remove_quotes(t_token *token)
{
	char	*new;

	while (token)
	{
		if (has_quote(token->str))
		{
			new = malloc(ft_strlen_quote(token->str) + 1);
			if (!new)
				return (ft_clear_token(token), 0);
			trim_quotes(new, token->str);
			free(token->str);
			token->str = new;
		}
		token = token->next;
	}
	return (1);
}
