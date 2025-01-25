/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:56:51 by jmafueni          #+#    #+#             */
/*   Updated: 2025/01/24 00:50:17 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>
# define MALLOC_ERROR -1
# define PIPE_ERROR -2
# define FORK_ERROR -3
# define DUP_ERROR -4
# define WRITE_ERROR -5
# define EXECVE_ERROR -6

typedef enum e_type
{
	UNKNOW,
	PIPE,
	INREDIR,
	OUTREDIR,
	HEREDOC,
	APPOUTREDIR,
	WORD,
}					t_type;

typedef struct s_env
{
	char			*var;
	int				printed;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	int		cmd_count;
	int		status;
	int		**fd_pipe;
	int		fd_in;
	int		fd_out;
	t_env	**my_env;
	t_env	**export_env;
	char	**env_tab;
	char	**path_tab;
	bool	sigint;
	bool	sigquit;
	pid_t	*process;
}			t_data;

typedef struct s_redir
{
	char			*file;
	char			*hdoc_name;
	int				fd;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**tab;
	t_redir			*redir;
	int				exit_status;
	int				is_empty_cmd;
	int				empty_var;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*str;
	t_type			type;
	int				empty_var;
	t_env			*env;
	struct s_token	*next;
}					t_token;

extern volatile sig_atomic_t	g_recu;

char				*ft_strndup(const char *s, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

int					double_redir(char *s);
int					error_pipe(char *s, int flag);
int					error_redir(char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					inside_quotes(char *s);
int					is_empty(char *s);
int					is_pipe(char c);
int					is_quote(char c);
int					is_redir(char c);
int					is_space(char c);
int					countwords(char *s);
int					parse_error(char *s);
int					quotes_closed(char *s);
int					is_separators(char c);
int					token_size(t_token *token);

t_token				*ft_lstlast(t_token *token);
t_token				*get_token(char *s, t_env *env);
t_token				*new_token(t_env *env);

int					ft_lstadd_back(t_token **token, t_token *new);
void				assign_redir_type(t_token *token);
void				check_parse_error(int parse, t_data *data);
void				ft_clear_token(t_token *token);

/*lst_cmd*/
int					check_cmd_malloc(t_token *token, t_cmd *cmd);
int					count_cmd(t_token *token);
int					count_word_for_cmd(t_token *token);

t_cmd				*ft_lstlast_cmd(t_cmd *cmd);
t_cmd				*get_cmd(t_token *token);
t_cmd				*new_cmd(void);

void				mark_quotes(t_token *token);
int					remove_quotes(t_token *token);
int					ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new);
void				ft_clear_cmd(t_cmd *cmd);

/*lst_redir*/
int					count_redir(t_token *token);
int					check_redir(t_redir *redir);

t_redir				*ft_lstlast_redir(t_redir *redir);
t_redir				*get_redir(t_token *token);
t_redir				*new_redir(void);

void				print_cmd(t_cmd *cmd, t_redir *redir);
void				fill_redir(t_token *token, t_redir *redir);
int					ft_lstadd_back_redir(t_redir **redir, t_redir *new);
void				ft_clear_redir(t_redir *redir);

/* utils*/
size_t				ft_strlen(const char *str);
size_t				ft_strlen_quote(const char *str);
size_t				ft_strlcpy(char *des, const char *src, size_t size);

void				expd_question(t_token *token,
						int dollar_pos, int question_pos, int exit);
char				*ft_strjoin(char const *s1, char const *s2);
char				*get_home(t_env *env);

int					check_home(t_data *data);
int					fill_data_pipe(t_data *data);
int					find_dollar(char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_lstaddback_env(t_env **env, t_env *new);
int					has_quote(char *str);

void				clear_array(int **array);
void				clear_all_tabs(t_cmd *cmd, t_data *data);
void				delete_var(t_env *to_delete, t_env **my_env);
void				index_cmd(t_cmd *cmd);
void				ft_clear_env(t_env *env);
void				ft_tabclear(char **tab);

/*signal*/
void				change_signal_status(t_data *data, t_cmd *cmd);
void				if_sigint(int sig);
void				print_signals(t_data *data);
void				set_child_signals(void);
void				set_exec_parent_signals(void);
void				set_parent_signals(void);
void				set_status_if_signal(t_data *data);

/*fd*/
int					check_fd(t_redir *redir);
int					get_inredir(t_cmd *cmd, t_data *data, int process_number);
int					get_outredir(t_cmd *cmd, t_data *data, int process_number);
int					open_files(t_cmd *cmd, t_data *data);

void				close_cmd_fds(t_cmd *cmd, int fd_in, int fd_out);
void				close_fds(t_data *data, int process_number);
void				close_fd_pipe(t_data *data, int i);
void				close_remaining_fds(t_data *data, int process_number);
void				get_command(t_cmd *cmd, t_data *data);
void				pipex(t_cmd *cmd, t_data *data, char *input, int index);

/*hdoc*/
int					get_hdoc(int fd, char *delimiter, t_data *data);

void				create_hdoc_file(t_redir *redir);

/*env*/
int					check_question_mark(char *str);
int					check_variable(t_token **token, int exit);
int					count_word_after_exp(char *str);
int					fill_temp_token(t_token *new_lst, char *str);
int					ft_lstsize(t_env *lst);

char				*get_variable_name(char *str);
char				**get_env_tab(t_env *my_env);

t_env				*copy_env(void);
t_env				*find_var_in_env(char *var, t_env *my_env);
t_env				*new_env(char *var);

t_token				*split_expand(t_token **token, t_token *temp);

void				error_expand(t_token *token, char *var_name);
void				expand_var2(t_token *token, int dollar, char *var,
						char **new);

/*buitins*/
int					is_a_path(char *cmd);
int					is_builtin(char *cmd);
int					set_up_data(t_data *data, t_cmd *cmd);

void				actualise_env(t_env *env, char *var);
void				change_oldpwd_env(char *oldpwd, t_env *env);
void				check_path_content(char *path);
void				exec_buildin_child(t_cmd *start, t_cmd *cmd,
						t_data *data, int process);
void				exec_buildin_parent(t_cmd *start, t_cmd *cmd, t_data *data);
void				exec_cd(t_cmd *cmd, t_data *data);
void				exec_cd_empty(t_data *data, t_cmd *cmd);
void				exec_echo(t_cmd *cmd, t_data *data);
void				exec_env(t_env *my_env);
void				exec_exit(t_cmd *start, t_cmd *cmd, t_data *data);
int					exec_export(t_cmd *cmd, t_data *data);
void				exec_pwd(void);
void				exec_unset(t_cmd *cmd, t_data *data);
void				exit_pipex_child(t_cmd *cmd, t_data *data,
						int process, int error_code);
void				reset_env_print(t_env *env);

#endif
