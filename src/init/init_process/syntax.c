/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/26 15:02:31 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	(void)data; // error handles
	if (!prev_tk && tk->op == PIPE)
		exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
	if (prev_tk && prev_tk->op != NONE && tk->op != NONE)
	{
		if (prev_tk->type == RED_OP && tk->type == CTRL_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
		else if (prev_tk->type == RED_OP && tk->type == RED_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
		else if (prev_tk->type == CTRL_OP && tk->type == CTRL_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
	}
}

t_tok	*expand(t_tok *tk)
{
	char	quote;
	char	*ptr;
	int		i;

	i = 0;
	ptr = tk->value;
	if (ptr[i] == SINGLE_QUOTE || ptr[i] == DOUBLE_QUOTE)
	{
		quote = ptr[i++];
		while (ptr[i] && ptr[i] != quote)
		{
			if (ptr[i] == '$' && quote == DOUBLE_QUOTE)
				i++; //expand_env_var
			i++;
		}
		if (!ptr[i])
			exit (1); // quote unclose
		tk->value = ft_substr(ptr, 1, (ft_strlen(ptr) - 2));
		free(ptr);
	}
	return (tk);
}
