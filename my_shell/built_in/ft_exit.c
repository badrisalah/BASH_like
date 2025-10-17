/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:42 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:52 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_spaces(char *str, int *i)
{
	while (str[*i])
	{
		if (ft_isspace(str[*i]) == 0)
			break ;
		(*i)++;
	}
}

static int	check_if_num(char *str)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			break ;
		i++;
	}
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

static void	exit_arg_handle2(char **args, t_env **env, t_garbage **garb_coll)
{
	write(1, "exit\n", 5);
	ft_print_err("minishell: exit: ");
	ft_print_err(args[1]);
	ft_print_err(": numeric argument required\n");
	rl_clear_history();
	ft_clear_list(env);
	garbage_clear(garb_coll);
}

static int	exit_arg_handle(char **args, int *std,
	t_env **env, t_garbage **garb_coll)
{
	t_exit_stat	exitt;

	exitt = ft_atoll(args[1]);
	exitt.check = check_if_num(args[1]);
	if (exitt.check == -1 || exitt.overflow == -1)
	{
		exit_arg_handle2(args, env, garb_coll);
		(1) && (close(std[0]), close(std[1]));
		exit(2);
	}
	else if (args[2])
	{
		write(1, "exit\n", 5);
		ft_print_err("minishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		rl_clear_history();
		ft_clear_list(env);
		garbage_clear(garb_coll);
		(1) && (close(std[0]), close(std[1]));
		printf("exit\n");
		exit(exitt.value % 256);
	}
}

int	ft_exit(char **args, int *std, t_env **env, t_garbage **garb_coll)
{
	int		status;
	char	*tmp;

	if (args[1])
	{
		return (exit_arg_handle(args, std, env, garb_coll));
	}
	else
	{
		(1) && (close(std[0]), close(std[1]));
		printf("exit\n");
		tmp = env_search_value("?", env);
		status = ft_atoi(tmp);
		free(tmp);
		rl_clear_history();
		ft_clear_list(env);
		garbage_clear(garb_coll);
		exit(status);
	}
}
