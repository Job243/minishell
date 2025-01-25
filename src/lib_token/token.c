/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:51:49 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/15 19:32:01 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_token	*new_token(t_env *env)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	token->env = env;
	return (token);
}

int	token_size(t_token *token)
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

void	assign_redir_type(t_token *token)
{
	if (token->str[0] == '>' && token->str[1] == '>')
		token->type = APPOUTREDIR;
	else if (token->str[0] == '>')
		token->type = OUTREDIR;
	if (token->str[0] == '<' && token->str[1] == '<')
		token->type = HEREDOC;
	else if (token->str[0] == '<')
		token->type = INREDIR;
}
