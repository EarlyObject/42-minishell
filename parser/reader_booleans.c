/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_booleans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:33:05 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:04:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether char is a sufix. */
int	is_sufix(char z)
{
	return (z == '-');
}

int is_lex_symbol(char *string) //temporal apra borrar
{
	if (!ft_strcmp(string, "lex_INPUT"))
		return (1);
	if (!ft_strcmp(string, "lex_OUTPUT"))
		return (1);
	return (0);
}

int	token_is_lexic(char *token)
{
	if (ft_strncmp(token, "lex_", 4) == 0)
		return (1);
	else
		return (0);	
}
