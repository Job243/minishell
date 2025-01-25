/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:32:06 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:49:09 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*change_token_head(t_token **token, t_token *new)
{
	ft_lstlast(new)->next = (*token)->next;
	(*token)->next = NULL;
	ft_clear_token(*token);
	*token = new;
	return (new);
}

t_token	*change_token_middle(t_token *start, t_token *new, t_token *temp)
{
	start->next = new;
	ft_lstlast(new)->next = temp->next;
	temp->next = NULL;
	ft_clear_token(temp);
	return (new);
}

t_token	*get_token_expand(t_token *token, t_token *temp)
{
	if (token == temp)
		return (temp);
	while (token->next != temp)
		token = token->next;
	return (token);
}

t_token	*split_expand(t_token **token, t_token *temp)
{
	t_token	*start;
	t_token	*new_lst;
	int		word_count;
	int		i;

	if (!temp->str[0])
		return (temp);
	word_count = count_word_after_exp(temp->str);
	i = 0;
	start = get_token_expand(*token, temp);
	while (i < word_count)
	{
		if (i == 0)
			new_lst = new_token(temp->env);
		else if (!new_lst || !ft_lstadd_back(&new_lst, new_token(temp->env)))
			return (ft_clear_token(new_lst), NULL);
		i++;
	}
	if (fill_temp_token(new_lst, temp->str))
		return (NULL);
	if (temp == *token)
		return (change_token_head(token, new_lst));
	return (change_token_middle(start, new_lst, temp));
}
