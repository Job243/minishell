/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:17:04 by ijabir            #+#    #+#             */
/*   Updated: 2024/12/27 22:52:01 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_check_convert(const char c, va_list args, int fd)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_print_char(va_arg(args, int), fd);
	else if (c == 's')
		i += ft_print_str(va_arg(args, char *), fd);
	else if (c == 'p')
		i += ft_print_ptr(va_arg(args, void *), fd);
	else if (c == 'i' || c == 'd')
		i += ft_print_str2(ft_itoa(va_arg(args, int)), fd);
	else if (c == 'u')
		i += ft_print_str2(ft_itoa2(va_arg(args, unsigned int)), fd);
	else if (c == 'x')
		i += ft_hexa(va_arg(args, unsigned int), fd);
	else if (c == 'X')
		i += ft_hexa_up(va_arg(args, unsigned int), fd);
	else if (c == '%')
		i += ft_print_char('%', fd);
	return (i);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
			len += write(fd, &str[i], 1);
		else
		{
			len += ft_check_convert(str[i + 1], args, fd);
			i++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
