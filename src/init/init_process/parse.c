/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:08:37 by bberthod          #+#    #+#             */
/*   Updated: 2023/12/02 12:38:33 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*add_cmd(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	last_cmd = data->lst_cmd;
	data->num_cmd++;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	new_cmd = gc(ft_calloc(sizeof(t_cmd), 1));
	if (!new_cmd)
		exit(1); // code erreur
	new_cmd->id = data->num_cmd - 1;
	if (!last_cmd)
		data->lst_cmd = new_cmd;
	else
		last_cmd->next = new_cmd;
	return (new_cmd);
}

void	append_cmd(t_data *data, t_tok *tk, t_cmd *cmd)
{
	int		j;
	char	**n_cmd;
	int		current_size;

	(void) data;
	current_size = 0;
	while (cmd->cmd_value && cmd->cmd_value[current_size] != NULL)
		current_size++;
	n_cmd = gc(ft_calloc(sizeof(char *), current_size + 2));
	if (!n_cmd)
		exit(1); //code erreur
	j = 0;
	while (cmd->cmd_value && cmd->cmd_value[j])
	{
		n_cmd[j] = gc(ft_strdup(cmd->cmd_value[j]));
		j++;
	}
	n_cmd[j] = gc(ft_strdup(tk->value));
	j = -1;
	if (cmd->cmd_value)
	{
		while (cmd->cmd_value[++j])
			rm_node(cmd->cmd_value[j]);
		rm_node(cmd->cmd_value);
	}
	cmd->cmd_value = n_cmd;
}

void	parse_token(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*tk;
	t_tok	*prev_tk;
	t_tok	*tmp_tk;
	t_tok	copy_tk;

	cmd = add_cmd(data);
	tk = data->lst_tk;
	prev_tk = NULL;
	while (tk && tk->op != NWLINE)
	{
		check_syntax(data, tk, prev_tk);
		if (tk->type == CTRL_OP)
			cmd = add_cmd(data);
		else if (tk->type == RED_OP)
		{
			add_red(lstadd_red(cmd), tk);
			tk = tk->next;
		}
		else
		{
			copy_tk = *tk;
			copy_tk.next = NULL;
			tmp_tk = expand(data, &copy_tk);
			while (tmp_tk)
			{
				append_cmd(data, tmp_tk, cmd);
				tmp_tk = tmp_tk->next;
			}
		}
		prev_tk = tk;
		tk = tk->next;
	}
}
