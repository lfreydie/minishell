/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/04 12:32:46 by blandineber      ###   ########.fr       */
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


// > = 1, >> = 2, < = 3, << = 4
int	search_redirections(t_data *data, char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->temp->redir = (int *)malloc(strlen(token) * sizeof(int));
	if (data->temp->redir == NULL)
		return (perror("Memory allocation failed"), exit(EXIT_FAILURE), 1);
	while (token[i])
	{
		if (token[i] == '>' || token[i] == '<')
		{
			if (token[i] == '>' && token[i + 1] != '>')
				data->temp->redir[j] = 1;
			else if (token[i] == '>' && token[i + 1] == '>')
				data->temp->redir[j] = 2;
			else if (token[i] == '<' && token[i + 1] != '<')
				data->temp->redir[j] = 3;
			else if (token[i] == '<' && token[i + 1] == '<')
				data->temp->redir[j] = 4;
			j++;
		}
		i++;
	}
	return (j);
}

void	parse_token(t_data *data)
{
	int		id;
	char	**cmd;
	char	*redir_in;
	char	*redir_out;
	int		num_redir;

	id = 0;
	redir_in = NULL;
	redir_out = NULL;
	while (data->temp->tokens[id])
	{
		num_redir = search_redirections(data, data->temp->tokens[id]);
		printf("nombre de redirections :%d\n", num_redir);
		if (num_redir == 1)
		{
			printf("Une seule redirection\n");
			break ;
		}
		else
			cmd = ft_split(data->temp->tokens[id], ' ');
		add_token(data, create_token(id, cmd, redir_in, redir_out));
		id++;
	}
}
