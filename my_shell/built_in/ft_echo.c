/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:25:43 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:45 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_n_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] != '-')
		return (-1);
	i++;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}

static void	ft_echo1(char **args)
{
	int	print_new_lign;
	int	i;

	i = 1;
	print_new_lign = check_n_flag(args[1]);
	if (print_new_lign == 0)
		i = 2;
	while (args[i])
	{
		if (check_n_flag(args[i]) == -1)
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (print_new_lign == -1)
		write(1, "\n", 1);
}

int	ft_echo(char **args, t_env **env)
{
	(void)env;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	ft_echo1(args);
	return (0);
}
