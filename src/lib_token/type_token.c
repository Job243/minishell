/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:29:57 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 20:57:42 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(t_token *token)
{
	while (token)
	{
		if (!token->str)
		{
			ft_clear_token(token);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	extract_separator(char *s, t_token *token)
{
	int	i;

	i = 0;
	if (s[i] == '|')
	{
		token->type = PIPE;
		token->str = ft_strndup(s, 1);
		return (1);
	}
	while (s[i] && is_redir(s[i]))
		i++;
	while (s[i] && is_space(s[i]))
		i++;
	while (s[i] && !is_space(s[i]) && !is_separators(s[i]))
	{
		if (is_quote(s[i]))
			i += inside_quotes(&s[i]);
		i++;
	}
	token->str = ft_strndup(s, i);
	if (!token->str)
		return (i);
	assign_redir_type(token);
	return (i);
}

int	extract(char *s, t_token *token)
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
		if (is_separators(s[i]) && !d_quote && !s_quote)
			break ;
		if (is_space(s[i]) && !s_quote && !d_quote)
			break ;
		i++;
	}
	token->str = ft_strndup(s, i);
	token->type = WORD;
	return (i);
}

void	extract_word(t_token *token, char *s)
{
	int	i;
	int	start;

	i = 0;
	while (s[i] && token)
	{
		while (is_space(s[i]))
			i++;
		start = i;
		if (is_separators(s[i]))
			i = start + extract_separator(&s[i], token);
		else if (s[i])
			i = start + extract(&s[i], token);
		if (s[i])
			token = token->next;
	}
}

t_token	*get_token(char *s, t_env *env)
{
	int		i;
	int		word_count;
	t_token	*token;

	i = 0;
	token = NULL;
	word_count = countwords(s);
	while (i < word_count)
	{
		if (i == 0)
			token = new_token(env);
		else if (!token || !ft_lstadd_back(&token, new_token(env)))
		{
			ft_clear_token(token);
			return (NULL);
		}
		i++;
	}
	extract_word(token, s);
	if (!check_token(token))
		return (NULL);
	return (token);
}
