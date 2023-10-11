/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/11 17:05:03 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n%s", get_prompt());
	fflush(stdout);
}

void	handle_sigquit(int sig)
{
	(void) sig;
	return ;
}


int	is_special_char(char c)
{
	return (c == '|' || c == ' ' || c == '<' || c == '>' || c == '\0');
}

void	tokenise_input(char *input, t_data *data)
{
	int	id;

	id = 0;
	data->temp = ft_calloc(sizeof(t_temp), 1);
	data->temp->tokens = ft_split(input, '|');
	while (data->temp->tokens[id])
		id++;
	data->num_tokens = id;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);
	data = ft_calloc(sizeof(t_data), 1);
	data->env = envp;
	while (1)
	{
		input = ft_readline();
		if (!input)
		{
			if (data)
				free_all(data);
			printf("exit\n");
			data->exit_flag = 1;
			break ;
		}
		tokenise_input(input, data);
		parse_token(data);
		//launch_exec_process(data);
		clear_tokens(data);
		free(input);
	}
	free_all(data); //SEGFAULT si ctrl_D
	return (0);
}
