/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/12/04 19:36:33 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

char	**word_split(char *ptr)
{
	char	**ws;
	int		count;
	int		wc;
	int		i;
	int		end_w;

	count = count_word(ptr);
	ws = gc(ft_calloc(sizeof(char *), (count + 1)));
	if (!ws)
		exit (1);
	i = 0;
	wc = 0;
	while (wc < count)
	{
		while (ptr[i] && ft_isspace(ptr[i]))
			i++;
		end_w = i;
		while (ptr[end_w] && !ft_isspace(ptr[end_w]))
				end_w++;
		ws[wc] = ft_substr(ptr, i, end_w - i);
		i = end_w;
		wc++;
	}
	return (ws);
}

char	*expand_env_val(t_data *data, char *var)
{
	char	*env_val;
	int		var_len;
	int		i;

	env_val = NULL;
	var_len = ft_strlen(var) + 1;
	if (ft_streq("?", var))
		env_val = gc(ft_itoa(g_sig));
	else
	{
		i = -1;
		while (data->env[++i])
		{
			if (!ft_memcmp(var, data->env[i], ft_strlen(var)) \
			&& data->env[i][ft_strlen(var)] == '=')
			{
				env_val = gc(ft_substr(data->env[i], var_len, \
				ft_strlen(data->env[i]) - var_len));
				break ;
			}
		}
	}
	return (env_val);
}

t_tok	*manage_end_ws(t_data *data, t_tok *tk, t_tok *n_tk, int end_var)
{
	t_tok	*last_tk;
	int		len;

	last_tk = n_tk;
	while (last_tk->next)
		last_tk = last_tk->next;
	if (tk->value[end_var + 1])
	{
		if (last_tk == n_tk)
			return (n_tk);
		len = ft_strlen(last_tk->value);
		last_tk->value = rrange_str_join(last_tk->value, \
		gc(ft_substr(tk->value, end_var + 1, \
		ft_strlen(tk->value) - end_var - 1)));
		expand(data, last_tk, len);
	}
	return (n_tk);
}

t_tok	*manage_ws(char **ws, t_tok *tk, char *var, int start)
{
	t_tok	*lst_exp;
	t_tok	*current_tk;
	int		index;
	int		end_var;

	index = 0;
	lst_exp = NULL;
	end_var = start + ft_strlen(var);
	while (ws[index])
	{
		current_tk = add_token(&lst_exp, new_token());
		current_tk->op = NONE;
		current_tk->type = WORD;
		if (!index && start)
			current_tk->value = \
			rrange_str_join(gc(ft_substr(tk->value, 0, start)), ws[index]);
		else
			current_tk->value = gc(ft_strdup(ws[index]));
		index++;
	}
	return (lst_exp);
}
