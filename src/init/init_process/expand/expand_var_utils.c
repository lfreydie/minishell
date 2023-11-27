/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/11/26 16:30:48 by lefreydier       ###   ########.fr       */
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

void	manage_ws(char **ws, t_tok *tk, int start)
{
	int		i;
	t_tok	*nxt_tk;
	t_tok	*current_tk;
	char	*n_ptr;
	char	*end_str;

	nxt_tk = tk->next;
	end_str = cpy_end_str(tk, start);
	current_tk = tk;
	while (ws[i])
	{
		if (i == 0)
		{
			if (start)
			{
				n_ptr = gc(ft_substr(current_tk->value, 0, start));
				tk->value = rrange_str_join(n_ptr, ws[i]);
			}
			else
			{
				tk->value = gc(ft_strdup(ws[i]));
				if (!tk->value)
					exit (1);
			}
		}
		else
		{
			current_tk->next = gc(ft_calloc(sizeof(t_tok), 1));
			if (!current_tk->next)
				exit (1);
			current_tk = current_tk->next;
			current_tk->type = WORD;
			current_tk->op = NONE;
			current_tk->value = gc(ft_strdup(ws[i]));
		}
		if (!ws[i + 1])
		{
			current_tk->next = nxt_tk;
			if (end_str)
				tk->value = rrange_str_join(n_ptr, ws[i]);
		}
	}
}
