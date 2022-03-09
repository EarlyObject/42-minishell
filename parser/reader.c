/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 11:02:48 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Reads command line and allocates it into string.
 * If pointer line exists and is not empty, adds it to history. */
static char	*read_shell_line(void)
{
	char	*line;

	line = readline(MSHELL);
	if (!line)
		return (NULL);
	if (line[0])
		add_history(line);
	return (line);
}

/** PURPOSE : Obtain COMMAND line and apply an initial filter. */
char	*read_and_filter_line(t_arguments *args)
{
	char	*line;

	line = read_shell_line();
	if (!line)
		return (NULL);
	if (pre_filter(line))
	{
		free(line);
		return (EMPTY_LINE);
	}
	args->flag_execution = 1;
	return (line);
}

static int	case_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspaces(str[i]))
			return (0);
	return (1);
}

/** PURPOSE : Count total number of pipes. */
static int	count_pipes(char **lexer_table)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (lexer_table[++i])
		if (!ft_strcmp(PIPE, lexer_table[i]))
			j++;
	return (j);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Creates linked list to manage any number of commands */
static void	arg_reader(char **table, t_arguments *args)
{
	args->total_commands = count_pipes(table) + 1;
	args->commands_lst = load_linked_list(table, args->envp, \
	args->total_commands);
	if (!args->commands_lst)
		ft_shutdown(ARG, 0, args);
}


/** PURPOSE : Handles file creation (in case of multipe redirections). */
void	file_redirections(char **lexer_table, t_arguments *args)
{
	management_file(lexer_table, args);
	if (case_space(lexer_table[0]) || args->flag_file_in == -1)
	{
		ft_free_split(lexer_table);
		if (args->flag_file_in)
			printf("%s: No such file or directory\n", args->file_input);
		args->flag_execution = 1;
		return ;
	}
}


/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Reads command line and applies a pre-filter.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
void
	shell_reader(t_arguments *args)
{
	char		*line;
	//char		**table;
	char		**lexer_table;
	int			*lexer_type;

	line = read_and_filter_line(args);
	if (!line)
		eof_exit(args);
	if (!line[0])
		return ;
	lexer_table = main_lexer(line, args);
	free(line);
	if (!lexer_table)
		return ;
	lexer_type = class_lex_table(lexer_table);
	if (!lexer_type)
		ft_shutdown(MEM, errno, args);
	
	printer(lexer_table, lexer_type);
	file_redirections(lexer_table, args);
	arg_reader(lexer_table, args);
	ft_free_split(lexer_table);
	free(lexer_type);
	//table = get_command_table(lexer_table, args, lexer_type);  esto estaba antes de file redirections.. mantener de momento
	//printer(table, lexer_type);
	//ft_free_split(table);
}
