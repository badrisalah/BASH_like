/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:52:33 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:21 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

//exit func if ^D entered!
void	exit_null(t_env **env, t_garbage **garb_coll)
{
	int	status;

	status = ft_atoi(env_search_value_g("?", env, garb_coll));
	rl_clear_history();
	garbage_clear(garb_coll);
	ft_clear_list(env);
	printf("exit\n");
	exit(status);
}

void	change_signal(t_env **env)
{
	static t_env	*tmp;

	if (env && *env)
	{
		tmp = *env;
		return ;
	}
	if (!env || !*env)
	{
		env_update_value("?", ft_strdup("130"), &tmp);
	}
}

void	minishell_loop(t_env **env, t_garbage **garb_coll)
{
	t_args	*parcing;
	char	*readline_input;

	parcing = NULL;
	while (999)
	{
		signals_init();
		change_signal(env);
		readline_input = readline(GREEN BOLD"minishell$> "RESET);
		if (!readline_input)
			exit_null(env, garb_coll);
		parcing = parsing(readline_input, env, garb_coll);
		execution(&parcing, env, garb_coll);
		if (ft_strcmp(readline_input, "") != 0)
			add_history(readline_input);
		free(readline_input);
		garbage_clear(garb_coll);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;
	t_garbage	*garb_coll;

	((void)ac, (void)av);
	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
	{
		perror("tty");
		exit(1);
	}
	env = ft_creat_env_list(envp);
	garb_coll = NULL;
	minishell_loop(&env, &garb_coll);
	ft_clear_list(&env);
	return (0);
}
