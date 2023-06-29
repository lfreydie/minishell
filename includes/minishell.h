/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/06/29 15:20:44 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include "libft.h"

# define ERR_TMP	0

typedef struct s_cmd
{
	char	**cmd_cut;
	char	*infile;
	char	*outfile;
}	t_cmd;

typedef struct s_data
{
	char	*line;
	char	**line_cut;
	t_cmd	*line_sort;
	int		order;
}	t_data;

//	READ
char	*ft_readline(void);
char	*get_prompt(void);

//	PARSE
t_data	*config_line_store(char *line);

#endif
