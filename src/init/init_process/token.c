/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:04:37 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/19 10:32:58 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*new_token(void)
{
	t_tok	*new_tk;

	new_tk = gc(ft_calloc(sizeof(t_tok), 1));
	return (new_tk);
}

t_tok	*add_token(t_tok **lst_tk, t_tok *new_tk)
{
	t_tok	*tmp;

	if (lst_tk)
	{
		if (!*lst_tk)
			*lst_tk = new_tk;
		else
		{
			tmp = *lst_tk;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = new_tk;
		}
	}
	return (new_tk);
}

char	*get_word_value(t_data *data, char *ptr)
{
	char	*value;
	char	quote;
	int		i;

	i = 0;
	while (ptr && ptr[i] && !ft_strchr(METACHARACTERS, ptr[i]))
	{
		if (ptr[i] == SINGLE_QUOTE || ptr[i] == DOUBLE_QUOTE)
		{
			quote = ptr[i++];
			while (ptr[i] && ptr[i] != quote)
				i++;
			if (!ptr[i])
				return (ft_err_syntax(data, SHELL, UNQUOTE, NULL), NULL);
		}
		i++;
	}
	value = gc(ft_substr(ptr, 0, i));
	return (value);
}

int	token_data(t_data *data, char *ptr, t_tok *tk, char **grammar)
{
	if (!*ptr)
		tk->op = NWLINE;
	while (*ptr && tk->op != NONE)
	{
		tk->value = grammar[tk->op];
		if (!ft_strncmp(ptr, tk->value, ft_strlen(tk->value)))
			break ;
		tk->op++;
	}
	if (tk->op == IN_RED || tk->op == HEREDOC_RED || tk->op == OUTTR_RED
		|| tk->op == OUTAP_RED)
		tk->type = RED_OP;
	else if (tk->op != NONE)
		tk->type = CTRL_OP;
	else
		tk->type = WORD;
	if (tk->op == NWLINE)
		tk->value = S_NEWLINE;
	else if (tk->op == NONE)
		tk->value = get_word_value(data, ptr);
	if (!tk->value)
		return (FAILED);
	return (SUCCESS);
}

int	tokenize_input(t_data *data)
{
	t_tok	*tk;
	char	*ptr;

	tk = NULL;
	ptr = data->line;
	while (!tk || tk->op != NWLINE)
	{
		while (*ptr == SPACE)
			ptr++;
		tk = add_token(&data->lst_tk, new_token());
		if (token_data(data, ptr, tk, data->grammar) == -1)
			return (FAILED);
		ptr += ft_strlen(tk->value);
	}
	return (SUCCESS);
}
