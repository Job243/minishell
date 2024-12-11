/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:46:25 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/11 17:18:41 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmd(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token)
	{
		while (token->str[i])
		{
			if (is_pipe(token->str[i]))
				count++;
			i++;
		}
		token = token->next;
	}
	return (count);
}

int	find_cmd(t_token *token, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token)
	{
		while (token->str)
		{
			if (is_pipe(token->str[i]))
				break ;
			if ((!is_space(token->str[i]) && !is_separators(token->str[i])) && (is_space(token->str[i + 1]) || is_separators(token->str[i + 1] || token->str[i + 1] == '\0')))
				j++;
			if (is_separators(token->str[i]) && (!is_separators(token->str[i + 1])))
			i++;
		}
	}
	cmd->tab = (char **)malloc(sizeof(char *) * (j + 1));
	if (!cmd->tab)
		return (0);
	return (i);
}

void	copy_cmd(t_token *token, t_cmd *cmd)
{
	int	i;
	int	len_cmd;

	i = 0;
	while (token)
	{

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
			cmd = new_cmd(i);
		else
			ft_lstadd_back_cmd(&cmd, new_cmd(i));
		i++;
	}
	find_cmd(token, cmd);
	return (cmd);
}
