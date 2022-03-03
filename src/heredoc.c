/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:25:59 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/01 10:30:25 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	update_buf(char **buf, char *readline_res)
{
	char	*res;
	char	*tmp;

	tmp = *buf;
	res = ft_strjoin(readline_res, "\n");
	*buf = ft_strjoin(*buf, res);
	free(tmp);
	free(res);
}

void
	mnge_heredoc(t_command *command_struct)
{
	char	*delim;
	char	*buf;
	char	*readline_res;

	delim = command_struct->command[1];
	readline_res = NULL;
	buf = ft_strdup("");
	while (delim && g_rv)
	{
		readline_res = readline(HEREDOC_PROMPT);
		if (!readline_res)
		{
			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file (wanted `%s\')\n", 2);// manage %
			break ;
		}
		if (!ft_strcmp(delim, readline_res))
			break ;
		update_buf(&buf, readline_res);
		free_pointers(1, readline_res);
	}
	//rl_event_hook = NULL;
	//free(buf);
	//free(readline_res); //provokes segfault
	//ft_putendl_fd(buf, 1); //where should we guard the result?
}

int
	heredoc_routine(t_command *command_struct)
{
	set_signal(3);
	mnge_heredoc(command_struct);
	set_signal(1);
	return (1);
}