/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:29:57 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/11 22:12:40 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_word_in_quote(char *s, t_token *token)
{
	int	i;
	int	flag;

	i = 0;
	if (s[i] == '\'')
		flag = 1;
	else
		flag = 2;
	i++;
	while (s[i])
	{
		if  (((flag == 1 && s[i] == '\'') || (flag == 2 && s[i] == '"')) && (is_space(s[i + 1]) || is_separators(s[i + 1])))
			break ;
		i++;
	}
	token->str = strndup(s + 1, i - 2);
	token->type = WORD;
	if (!s[i])
		i--;
	return (i);
}

int	extract_separator(char *s, t_token *token)
{
	int	i;

	i = 0;
	if (s[i] == '|')
		token->type = PIPE;
	while (s[i] && is_separators(s[i]))
		i++;
	token->str = strndup(s, i);
	if (i == 2 && token->str[0] == '>')
		token->type = APPOUTREDIR;
	else if (i == 2 && token->str[0] == '<')
		token->type = HEREDOC;
	else if (i == 1 && token->str[0] == '>')
		token->type = OUTREDIR;
	else
		token->type = INREDIR;
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
		if (is_separators(s[i]) && !s_quote && !d_quote)
			break ;
		if (is_space(s[i]) && is_quote(s[i + 1]))
			break ;
		i++;
	}
	token->str = strndup(s, i);
	// if (quote_checking(token->str))
	// 	token->str = ft_trimquote(token->str);
	token->type = WORD;
	return (i);
}

void	extract_word(t_token *token, char *s)
{
	int	i;
	int	start;

	i = 0;
	while (s[i])
	{
		while(is_space(s[i]))
			i++;
		start = i;
		if (is_quote(s[i]))
			i = start + extract_word_in_quote(&s[i], token) + 1;
		else if (is_separators(s[i]))
			i = start + extract_separator(&s[i], token);
		else if (s[i])
			i = start + extract(&s[i], token);
		if (s[i])
			token = token->next;
	}
}


t_token	*get_token(char *s)
{
	int	i;
	int	word_count;
	t_token	*token;

	i = 0;
	token = NULL;
	word_count = countwords(s);
	printf("%d\n", word_count);
	while (i < word_count)
	{
		if (i == 0)
			token = new_token(i);
		else if (!token || !ft_lstadd_back(&token, new_token(i)))
			ft_clear_token(token);
		i++;
	}
	extract_word(token, s);
	return (token);
}
