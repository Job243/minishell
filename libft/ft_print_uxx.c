/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uxx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:17:22 by ijabir            #+#    #+#             */
/*   Updated: 2024/12/27 22:57:30 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	str_size2(unsigned int n)
{
	size_t	i;

	i = 0;
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa2(unsigned int n)
{
	int		size;
	char	*str;

	size = str_size2(n);
	str = malloc(size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	size--;
	while (size >= 0)
	{
		str[size] = '0' + n % 10;
		n /= 10;
		size--;
	}
	return (str);
}

int	ft_hexa(unsigned long int i, int fd)
{
	int	j;

	j = 0;
	if (i >= 16)
		j += ft_hexa(i / 16, fd);
	j++;
	write(fd, &"0123456789abcdef"[i % 16], 1);
	return (j);
}

int	ft_hexa_up(unsigned long int i, int fd)
{
	int	j;

	j = 0;
	if (i >= 16)
		j += ft_hexa_up(i / 16, fd);
	j++;
	write(fd, &"0123456789ABCDEF"[i % 16], 1);
	return (j);
}
