/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:22:12 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:36 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_path(char **paths, char *cmd, t_garbage **garb_coll)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin_g(paths[i], "/", garb_coll);
		cmd_path = ft_strjoin_g(tmp, cmd, garb_coll);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (ft_strdup_g(cmd, garb_coll));
}

char	*get_cmd_path(char *cmd, t_env **env, t_garbage **garb_coll)
{
	char	*path;
	char	**paths;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || cmd[0] == 0)
		return (ft_strdup_g(cmd, garb_coll));
	path = env_search_value_g("PATH", env, garb_coll);
	if (!path)
		return (ft_strdup_g(cmd, garb_coll));
	paths = ft_split_g(path, ':', garb_coll);
	path = check_path(paths, cmd, garb_coll);
	return (path);
}
