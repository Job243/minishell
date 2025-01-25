/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:39:14 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/27 22:52:40 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*dup;

	size = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*int	main(void)
{
	char	str[] = "abcde45fv465v ajb v";

	printf("%s\n", strdup(str));
	printf("%s\n", ft_strdup(str));
}*/
