/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2file_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:33:15 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/30 10:20:51 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : File is input type. 
 *  * 1 is for output, 2 is for input, 3 for append 
 * and 4 for heredoc. */
static int	input_type(int *ptr)
{
	if ((*ptr) == 1 || (*ptr) == 3)
		return (1);
	return (0);
}

static void	manage_output(int *ptr, char *file, t_arguments *args)
{
	args->flag_file_out = 1;
	if (args->file_output)
		free(args->file_output);
	if (!file || !file[0])
	{
		args->flag_file_out = -1;
		return ;
	}
	args->file_output = ft_strdup(file);
	if (!args->file_output)
		ft_shutdown(MEM, 1, args);
	if ((*ptr) == 1)
		create_file(file);
	if ((*ptr) == 3)
	{
		create_file_append(file);
		args->flag_file_out = 2;
	}
}

static void	manage_input(char *file, t_arguments *args)
{
	if (args->file_input)
		free(args->file_input);
	if (!file)
	{
		args->flag_file_out = -1;
		return ;
	}
	args->file_input = ft_strdup(file);
	if (!args->file_input)
		ft_shutdown(MEM, 1, args);
}

/** PURPOSE : Iterate list and create every single file as is needed. 
 *  Codes: 1 is for output, 2 is for input, 3 for append and 4 for heredoc. */
void	create_output_files(t_list *list_files, \
t_list *list_type, t_arguments *args)
{
	int		*ptr;

	ptr = NULL;
	while (list_files)
	{
		ptr = list_type->content;
		if (input_type(ptr))
			manage_output(ptr, list_files->content, args);
		if ((*ptr) == 2)
		{
			manage_input(list_files->content, args);
			if (!file_exists(list_files->content))
			{
				args->flag_file_in = -1;
				break ;
			}
			args->flag_file_in = 1;
		}
		list_files = list_files->next;
		list_type = list_type->next;
	}
}
