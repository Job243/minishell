/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:20 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/15 19:31:51 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new)
{
	if (!cmd || !new)
		return (0);
	if (*cmd)
		ft_lstlast_cmd(*cmd)->next = new;
	else
		*cmd = new;
	return (1);
}

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->is_empty_cmd = 1;
	return (cmd);
}
