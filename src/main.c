/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:10:21 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/10 14:50:00 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	parsing(char *input)
{
	t_token	*a;
	// if (!token)
	// 	return (0);
	// if (!analyse)
	// 	return (0);
	// if (!quote)
	// 	return (0);
	// if (!arg)
	// 	return (0);
	add_history(input);
	if (!parse_error(input))
		return (0);
	a = get_token(input);
	if (!a)
		return (0);

	// printf("%p\n", a);
	printtoken(a);

	ft_clear_token(a);
	return (1);
}
void	handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

// t_redir create redir()

// {
// 	sefjadfadasf;

// }

int	main(int ac, char **av)
{
	char	*str;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);

	while (1)
	{
		// free(token);
		str = readline("minishell> ");
		if (str == NULL)
			break;
		if (!parsing(str))
			continue;
		// if (!exec())
		// 	break ;
		else
			continue ;
	}
	return (0);
}

