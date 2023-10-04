/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/04 15:55:15 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_redirection(t_data *data, t_tok *new_token)
{
	(void)data;
	(void)new_token;
	printf("One redirection\n");
}

void	multiple_redirections(t_data *data, t_tok *new_token)
{
	(void)data;
	(void)new_token;
	printf("Multiple redirection\n");
}

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
	int		num_redir;
	t_tok	*new_token;

	id = 0;
	while (data->temp->tokens[id])
	{
		new_token = create_token();
		new_token->id = id;
		num_redir = search_redirections(data, data->temp->tokens[id]);
		if (num_redir == 1)
			one_redirection(data, new_token);
		else if (num_redir >= 2)
			multiple_redirections(data, new_token);
		else
			new_token->cmd = ft_split(data->temp->tokens[id], ' ');
		add_token(data, new_token);
		id++;
	}
}
