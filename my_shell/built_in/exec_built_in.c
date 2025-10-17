/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:52:18 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:36 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Executes built-in commands return -1 if command is not found.
int	exec_built_in(char **args, int *std, t_env **env, t_garbage **garb_coll)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, std, env, garb_coll));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args, env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env));
	else
		return (-1);
	return (0);
}
