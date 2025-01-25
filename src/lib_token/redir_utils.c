/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:46:54 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/15 19:31:43 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstadd_back_redir(t_redir **redir, t_redir *new)
{
	if (!redir || !new)
		return (0);
	if (*redir)
		ft_lstlast_redir(*redir)->next = new;
	else
		*redir = new;
	return (1);
}

t_redir	*ft_lstlast_redir(t_redir *redir)
{
	while (redir && redir->next)
		redir = redir->next;
	return (redir);
}

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	ft_memset(redir, 0, sizeof(t_redir));
	redir->fd = -1;
	return (redir);
}

int	check_redir(t_redir *redir)
{
	if (!redir)
		return (0);
	while (redir)
	{
		if (!redir->file)
			return (0);
		redir = redir->next;
	}
	return (1);
}

void	print_cmd(t_cmd *cmd, t_redir *redir)
{
	int	i;

	while (cmd)
	{
		i = 0;
		printf("Commande = %s\n", cmd->cmd);
		printf("Commande arg :\n");
		while (cmd->tab[i])
		{
			printf("%s\n", cmd->tab[i]);
			i++;
		}
		printf("Commande redir :\n");
		redir = cmd->redir;
		while (redir)
		{
			printf("%s\n", redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
