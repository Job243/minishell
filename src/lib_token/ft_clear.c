/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijabir <ijabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:51:09 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/21 20:50:46 by ijabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->str)
			free(token->str);
		token->env = NULL;
		free(token);
		token = tmp;
	}
}

void	ft_clear_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		if (redir->fd != -1)
			close(redir->fd);
		if (redir->hdoc_name)
		{
			unlink(redir->hdoc_name);
			free(redir->hdoc_name);
		}
		free(redir);
		redir = tmp;
	}
}

void	ft_clear_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	while (cmd)
	{
		i = 0;
		ft_clear_redir(cmd->redir);
		tmp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->tab)
		{
			while (cmd->tab[i])
			{
				free(cmd->tab[i]);
				i++;
			}
			free(cmd->tab);
		}
		free(cmd);
		cmd = tmp;
	}
}

void	ft_tabclear(char **tab)
{
	int	size;

	size = 0;
	if (!tab)
		return ;
	while (tab[size])
		size++;
	while (size)
	{
		free(tab[size]);
		size--;
	}
	free(tab[size]);
	free(tab);
}
