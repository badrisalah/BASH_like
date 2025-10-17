/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:19:08 by monabati          #+#    #+#             */
/*   Updated: 2025/06/29 13:26:42 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*export_creat_node(char *str, int stat, int can_be_deleted)
{
	t_env	*node;
	char	**tmp;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		return (NULL);
	}
	tmp = sub_env(str);
	node->name = ft_strdup(tmp[0]);
	node->value = ft_strdup(tmp[1]);
	node->env_visibilty = stat;
	node->can_be_deleted = can_be_deleted;
	node->next = NULL;
	free_double(tmp);
	return (node);
}

void	zero_case(t_env **env, char *arg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(arg, tmp->name) == 0)
		{
			tmp->env_visibilty = 1;
			tmp->can_be_deleted = 1;
			return ;
		}
		tmp = tmp->next;
	}
	node_add_back(env, export_creat_node(arg, 1, 1));
	env_update_value(arg, NULL, env);
}

void	one_case(t_env **env, char *arg)
{
	t_env	*tmp;
	char	**all;
	int		flag;

	tmp = *env;
	all = sub_env(arg);
	flag = 0;
	while (tmp)
	{
		if (ft_strcmp(all[0], tmp->name) == 0)
		{
			tmp->env_visibilty = 1;
			tmp->can_be_deleted = 1;
			env_update_value(all[0], ft_strdup(all[1]), env);
			flag = 1;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		node_add_back(env, export_creat_node(arg, 1, 1));
	free_double(all);
}

int	two_case2(t_env **env, char **all)
{
	t_env	*tmp;
	char	*tmpp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(all[0], tmp->name) == 0)
		{
			if (!tmp->value)
			{
				(tmp->env_visibilty = 1, tmp->can_be_deleted = 1);
				tmp->value = ft_strdup(all[1]);
				return (free_double(all), 1);
			}
			else
			{
				(tmp->env_visibilty = 1, tmp->can_be_deleted = 1);
				tmpp = tmp->value;
				tmp->value = ft_strjoin(tmpp, all[1]);
				return (free(tmpp), free_double(all), 1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	two_case(t_env **env, char *arg)
{
	char	**all;
	char	*tmp;
	char	*tmp1;

	all = sub_env(arg);
	tmp = ft_strtrim(all[0], "+");
	free(all[0]);
	all[0] = tmp;
	if (two_case2(env, all) == 1)
		return ;
	tmp1 = ft_strjoin(all[0], "=");
	tmp = ft_strjoin(tmp1, all[1]);
	node_add_back(env, export_creat_node(tmp, 1, 1));
	(free(tmp1), free(tmp));
	free_double(all);
}
