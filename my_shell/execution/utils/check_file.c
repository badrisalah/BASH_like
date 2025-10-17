/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:46:13 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:28 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_cmd1(char *cmd)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (0);
			else if (access(cmd, X_OK) != 0)
			{
				ft_print_err("minisell: ");
				ft_print_err(cmd);
				ft_print_err(": Permission denied\n");
				return (126);
			}
		}
		else
		{
			ft_print_err("minisell: ");
			ft_print_err(cmd);
			ft_print_err(": No such file or directory\n");
			return (127);
		}
	}
	return (0);
}

static int	check_error(char *cmd, t_env **env, t_garbage **garb_coll)
{
	char	*tmp;
	int		i;

	tmp = env_search_value_g("PATH", env, garb_coll);
	ft_print_err("minishell: ");
	if (!tmp || tmp[0] == 0)
	{
		ft_print_err(cmd);
		ft_print_err(": No such file or directory\n");
		return (127);
	}
	else
	{
		i = does_has_slash(cmd);
		ft_print_err(cmd);
		if (cmd[i] == '/')
			ft_print_err(": No such file or directory\n");
		else
			ft_print_err(": command not found\n");
		return (127);
	}
}

static int	check_cmd2(char *cmd, char *cmd_path,
	t_env **env, t_garbage **garb_coll)
{
	char	*path;

	if (access(cmd_path, X_OK) == 0
		&& (cmd_path[0] == '.' || cmd_path[0] == '/'))
		return (0);
	else
	{
		if (access(cmd_path, X_OK) == 0)
			return (0);
		path = env_search_value_g("PATH", env, garb_coll);
		ft_print_err("minishell: ");
		ft_print_err(cmd);
		if (!path || path[0] == 0)
		{
			return (ft_print_err(": Permission denied\n"), 126);
		}
		else
		{
			return (ft_print_err(": command not found\n"), 127);
		}
	}
	return (0);
}

int	check_dir(char *cmd, t_env **env, t_garbage **garb_coll)
{
	char	*path;

	path = env_search_value_g("PATH", env, garb_coll);
	if (cmd[0] != '.' && cmd[1] != '/' && cmd[strlen(cmd) - 1] != '/'
		&& cmd[0] != '/')
	{
		if (!path || path[0] == 0)
		{
			ft_print_err(cmd);
			ft_print_err(": Is a directory\n");
			return (126);
		}
		ft_print_err(cmd);
		ft_print_err(": command not found\n");
		return (127);
	}
	ft_print_err(cmd);
	ft_print_err(": Is a directory\n");
	return (126);
}

int	check_cmd(char *cmd, char *cmd_path, t_env **env, t_garbage **garb_coll)
{
	struct stat	*cmd_stat;
	int			status;

	status = check_cmd1(cmd);
	if (status != 0)
		return (status);
	cmd_stat = ft_malloc(sizeof(struct stat), garb_coll);
	if (stat(cmd_path, cmd_stat) == -1)
	{
		return (check_error(cmd, env, garb_coll));
	}
	if (S_ISDIR((*cmd_stat).st_mode))
	{
		ft_print_err("minishell: ");
		status = check_dir(cmd, env, garb_coll);
		return (status);
	}
	status = check_cmd2(cmd, cmd_path, env, garb_coll);
	if (status != 0)
		return (status);
	return (0);
}
