/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:17:07 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:29:07 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_pipex_child(t_cmd *cmd, t_data *data, int process, int error_code)
{
	int	exit_number;

	close_remaining_fds(data, process);
	if (error_code == EXECVE_ERROR)
	{
		if (is_a_path(cmd->cmd) && !access(cmd->cmd, F_OK))
		{
			exit_number = 126;
			if (!closedir(opendir(cmd->cmd)))
				ft_printf(2, "%s : est un dossier\n", cmd->cmd);
		}
		else if (!cmd->empty_var
			&& (!cmd->redir || cmd->redir->type != HEREDOC))
			exit_number = 127;
		else
			exit_number = 0;
	}
	clear_all_tabs(cmd, data);
	clear_array(data->fd_pipe);
	ft_clear_env(*(data->my_env));
	ft_clear_env(*(data->export_env));
	if (error_code == EXECVE_ERROR)
		exit(exit_number);
	exit(error_code);
}

void	manage_fd_child(t_data *data, t_cmd *cmd, t_cmd *start, int process)
{
	data->fd_in = get_inredir(cmd, data, process);
	data->fd_out = get_outredir(cmd, data, process);
	close_fds(data, process);
	close_cmd_fds(start, data->fd_in, data->fd_out);
	if (data->fd_in > 0)
	{
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			exit_pipex_child(start, data, process, DUP_ERROR);
		close(data->fd_in);
	}
	if (data->fd_out != 1 && data->fd_out != -1)
	{
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			exit_pipex_child(start, data, process, DUP_ERROR);
		close(data->fd_out);
	}
}

void	child_process(t_cmd *cmd, t_data *data, int process_number)
{
	t_cmd	*start;

	start = cmd;
	set_child_signals();
	while (cmd->index != process_number)
		cmd = cmd->next;
	manage_fd_child(data, cmd, start, process_number);
	get_command(cmd, data);
	if (!cmd->cmd)
		exit_pipex_child(start, data, process_number, MALLOC_ERROR);
	if (is_builtin(cmd->cmd) && data->fd_in != -1 && data->fd_out != -1)
		exec_buildin_child(start, cmd, data, process_number);
	if (data->fd_in != -1 && data->fd_out != -1)
		execve(cmd->cmd, cmd->tab, data->env_tab);
	exit_pipex_child(start, data, process_number, EXECVE_ERROR);
}

void	parent_process(t_cmd *cmd, t_data *data, char *input, int index)
{
	t_cmd	*start;

	(void)input;
	start = cmd;
	while (cmd->index != index)
		cmd = cmd->next;
	if (is_builtin(cmd->cmd))
		exec_buildin_parent(start, cmd, data);
}

void	pipex(t_cmd *cmd, t_data *data, char *input, int index)
{
	data->process[index] = fork();
	if (data->process[index] == -1)
		return ;
	if (!data->process[index])
		child_process(cmd, data, index);
	parent_process(cmd, data, input, index);
}
