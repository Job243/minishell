/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:20 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/10 15:54:06 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_cmd(t_cmd *cmd)
{// a revoir si pb de leak
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}


void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new)
{
	if (!cmd || !new)
		return ;
	if (*cmd)
		ft_lstlast(*cmd)->next = new;
	else
		*cmd = new;
}

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*new_cmd(int n)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir = NULL;
	cmd->tab = NULL;
	cmd->next = NULL;
	return (cmd);
}

int		cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

// void printcmd(t_cmd *cmd)
// {
// 	while(cmd)
// 	{
// 		printf("word is %s type is %d\n", cmd->str, cmd->type);
// 		cmd = cmd->next;
// 	}
// }
