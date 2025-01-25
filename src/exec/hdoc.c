/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:13 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/23 19:14:33 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	return (0);
}

int	end_hdoc(char *line, char *delimiter)
{
	if (line == NULL)
	{	
		printf("bash: warning: here-document delimited by end-of-file\n");
		return (1);
	}
	if (is_delimiter(line, delimiter))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	get_hdoc(int fd, char *delimiter, t_data *data)
{
	char	*line;
	int		save;

	save = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_recu != 0)
			break ;
		if (end_hdoc(line, delimiter))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (close(save), 0);
		}
		free(line);
		if (write(fd, "\n", 1) == -1)
			return (close(save), 0);
	}
	set_status_if_signal(data);
	if (data->status == 130)
		return (close(save), 0);
	return (close(save), 1);
}

void	create_hdoc_file(t_redir *redir)
{
	static int	i = 0;
	char		*hdoc_number;

	hdoc_number = ft_itoa(i);
	if (!hdoc_number)
		return ;
	redir->hdoc_name = ft_strjoin("/tmp/here_doc", hdoc_number);
	free(hdoc_number);
	i++;
}
