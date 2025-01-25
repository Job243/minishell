/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:39:30 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/27 22:52:45 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	print_char_with_index(unsigned int index, char *c)
{
	printf("Index %u : %c\n", index, *c);
}

int	main(void)
{
	char	str[] = "Hello, World!";

	ft_striteri(str, print_char_with_index);
	return (0);
}*/
