/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:23:40 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:08 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path_exist(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	if_env_exist(char **tenv, t_env **env)
{
	int		i;
	int		tmp;
	char	*tmp1;

	i = 0;
	while (tenv[i])
	{
		node_add_back(env, creat_node(env, tenv[i], 1, 1));
		i++;
	}
	node_add_back(env, creat_node(env, "?=0", 0, 0));
	if (is_path_exist(env) == 0)
		node_add_back(env, creat_node(env, SECURE_PATH, 0, 1));
	tmp1 = env_search_value("SHLVL", env);
	tmp = ft_atoi(tmp1);
	free(tmp1);
	env_update_value("SHLVL", ft_itoa(tmp + 1), env);
}

void	if_env_not_exist(t_env **env)
{
	char	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd);
	node_add_back(env, creat_node(env, tmp, 1, 1));
	free(tmp);
	free(pwd);
	node_add_back(env, creat_node(env, SECURE_PATH, 0, 1));
	node_add_back(env, creat_node(env, "OLDPWD=", 1, 1));
	env_update_value("OLDPWD", NULL, env);
	node_add_back(env, creat_node(env, "SHLVL=1", 1, 1));
	node_add_back(env, creat_node(env, "?=0", 0, 0));
	env_update_value("OLDPWD", NULL, env);
}
