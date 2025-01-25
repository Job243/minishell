/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:35:44 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:40:07 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_neg_quotes(char *str)
{
	int	i;
	int	quote;

	quote = str[0];
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	get_new_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -34 || str[i] == -39)
			i += inside_neg_quotes(&str[i]);
		else if (is_space(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	fill_temp_token(t_token *new_lst, char *str)
{
	int	i;
	int	start;

	i = 0;
	while (new_lst)
	{
		while (str[i] && is_space(str[i]))
			i++;
		new_lst->type = WORD;
		start = i;
		i += get_new_word(&str[i]);
		new_lst->str = ft_strndup(str + start, i - start);
		if (!new_lst->str)
			return (ft_clear_token(new_lst), 1);
		new_lst = new_lst->next;
	}
	return (0);
}

int	count_word_after_exp(char *str)
{
	int	word;
	int	i;

	word = 1;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == -34 || str[i] == -39)
			i += inside_neg_quotes(&str[i]);
		else if (str[i] != ' ' && str[i + 1] == ' ')
			word++;
		i++;
	}
	return (word);
}
