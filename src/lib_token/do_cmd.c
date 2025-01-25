/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:46:25 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/21 21:21:25 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	fonction qui compte les words et les redirs d'une commande
*/

void	extract_token_to_cmd(char *s, t_cmd *cmd)
{
	cmd->cmd = ft_strndup(s, ft_strlen(s));
	if (!cmd->cmd)
		return ;
	cmd->is_empty_cmd = 0;
	cmd->tab[0] = ft_strndup(s, ft_strlen(s));
	if (!cmd->tab[0])
		return ;
	cmd->tab[1] = NULL;
}

void	extract_token_to_cmd2(char *s, t_cmd *cmd)
{
	int	j;

	j = 0;
	while (cmd->tab[j])
		j++;
	cmd->tab[j] = ft_strndup(s, ft_strlen(s));
	if (!cmd->tab[j])
		return ;
	cmd->tab[j + 1] = NULL;
}

int	fill_cmd(t_token *token, t_cmd *cmd)
{
	int	word;

	word = 0;
	while (token)
	{
		if (token->type > 1 && token->type < 6 && !cmd->redir)
		{
			cmd->redir = get_redir(token);
			if (!cmd->redir)
				return (0);
		}
		if (token->type == WORD)
			word++;
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	cmd->tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!cmd->tab)
		return (0);
	cmd->tab[0] = NULL;
	return (1);
}

void	copy_cmd(t_token *token, t_cmd *cmd)
{
	while (token && cmd)
	{
		if (!fill_cmd(token, cmd))
			break ;
		while (token && token->type != WORD && token->type != PIPE)
			token = token->next;
		if (!token || token->type == PIPE)
			cmd->cmd = ft_strndup("\0", 0);
		if (!token)
			break ;
		if (token->type == WORD)
		{
			cmd->empty_var = token->empty_var;
			extract_token_to_cmd(token->str, cmd);
			while (token && token->type != PIPE)
			{
				token = token->next;
				if (token && token->type == WORD)
					extract_token_to_cmd2(token->str, cmd);
			}
		}
		cmd = cmd->next;
		if (token)
			token = token->next;
	}
}

t_cmd	*get_cmd(t_token *token)
{
	int		i;
	int		cmd_count;
	t_cmd	*cmd;

	i = 0;
	cmd_count = count_cmd(token);
	while (i < cmd_count)
	{
		if (i == 0)
			cmd = new_cmd();
		else if (!cmd || !ft_lstadd_back_cmd(&cmd, new_cmd()))
		{
			ft_clear_cmd(cmd);
			return (NULL);
		}
		i++;
	}
	copy_cmd(token, cmd);
	if (!check_cmd_malloc(token, cmd))
		return (NULL);
	return (cmd);
}
