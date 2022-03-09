/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6file_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:10:20 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/07 16:26:12 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Recieves input from file if needed. */
void	input_from_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed. */
void	output_to_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed append. */
void	output_to_file_append(char *path)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

void
	manage_input_redirection(t_arguments *args)
{
	if (args->flag_file_in)
		input_from_file(args->file_input);
}

void
	manage_output_redirection(t_arguments *args)
{
	if (args->flag_file_out == 2)
		output_to_file_append(args->file_output);
	else if (args->flag_file_out)
		output_to_file(args->file_output);
}
