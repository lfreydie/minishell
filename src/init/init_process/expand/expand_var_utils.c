/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/12/21 01:43:36 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

char	**word_split(char *ptr, int count)
{
	char	**ws;
	int		wc;
	int		i;
	int		end_w;

	ws = gc(ft_calloc(sizeof(char *), (count + 1)));
	i = 0;
	wc = 0;
	while (wc < count)
	{
		while (ptr[i] && ft_isspace(ptr[i]))
			i++;
		end_w = i;
		while (ptr[end_w] && !ft_isspace(ptr[end_w]))
				end_w++;
		ws[wc] = gc(ft_substr(ptr, i, end_w - i));
		i = end_w;
		wc++;
	}
	return (ws);
}

char	*expand_env_val(t_data *data, char *var)
{
	char	*env_val;

	if (!var)
		return (NULL);
	env_val = NULL;
	if (ft_streq("?", var))
		env_val = gc(ft_itoa(data->exit));
	else
		env_val = getenv(var);
	return (env_val);
}

t_tok	*manage_end_ws(t_data *data, t_tok *tk, t_tok *n_tk, int end_var)
{
	t_tok	*last_tk;
	char	*tmp;
	int		len;

	last_tk = n_tk;
	while (last_tk->next)
		last_tk = last_tk->next;
	if (tk->value[end_var + 1])
	{
		tmp = gc(ft_substr(tk->value, end_var + 1, \
		ft_strlen(tk->value) - (end_var + 1)));
		len = ft_strlen(last_tk->value);
		last_tk->value = rrange_str_join(last_tk->value, tmp);
		if (last_tk == n_tk)
			return (n_tk);
		expand(data, last_tk, len);
	}
	return (n_tk);
}

t_tok	*manage_ws(char **ws, t_tok *tk, int start)
{
	t_tok	*lst_exp;
	t_tok	*current_tk;
	char	*tmp;
	int		index;

	index = -1;
	lst_exp = NULL;
	while (ws[++index])
	{
		current_tk = add_token(&lst_exp, new_token());
		current_tk->op = NONE;
		current_tk->type = WORD;
		if (!index && start)
		{
			tmp = gc(ft_substr(tk->value, 0, start));
			current_tk->value = rrange_str_join(tmp, ws[index]);
		}
		else
			current_tk->value = ws[index];
	}
	return (lst_exp);
}
