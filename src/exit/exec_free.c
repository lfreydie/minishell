/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:52:17 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/06 17:58:15 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1)
		close(fd1);
	else if (fd2)
		close(fd2);
	else if (fd3)
		close(fd3);
	else if (fd4)
		close(fd4);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
