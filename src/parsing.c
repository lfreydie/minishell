/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/04 17:04:02 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_cmd(char **tab, t_tok *new_token, int id);
{
	//oijioj
}

void	parse_redir_in(char **tab, t_tok *new_token, int id)
{
	int		i;
	int		fd;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<", ft_strlen(tab[i])))
		{
			if (new_token->redir_in != NULL)
			{
				fd = open(new_token->redir_in);
				if (fd < 0)
					perror("open");
				close(fd);
			}
			if (ft_strncmp(tab[i], "<<", ft_strlen(tab[i])))
			{
				new_token->heredoc = true;
				//new_token->redir_in = appel heredoc;
			}
			else
				new_token->redir_in = tab[i + 1];
		}
		i++;
	}
}

void	parse_redir_out(char **tab, t_tok *new_token, int id)
{
	int		i;
	int		fd;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], ">", ft_strlen(tab[i])))
		{
			if (new_token->redir_out != NULL)
			{
				fd = open(new_token->redir_out);
				if (fd < 0)
					perror("open");
				close(fd);
			}
			if (ft_strncmp(tab[i], ">>", ft_strlen(tab[i])))
				new_token->append = true;
			new_token->redir_out = tab[i + 1];
		}
		i++;
	}

}

void	parse_token(t_data *data)
{
	int		id;
	t_tok	*new_token;

	id = 0;
	while (data->temp->tokens[id])
	{
		new_token = create_token();
		new_token->id = id;
		data->temp->tab_cmd = ft_split(data->temp->tokens[id], ' ');
		parse_redir_in(data->temp->tab_cmd, new_token, id);
		parse_redir_out(data->temp->tab_cmd, new_token, id);
		parse_cmd(data->temp->tab_cmd, new_token, id);
		add_token(data, new_token);
		id++;
	}
}
