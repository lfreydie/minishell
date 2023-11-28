/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/11/28 10:35:13 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

char	**word_split(char *ptr)
{
	char	**ws;
	int		len_ptr;
	int		count;
	int		wc;
	int		i;

	len_ptr = ft_strlen(ptr);
	count = count_word(ptr);
	ws = gc(ft_calloc(sizeof(char *), (count + 1)));
	if (!ws)
		exit (1);
	i = 0;
	wc = 0;
	while (wc < count)
	{
		while (!ptr[i] && i < len_ptr)
			i++;
		if (i >= len_ptr)
			exit (1);
		ws[i] = ft_strdup(ptr + i);
		i += ft_strlen(ptr + i);
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
			if (!ft_memcmp(var, data->env[i], ft_strlen(var) - 1) \
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
		if (!index && start)
			current_tk->value = \
			rrange_str_join(gc(ft_substr(tk->value, 0, start)), ws[index]);
		else
			current_tk->value = gc(ft_strdup(ws[index]));
		index++;
	}
	if (tk->value[end_var + 1])
		current_tk->value = rrange_str_join(gc(ft_substr(tk->value, \
		end_var + 1, ft_strlen(tk->value) - end_var - 1)), current_tk->value);
	current_tk->next = tk->next;
	return (lst_exp);
}
