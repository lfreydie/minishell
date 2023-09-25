/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:59 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/25 19:12:56 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//echo, cd, pwd, export, unset, env, exit

void	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
}

void	ft_echo(char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
	{
		if (args[1] == NULL)
		{
			printf("\n");
			return ;
		}
		if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
			printf("%s", args[2]);
		else
			printf("%s\n", args[1]);
	}
}

// doesn't work with relative path
void	ft_cd(char **args)
{
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
	{
		if (args[1] == NULL)
			chdir("/mnt/nfs/homes/bberthod");
		else
		{
			if (chdir(args[1]) != 0)
				perror ("cd");
		}
	}
}
