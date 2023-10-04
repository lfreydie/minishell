/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:38 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/04 12:01:44 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	print_tokens(t_data *data)
{
	t_tok	*current;
	int		i;
	int		j;

	i = 0;
	current = data->head;
	while (current != NULL)
	{
		printf("Token %d ID: %d\n", i, current->id);
		j = 0;
		while (current->cmd[j] != NULL)
		{
			printf("Command %d: %s\n", j, current->cmd[j]);
			j++;
		}
		if (current->redir_in != NULL)
			printf("Redirection In: %s\n", current->redir_in);
		if (current->redir_out != NULL)
			printf("Redirection Out: %s\n", current->redir_out);
		current = current->next;
		i++;
	}
}

void	print_tokens1(t_data *data)
{
	int	i;

	i = 0;
	while (data->temp->tokens[i] != NULL)
	{
		printf("Token %d : %s\n", i, data->temp->tokens[i]);
		i++;
	}
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*next_token;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delimiters, *next_token))
		next_token++;
	if (*next_token == '\0')
		return (next_token = NULL, NULL);
	token = next_token;
	while (*next_token != '\0' && !strchr(delimiters, *next_token))
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token);
}
