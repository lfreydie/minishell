/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:08:37 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/24 13:29:23 by lefreydier       ###   ########.fr       */
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
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		exit(1); // code erreur
	new_cmd->id = data->num_cmd - 1;
	if (!last_cmd)
		data->lst_cmd = new_cmd;
	else
		last_cmd->next = new_cmd;
	return (new_cmd);
}

void	add_tk_red(t_data *data, t_tok	*tk, t_cmd *cmd)
{
	int	fd;

	(void) data;
	if (tk->op == IN_RED)
	{
		if (cmd->io_red.red_in)
			(fd = open(cmd->io_red.red_in, O_RDONLY), close(fd));
		cmd->io_red.red_in = tk->next->value;
		cmd->io_red.heredoc = false;
	}
	else if (tk->op == HEREDOC_RED)
		heredoc_set(data, cmd, tk->next->value);
	else if (tk->op == OUTTR_RED || tk->op == OUTAP_RED)
	{
		if (cmd->io_red.red_out)
			(fd = open(cmd->io_red.red_out, O_RDONLY), close(fd));
		if (tk->op == OUTAP_RED)
			cmd->io_red.append = true;
		else
			cmd->io_red.append = false;
		cmd->io_red.red_out = tk->next->value;
	}
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
	n_cmd = ft_calloc(sizeof(char *), current_size + 2);
	if (!n_cmd)
		exit(1); //code erreur
	j = 0;
	while (cmd->cmd_value && cmd->cmd_value[j])
	{
		n_cmd[j] = ft_strdup(cmd->cmd_value[j]);
		j++;
	}
	n_cmd[j] = ft_strdup(tk->value);
	j = -1;
	if (cmd->cmd_value)
	{
		while (cmd->cmd_value[++j])
			free(cmd->cmd_value[j]);
		free(cmd->cmd_value);
	}
	cmd->cmd_value = n_cmd;
}

void	parse_token(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*tk;
	t_tok	*prev_tk;

	(void) prev_tk;
	cmd = add_cmd(data);
	tk = data->lst_tk;
	prev_tk = NULL;
	while (tk && tk->op != NWLINE)
	{
		//check_syntax(tk, prev_tk);
		if (tk->type == CTRL_OP)
			cmd = add_cmd(data);
			cmd = add_cmd(data);
		else if (tk->type == RED_OP)
		{
			add_tk_red(data, tk, cmd);
			tk = tk->next;
		}
		else
			append_cmd(data, tk, cmd);
		prev_tk = tk;
		tk = tk->next;
	}
}