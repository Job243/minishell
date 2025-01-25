/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:10:21 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/23 23:38:30 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_recu = 0;

void	exec_command(t_data *data, t_cmd *cmd, char *input)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		pipex(cmd, data, input, i);
		i++;
	}
	close_fd_pipe(data, 0);
	close_cmd_fds(cmd, 0, 0);
	i = -1;
	while (++i < data->cmd_count)
	{
		if (waitpid(data->process[i], &data->status, 0) == -1)
			continue ;
		change_signal_status(data, cmd);
	}
}

t_cmd	*get_cmd_from_token(t_env *my_env, char *input, int exit_status)
{
	t_token	*token;
	t_cmd	*cmd;

	token = get_token(input, my_env);
	if (!token)
		return (NULL);
	if (!check_variable(&token, exit_status))
		return (NULL);
	if (!token)
		return (NULL);
	if (!remove_quotes(token))
		return (NULL);
	cmd = get_cmd(token);
	ft_clear_token(token);
	return (cmd);
}

void	minishell(char *input, t_data *data)
{
	t_cmd		*cmd;
	int			parse;

	add_history(input);
	parse = parse_error(input);
	if (parse <= 0)
		return (check_parse_error(parse, data));
	cmd = get_cmd_from_token(*data->my_env, input, data->status);
	if (!cmd)
		return ;
	index_cmd(cmd);
	if (!set_up_data(data, cmd))
		return (ft_clear_cmd(cmd));
	if (!open_files(cmd, data))
		return (print_signals(data), close_fd_pipe(data, 0),
			clear_all_tabs(cmd, data));
	set_exec_parent_signals();
	exec_command(data, cmd, input);
	print_signals(data);
	clear_all_tabs(cmd, data);
	return ;
}

void	loop_minihell(t_data *data)
{
	char	*str;

	while (1)
	{
		data->sigint = 0;
		data->sigquit = 0;
		g_recu = 0;
		set_parent_signals();
		str = readline("minishell> ");
		if (g_recu != 0)
		{
			set_status_if_signal(data);
			continue ;
		}
		if (str == NULL)
			break ;
		minishell(str, data);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_env	*my_env;
	t_env	*export_env;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	my_env = copy_env();
	if (!my_env)
		return (MALLOC_ERROR);
	export_env = copy_env();
	if (!export_env)
		return (ft_clear_env(my_env), MALLOC_ERROR);
	data.my_env = &my_env;
	data.export_env = &export_env;
	loop_minihell(&data);
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_clear_env(my_env);
	ft_clear_env(export_env);
	return (0);
}
