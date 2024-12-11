/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:51:49 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/11 21:35:27 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_token(t_token *token)
{// a revoir si pb de leak
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}


int	ft_lstadd_back(t_token **token, t_token *new)
{
	if (!token || !new)
		return (0);
	if (*token)
		ft_lstlast(*token)->next = new;
	else
		*token = new;
	return (1);
}

t_token	*ft_lstlast(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

t_token	*new_token(int n)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = NULL;
	token->token_id = n + 1;
	token->type = UNKNOW;
	token->next = NULL;
	return (token);
}

int		token_size(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

void printtoken(t_token *token)
{
	while(token)
	{
		printf("word is %s type is %d\n", token->str, token->type);
		token = token->next;
	}
}
