/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijabir <ijabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:06:41 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/06 21:19:01 by ijabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word_for_cmd(t_token *token)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (token->str[i])
	{
		if (!is_space(token->str[i]) && (is_space(token->str[i + 1])
				|| token->str[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

int	count_redir(t_token *token)
{
	int	redir_count;

	redir_count = 0;
	while (token)
	{
		if (token->type == PIPE)
			break ;
		if (token->type > 1 && token->type < 6)
			redir_count++;
		token = token->next;
	}
	return (redir_count);
}
/*
	Fonction qui extrait le type des tokens_redir pour affilier par
	la suite les structures redirs et les remplir par le nom des fichier
	qui les suit.
*/

void	fill_redir(t_token *token, t_redir *redir)
{
	int	i;

	while (token && redir)
	{
		i = 0;
		if (token->type == PIPE)
			return ;
		if (token->type > 1 && token->type < 6)
		{
			redir->type = token->type;
			while (is_redir(token->str[i]))
				i++;
			while (is_space(token->str[i]))
				i++;
			redir->file = ft_strndup(token->str + i, ft_strlen(token->str) - i);
			if (!redir->file)
				return ;
			redir = redir->next;
		}
		token = token->next;
	}
}

t_redir	*get_redir(t_token *token)
{
	int		i;
	int		redir_count;
	t_redir	*redir;

	i = 0;
	redir = NULL;
	redir_count = count_redir(token);
	while (i < redir_count)
	{
		if (i == 0)
			redir = new_redir();
		else if (!redir || !ft_lstadd_back_redir(&redir, new_redir()))
		{
			ft_clear_redir(redir);
			return (NULL);
		}
		i++;
	}
	fill_redir(token, redir);
	if (!check_redir(redir))
		return (ft_clear_redir(redir), NULL);
	return (redir);
}
