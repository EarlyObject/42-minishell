/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/16 17:02:55 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//wc << fin
//<< fin > a

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks commands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	t_prog		*prog;
	t_arguments	*arguments;
	char		*builtin_str[9];
	int			ret;

	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		g_rv = 1;
		arguments = initialize_arg(prog);
		set_shlvl_num(arguments);
		shell_reader(arguments);
		if (arguments->flag_execution)
			if (!msh_execute(arguments->argv, arguments))
				break ;
		manage_loop_heap(arguments, prog);
	}
	manage_program_heap(arguments, prog);
	ret = arguments->status;
	free_heap_memory(arguments);
	return (ret);
}

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	set_signal(1);
	atexit(ft_leaks);
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	return (shell_loop(envp));
}

//ls < a
//lsof -c minishell | grep PIPE
//export vs env
//export todas, env solo seteadas

//https://datacarpentry.org/shell-genomics/04-redirection/index.html

//<< eof | cat, cat | cat | ls

//echo "''$PWD'''qwere"qwqwer$P$P$PWD"'$PWD'"
//echo $""HOME   ->elimina dollar. NOPE
//meter un control de top | cat

//NO BORRAR "ls" "|" "wc" COMMIT LLAMADO "LS EJEMPLO" LO TIENE

//TODO funcion de checckeo por si te meten un Null en la talbla, 
//por memoria o de la manera que sea, cierre minishell en shutdown.

//ESTUDIAR
//en el proceso principal, tras los forks, todos los fd del pipe cerrados
//ejecutarlos en paralelo, no en serie. 
//todos los procesos del fork se lanazarian a la vez

// << eof | cat, cat | cat | ls

//ls |  wc -l |  cat |  grep 72 |  grep 72 <<  fin

//echo $TEST > $TEST
//ls > omega | ls -la > final
//wc < omega >dd | wc -l< final > cc 
//cat dd && cat cc

//ls < aijshf | wc -l < nonexisten
//ls < aijshf | wc -l | echo hola

//ls < a | wc -l | echo hola NOT WORKING