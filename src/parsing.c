/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/03 19:03:31 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tok	*create_token(int id, char **cmd, char *redir_in, char *redir_out)
{
	t_tok	*new_token;

	new_token = ft_calloc(sizeof(t_tok), 1);
	if (!new_token)
		return (NULL);
	new_token->id = id;
	new_token->cmd = cmd;
	new_token->redir_in = redir_in;
	new_token->redir_out = redir_out;
	return (new_token);
}

void	add_token(t_data *data, t_tok *token)
{
	t_tok	*current;

	if (data->head == NULL)
	{
		data->head = token;
		data->head->previous = NULL;
	}
	else
	{
		current = data->head;
		while (current->next != NULL)
			current = current->next;
		current->next = token;
		token->previous = current;
	}
	data->num_tokens++;
}

int	search_redirections(t_data *data, char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '>')
			redir[0] = 0;
	}
	return (0);
}

void	parse_token(t_data *data)
{
	int		id;
	char	**cmd;
	char	*redir_in;
	char	*redir_out;

	id = 0;
	redir_in = NULL;
	redir_out = NULL;
	while (data->tokens[id])
	{
		if (search_redirections(data, data->tokens[id]) == 0)
			cmd = ft_split(data->tokens[id], ' ');
		add_token(data, create_token(id, cmd, redir_in, redir_out));
		id++;
	}
}

// void	parse_token(t_data *data)
// {
// 	int		id;
// 	char	**cmd;
// 	char	*redir_in;
// 	char	*redir_out;

// 	id = 0;
// 	redir_in = NULL;
// 	redir_out = NULL;
// 	while (data->tokens[id])
// 	{
// 		cmd = ft_split(data->tokens[id], ' ');
// 		add_token(data, create_token(id, cmd, redir_in, redir_out));
// 		id++;
// 	}
// }
