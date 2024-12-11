/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:56:51 by jmafueni          #+#    #+#             */
/*   Updated: 2024/12/11 21:35:27 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# define ERR_MALLOC -3

typedef enum e_joba
{
	UNKNOW,
	PIPE,
	INREDIR,
	OUTREDIR,
	HEREDOC,
	APPOUTREDIR,
	WORD,
}					e_job;

typedef struct s_redir
{
	char			*redir;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**tab;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*str;
	int				token_id;
	e_job			type;
	struct s_token	*next;
}					t_token;

// typedef struct s_ilias
// {
// 	t_token	*token;
// } t_ilias;

char				*ft_strndup(const char *s, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

int					double_redir(char *s);
int					error_pipe(char *s);
int					error_redir(char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					inside_quotes(char *s);
int					is_empty(char *s);
int					is_pipe(char c);
int					is_quote(char c);
int					is_redir(char c);
int					is_space(char c);
int					countwords(char *s);
int					len_trimquote(char *s);
int					parse_error(char *s);
int					quote_checking(char *s);
int					quotes_closed(char *s);
int					is_separators(char c);
int					token_size(t_token *token);

t_token				*ft_lstlast(t_token *token);
t_token				*get_token(char *s);
t_token				*new_token(int n);

int					ft_lstadd_back(t_token **token, t_token *new);
void				ft_clear_token(t_token *token);
void				printtoken(t_token *token);

/*lst_cmd*/
int					count_cmd(t_token *token);
int					cmd_size(t_cmd *cmd);

t_cmd				*ft_lstlast_cmd(t_cmd *cmd);
t_cmd				*get_cmd(t_token *token);
t_cmd				*new_cmd(int n);

void				ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new);
void				ft_clear_cmd(t_cmd *cmd);

#endif
