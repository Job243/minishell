/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:13:12 by ijabir            #+#    #+#             */
/*   Updated: 2025/01/24 00:35:02 by jmafueni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit(char *str, char *new_str, int dollar_pos, int exit)
{
	char	*str_exit;
	char	*temp;
	char	*new;

	str_exit = ft_itoa(exit);
	if (!str_exit)
		return (free(new_str), NULL);
	new = ft_strjoin(new_str, str_exit);
	free(str_exit);
	free(new_str);
	if (!new)
		return (NULL);
	temp = new;
	new = ft_strjoin(new, &str[dollar_pos + 1]);
	free(temp);
	return (new);
}

void	expand_var(t_token *token, int exit)
{
	int		dollar_pos;
	int		question_pos;
	char	*variable_name;
	char	*new_str;

	dollar_pos = find_dollar(token->str);
	if (!dollar_pos)
		return ;
	question_pos = check_question_mark(&token->str[dollar_pos]);
	if (question_pos >= 0)
		return (expd_question(token, dollar_pos, question_pos, exit));
	variable_name = get_variable_name(&token->str[dollar_pos]);
	if (!variable_name)
		return (error_expand(token, variable_name));
	new_str = malloc(sizeof(char) * (dollar_pos));
	if (!new_str)
		return (error_expand(token, variable_name));
	ft_strlcpy(new_str, token->str, dollar_pos);
	expand_var2(token, dollar_pos, variable_name, &new_str);
	free(variable_name);
	free(token->str);
	token->str = new_str;
	if (find_dollar(new_str))
		return (expand_var(token, exit));
}

void	expd_question(t_token *token, int dollar, int question, int exit)
{
	char	*new_str;
	char	*temp;

	new_str = malloc(dollar);
	if (!new_str)
		return ;
	ft_strlcpy(new_str, token->str, dollar);
	temp = new_str;
	if (!question)
		new_str = expand_exit(token->str, new_str, dollar, exit);
	else
	{
		new_str = ft_strjoin(new_str, &token->str[dollar + question]);
		free(temp);
	}
	free(token->str);
	token->str = new_str;
	if (find_dollar(new_str))
		return (expand_var(token, exit));
}

t_token	*delete_empty_var(t_token **token, t_token *to_delete)
{
	t_token	*temp;

	free(to_delete->str);
	if (to_delete == (*token))
	{
		(*token) = (*token)->next;
		free(to_delete);
		return ((*token));
	}
	temp = (*token);
	while (temp->next != to_delete)
		temp = temp->next;
	temp->next = to_delete->next;
	free(to_delete);
	return (temp);
}

int	check_variable(t_token **token, int exit)
{
	t_token	*temp;

	temp = *token;
	mark_quotes(temp);
	while (temp)
	{
		if (find_dollar(temp->str))
		{
			expand_var(temp, exit);
			if (!temp->str)
				return (ft_clear_token(temp), 0);
			temp = split_expand(token, temp);
			if (!temp)
				return (ft_clear_token(*token), 0);
		}
		if (!temp->str[0] && temp->next)
			temp = delete_empty_var(token, temp);
		else if (!temp->str[0])
			temp->empty_var = 1;
		temp = temp->next;
	}
	return (1);
}
