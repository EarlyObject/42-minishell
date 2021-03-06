/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:54:39 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/17 12:43:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_lex_symbol(char *string)
{
	if (!ft_strcmp(string, IN))
		return (1);
	if (!ft_strcmp(string, OUT))
		return (1);
	return (0);
}

static int	is_append(char *string)
{
	if (!ft_strcmp(string, APPEND))
		return (1);
	return (0);
}

static int	*alloc_type(char **lexer_table)
{
	int	*type;
	int	total_types;

	total_types = count_table(lexer_table);
	if (!total_types)
		return (NULL);
	type = ft_calloc(total_types, sizeof(int));
	if (!type)
		return (NULL);
	return (type);
}

/** PURPOSE : Corresponding numbers are:
 * 0	PIPE
 * 1	REDIRECT
 * 2	FILE
 * 3	APPEND
 * 4	HEREDOC
 * 5	COMMAND TOKEN
 * 6	EMPTY */
static void	classification(char **lexer_table, int *type, int i)
{
	if (!ft_strcmp(lexer_table[i], " "))
		type[i] = 6;
	else if (!ft_strcmp(lexer_table[i], PIPE))
		type[i] = 0;
	else if (is_lex_symbol(lexer_table[i]))
		type[i] = 1;
	else if (is_append(lexer_table[i]))
		type[i] = 3;
	else if (is_heredoc(lexer_table[i]))
		type[i] = 4;
	else if (i != 0 && (type[i - 1] == 1
			|| type[i - 1] == 3 || type[i - 1] == 4))
		type[i] = 2;
	else
		type[i] = 5;
}

/** PURPOSE : Assigns a number for each token in lexer table.  */
int	*class_lex_table(char **lexer_table)
{
	int	i;
	int	*type;

	type = alloc_type(lexer_table);
	if (!type)
		return (NULL);
	i = -1;
	while (lexer_table[++i])
		classification(lexer_table, type, i);
	return (type);
}
