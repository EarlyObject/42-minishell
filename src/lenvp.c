/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:44 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/11 10:17:30 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	expand_l_var(char **args, t_arguments *arg, int i, char *temp)
{
	temp = get_env_var(arg->lenvp, args[i], true);
	if (temp)
	{
		free(args[i]);
		args[i] = temp;
		delete_env_var(arg->lenvp, get_envv_len(temp), temp);
	}
}

char *
	find_var_location(char *const *args, t_arguments *arg, int i, char *temp)
{
	long	len;
	char	*key;

	len = ft_strchr(args[i], '=') - (args[i]);
	key = ft_substr(args[i], 0, len);
	temp = get_env_var(arg->lenvp, key, false);
	if (temp)
	{
		free_pointers(1, temp);
		temp = lenvp_routine(args, arg, i, key);
		key = NULL;
	}
	else
	{
		temp = get_env_var(arg->envp, key, false);
		if (temp)
		{
			free_pointers(1, temp);
			temp = envp_routine(args, arg, i, key);
			key = NULL;
		}
	}
	free_pointers(1, key);
	return (temp);
}

void
	export_new_l_vars_cont(char **args, int i, size_t envp_len, char **new_envp)
{
	if (count_chars(args[i], "=") > 1)
		export_multi_var(args, i, envp_len, new_envp);
	else if (!new_envp[envp_len])
		new_envp[envp_len] = ft_strdup(args[i]);
}

void
	save_l_var(char **args, t_arguments *arg, int i)
{
	size_t	lenvp_len;
	char	**new_lenvp;

	new_lenvp = NULL;
	lenvp_len = get_arr_len(arg->lenvp);
	new_lenvp = copy_array(new_lenvp, arg->lenvp, 2);
	export_new_l_vars_cont(args, i, lenvp_len, new_lenvp);
	new_lenvp[lenvp_len + 1] = NULL;
	ft_free_split(arg->lenvp);
	arg->lenvp = new_lenvp;
}

bool
	export_new_l_variables(char **args, t_arguments *arg)
{
	int		i;
	bool	ret;
	char	*temp;

	ret = false;
	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		ret = true;
		temp = NULL;
		temp = find_var_location(args, arg, i, temp);
		if (!temp || !ft_strcmp("lenvp", temp))
			save_l_var(args, arg, i);
		else
			set_new_var(args[i], arg);
		i++;
	}
	return (ret);
}
