/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:01:41 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:35:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	ft_str_swap(char **p1, char **p2)
{
	char	*temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

/*
** SYNOPSIS: function for sorting string arrays using quicksort method.
*/
void
	ft_str_arr_sort(char *arr[], unsigned int len)
{
	unsigned int	i;
	unsigned int	pivot;

	if (len <= 1)
		return ;
	pivot = 0;
	i = 0;
	while (i < len)
	{
		if (ft_strcmp(arr[i], arr[len - 1]) < 0)
			ft_str_swap(arr + i, arr + pivot++);
		i++;
	}
	ft_str_swap(arr + pivot, arr + len - 1);
	ft_str_arr_sort(arr, pivot++);
	ft_str_arr_sort(arr + pivot, len - pivot);
}
