/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_csp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:16:40 by ijabir            #+#    #+#             */
/*   Updated: 2024/12/27 22:55:36 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_print_char(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_print_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_str2(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	free(str);
	return (i);
}

int	ft_print_ptr(void *ptr, int fd)
{
	unsigned long int	i;

	i = (unsigned long int)ptr;
	if (i == 0)
		return (write(fd, "(nil)", 5));
	write(fd, "0x", 2);
	return (2 + ft_hexa(i, fd));
}
