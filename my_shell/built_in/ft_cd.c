/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:42:23 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:42 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd1(t_env **env)
{
	int		status;
	char	*home;

	home = env_search_value("HOME", env);
	if (!home)
	{
		ft_print_err("minishel: cd: HOME not set\n");
		return (1);
	}
	else
	{
		status = chdir(home);
		if (status == -1)
		{
			perror("cd");
			free(home);
			return (1);
		}
		update_pwd(env);
		free(home);
	}
	return (0);
}

int	ft_cd2(char **args, t_env **env)
{
	int		status;
	char	*cwd;

	status = chdir(args[1]);
	if (status == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			update_pwd_in_err(env, args[1]);
			perror(CD_ERROR);
		}
		else
		{
			update_pwd(env);
			free(cwd);
		}
	}
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	if (!args[1])
		return (ft_cd1(env));
	if (args[2])
	{
		ft_print_err("cd: too many arguments\n");
		return (1);
	}
	else
		return (ft_cd2(args, env));
	return (0);
}
