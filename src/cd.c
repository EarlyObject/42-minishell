/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/30 11:31:06 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: returns value for env variable passed as second argument.
** If variable is not found returns NULL
*/
char *
	get_env_var(char **envp, char *needle, bool do_expand)
{
	char	*var;
	int		i;
	int		len;

	var = NULL;
	len = (int )ft_strlen(needle);
	i = 0;
	while (envp[i])
	{
		if (!ft_memcmp(envp[i], needle, len))
		{
			if (((envp[i])[len]) == '=' || ((envp[i])[len]) == '\0')
			{
				var = get_env_var_body(envp, do_expand, i, len);
				return (var);
			}
		}
		i++;
	}
	return (NULL);
}

/*
** SYNOPSIS: saves new environment variable.
*/
void
	set_new_var(char *var, t_arguments *arg)
{
	char	*temp_args[3];

	temp_args[0] = "export";
	temp_args[1] = var;
	temp_args[2] = NULL;
	export_new_variables(temp_args, arg);
}
/*
** SYNOPSIS: changes the values of 'OLDPWD' and 'PWD' variables.
*/

void
	renew_pwds(t_arguments *arg, char *old_path)
{
	char	*cur_path;
	char	*cwd;
	char	*p;

	p = NULL;
	p = get_env_var(arg->envp, "OLDPWD", false);
	if (p)
	{
		free_pointers(1, p);
		delete_env_var(arg->envp, 7, "OLDPWD");
		set_new_var(old_path, arg);
	}
	p = get_env_var(arg->envp, "PWD", false);
	if (p)
	{
		free_pointers(1, p);
		cwd = getcwd(NULL, 0);
		cur_path = ft_strjoin("PWD=", cwd);
		free_pointers(1, cwd);
		delete_env_var(arg->envp, 4, "PWD");
		set_new_var(cur_path, arg);
		free_pointers(1, cur_path);
	}
}

/*
** SYNOPSIS: gets correct path depending on the argument
** passed to cd  command ('--' or '~').
*/
void
	get_paths(char **args, t_arguments *arg, char **path, char **old_path)
{
	char	*cwd;

	(*path) = NULL;
	cwd = getcwd(NULL, 0);
	(*old_path) = ft_strjoin("OLDPWD=", cwd);
	free_pointers(1, cwd);
	if (!args[1] || !ft_memcmp(args[1], "~", 2) || !ft_memcmp(args[1], "--", 3))
	{
		(*path) = get_env_var(arg->envp, "HOME", false);
		if (!*path)
			printf("%s\n", HOMENOTSET);
	}
	else if (!ft_memcmp(args[1], "-", 2))
	{
		(*path) = get_env_var(arg->envp, "OLDPWD", false);
		if (!*path)
			printf("%s\n", OLDPWDNOTSET);
	}
	else
		(*path) = ft_strdup(args[1]);
}

/*
** SYNOPSIS: builtin cd command.
*/
int
	msh_cd(char **args, t_arguments *arg)
{
	char	*path;
	char	*old_path;

	if (get_arr_len(args) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", 1);
		set_status(arg, 1);
		return (2);
	}
	get_paths(args, arg, &path, &old_path);
	if (chdir(path) != 0)
	{
		if (path)
			set_cd_error(path);
		free_pointers(2, path, old_path);
		set_status(arg, 1);
	}
	else
	{
		free_pointers(1, path);
		renew_pwds(arg, old_path);
		free_pointers(1, old_path);
		set_status(arg, 0);
	}
	return (1);
}
