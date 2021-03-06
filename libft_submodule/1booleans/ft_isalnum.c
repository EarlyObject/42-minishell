/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 09:00:09 by guilmira          #+#    #+#             */
/*   Updated: 2021/09/23 11:45:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : returns 1 if alphabet or numeric. */
t_bool	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') \
	|| (c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9')));
}
