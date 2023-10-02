/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/09/29 17:01:39 by blandineber      ###   ########.fr       */
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

// void	parse_token(t_data *data)
// {
// 	int		i;
// 	int		id;
// 	char	**cmd;
// 	char	*redir_in;
// 	char	*redir_out;

// 	i = 0;
// 	id = 0;
// 	redir_in = "IDK";
// 	redir_out = "IDK";
// 	cmd = malloc(sizeof(char **) * (MAX_TOKENS + 1));

// 	while (data->tokens[i] != NULL)
// 	{
// 		while (ft_strncmp(data->tokens[i], "|", ft_strlen(data->tokens[i])) != 0)

// 			cmd[id][i] = *ft_strdup(data->tokens[i]);
// 			i++;
// 			j++;
// 		}
// 		cmd[id][j] = '\0';
// 		add_token(data, create_token(id, cmd, redir_in, redir_out));
// 		id++;
// 	}
// 	cmd[id] = NULL;
// }

void	parse_token(t_data *data)
{
	int		id;
	char	**cmd;
	char	*redir_in;
	char	*redir_out;

	id = 0;
	redir_in = "IDK";
	redir_out = "IDK";
	while (data->tokens[id])
	{
		cmd = ft_split(data->tokens[id], ' ');
		add_token(data, create_token(id, cmd, redir_in, redir_out));
		id++;
	}
}
