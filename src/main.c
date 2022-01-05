/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/05 15:15:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Store variables in struct that will be kept after loop. */
static void	store_program(t_prog *prog, t_arguments *args)
{
	prog->envp = args->envp;
	prog->status = args->status;
	prog->builtin_str = args->builtin_str;
}

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks cmmands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	int			status;
	t_prog		*prog;
	t_arguments	*arguments;
	char		*builtin_str[9];
	
	//introducir ignorar señales?
	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		arguments = intialize_arg(prog);
		shell_reader(envp, arguments);
		if (arguments->flag_execution)
			//prog->status = msh_execute(arguments->argv, arguments); //TODO :falta introducir set_status(t_arguments *arg, int status) en los pipes.ls
			if (!msh_execute(arguments->argv, arguments)) //We can't rely on prog->status to exit.
				break ;
		store_program(prog, arguments);

		//FOUND OUT SEGFAULT WITH SPLIT. THE PROBLEM IS THAT ARGV IS MODIFIED WHEN USED 'CD'AND NOT TERMINATED IN NULL.
		if (arguments->flag_execution)
			if (!ft_strcmp(arguments->argv[0], "cd")) 
				arguments->argv[1] = NULL;
		//TEMPORARY ^


		free_heap_memory(arguments); //free_heap now frees arguments as well. BUT keeps prog.
		if (0) //temporal
			break ;
		/* if (prog->status)
			break ; */
	}
	status = prog->status;
	free(prog);
	return (status);
}

//PROVISIONAL -- comment if compiling with fsanitize
/* void	*ft_leaks(void)
{
	system("leaks minishell");
	return (NULL);
} */

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	//atexit(ft_leaks()); //on exit, gves seg fault.
	 if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC, 0);
	return (shell_loop(envp));
}

//todo. vale, tengo command para la command tabe. falta, ¿que es o siguiente qe viene?
//si es un delimitator, entonnces ya puedes cerrar ls. SI no, entonces tokeniza, ponlo n el command.
//hacer el orden. lexer -> parser -> re ->executer

//tdo, ls + name of file/directory

//to do configurar exclamacion.
/* minishell$ echo $?
127
minishell$ ! ls | dsgs
dsgs: orden no encontrada
minishell$ echo $?
0 */

//https://datacarpentry.org/shell-genomics/04-redirection/index.html
 //cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.
