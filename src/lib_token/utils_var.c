/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:33:58 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/10 18:15:54 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd_malloc2(t_cmd *cmd, int word_count, int redir_count)
{
	int		i;
	int		j;
	t_redir	*temp;

	i = 0;
	j = 0;
	temp = cmd->redir;
	while (cmd->tab[i])
		i++;
	while (temp)
	{
		if (!temp->file)
			break ;
		j++;
		temp = temp->next;
	}
	if (i != word_count || j != redir_count)
	{
		ft_clear_cmd(cmd);
		return (0);
	}
	return (1);
}

int	check_cmd_malloc(t_token *token, t_cmd *cmd)
{
	int	word_count;
	int	redir_count;

	while (cmd)
	{
		word_count = 0;
		redir_count = 0;
		if (!cmd->cmd || !cmd->tab)
			return (ft_clear_cmd(cmd), 0);
		while (token && token->type != PIPE)
		{
			if (token->type == WORD)
				word_count++;
			else
				redir_count++;
			token = token->next;
		}
		if (!check_cmd_malloc2(cmd, word_count, redir_count))
			return (0);
		if (token)
			token = token->next;
		cmd = cmd->next;
	}
	return (1);
}

int	ft_isalpha(int c)
{
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
		return (1);
	return (0);
}

int	count_cmd(t_token *token)
{
	int	cmd;

	cmd = 1;
	while (token)
	{
		if (token->type == PIPE)
			cmd++;
		token = token->next;
	}
	return (cmd);
}

int	find_dollar(char *str)
{
	int	i;
	int	squote_flag;

	squote_flag = 0;
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == -34)
			squote_flag = !squote_flag;
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])
				|| str[i + 1] == '?') && !squote_flag)
			return (i + 1);
		i++;
	}
	return (0);
}
