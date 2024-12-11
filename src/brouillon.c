/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:50:03 by jmafueni          #+#    #+#             */
/*   Updated: 2024/11/19 18:51:33 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
void	print_context(char *str, int fd);
void	ft_free_tab(char **tab);
char	**get_path(char **env);
char	*build_and_search(char **path, char *cmd);
char	*set_cmd(char **path, char *cmd);
void	exec_cmd(char *cos, char **path, char **env);
int		open_infile(char *f_in, int fd_out);
int		write_outfile(int read_var, char *path_outfile);
int		check_fork(int *fd);
int		child_one(int *fd, char *path_infile, char *cmd, char **path);
int		next_child(int *fd, char *path_outfile, char *cmd, char **path);
void	end_of_process(int *fd, char **path);

int	write_outfile(int read_var, char *outfile)
{
	int	out_file;

	out_file = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (out_file == -1)
	{
		if (access(outfile, F_OK) == -1)
			print_context("Outfile : No such file or directory\n", 2);
		else if (access(outfile, W_OK) == -1)
			print_context("Outfile : Permission denied\n", 2);
		return (0);
	}
	if (dup2(read_var, STDIN_FILENO) == -1)
	{
		print_context("Error dup2 in to write outfile\n", 2);
		close(out_file);
		return (0);
	}
	if (dup2(out_file, STDOUT_FILENO) == -1)
	{
		print_context("Error dup2 out to write file\n", 2);
		close(out_file);
		return (0);
	}
	close(out_file);
	return (1);
}

int	check_fork(int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit (0);
	}
	return (pid);
}

int	child_one(int *fd, char *path_infile, char *cmd, char **path)
{
	int	check;

	close(fd[0]);
	check = open_infile(path_infile, fd[1]);
	close(fd[1]);
	if (check != 0)
		exec_cmd(cmd, path, NULL);
	if (check != 1)
		ft_free_tab(path);
	exit (1);
}

int	next_child(int *fd, char *path_outfile, char *cmd, char **path)
{
	int	check;

	close(fd[1]);
	check = write_outfile(fd[0], path_outfile);
	close(fd[0]);
	if (check != 0)
		exec_cmd(cmd, path, NULL);
	if (check != 1)
		ft_free_tab(path);
	exit (1);
}

void	end_of_process(int *fd, char **path)
{
	close(fd[1]);
	close(fd[0]);
	wait(NULL);
	wait(NULL);
	ft_free_tab(path);
}

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
			{
				ft_free_tab(path);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (path);
}

char	*build_and_search(char **path, char *cmd)
{
	int		i;
	char	*parthial;
	char	*full;

	i = 0;
	while (path && path[i])
	{
		parthial = ft_strjoin(path[i], "/");
		if (!parthial)
		{
			free(parthial);
			return (NULL);
		}
		full = ft_strjoin(parthial, cmd);
		free(parthial);
		if (!full)
			return (NULL);
		i++;
		if (access(full, X_OK) != -1)
			return (full);
		free(full);
	}
	return (NULL);
}

char	*set_cmd(char **path, char *cmd)
{
	char	*ret;

	if (cmd == NULL)
	{
		print_context("Command not found\n", 2);
		return (NULL);
	}
	if (access(cmd, X_OK) != -1)
		return (cmd);
	ret = build_and_search(path, cmd);
	if (ret)
		return (ret);
	print_context("Command not found\n", 2);
	return (ret);
}

void	exec_cmd(char *cos, char **path, char **env)
{
	char	**scos;
	char	*cmd;

	scos = ft_split(cos, ' ');
	if (!scos)
		return ;
	cmd = set_cmd(path, scos[0]);
	if (!cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	if (cmd)
		execve(cmd, scos, env);
	free(cmd);
	ft_free_tab(path);
	ft_free_tab(scos);
}

int	open_infile(char *f_in, int fd_out)
{
	int	fdin;

	fdin = open(f_in, O_RDONLY);
	if (fdin == -1)
	{
		if (access(f_in, F_OK) == -1)
			print_context("Infile : No such file or directory\n", 2);
		else if (access(f_in, R_OK) == -1)
			print_context("Infile : Permission denied\n", 2);
		return (0);
	}
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		print_context("Error dup2 in to openfile\n", 2);
		close(fdin);
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		print_context("Error dup2 out to openfile\n", 2);
		close(fdin);
		return (0);
	}
	close(fdin);
	return (1);
}

void	print_context(char *str, int fd)
{
	int	size;

	size = ft_strlen(str);
	write(fd, str, size);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	main(int nargs, char **args, char **env)
{
	char	**path;
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell > ");
		printf("%s\n", str);
		if (str == NULL)
			return 0;
		add_history(str);

		if (nargs - 1 != 4)
		{
			print_context("Error arguments\n", 2);
			return (0);
		}
		if (pipe(fd) == -1)
			exit (0);
		path = get_path(env);
		pid = check_fork(fd);
		if (pid == 0)
			child_one(fd, args[1], args[2], path);
		pid2 = check_fork(fd);
		if (pid2 == 0)
			next_child(fd, args[4], str, path);
		if (pid != 0)
		{
			end_of_process(fd, path);
		}
	}
	return (0);
}*/
