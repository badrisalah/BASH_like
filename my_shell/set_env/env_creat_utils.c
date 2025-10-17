/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:42:17 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:05 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*last_node(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	node_add_back(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (env == NULL)
		return ;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	else
	{
		tmp = last_node(*env);
		tmp->next = node;
	}
}

t_env	*creat_node(t_env **env, char *str, int stat, int can_be_deleted)
{
	t_env	*node;
	char	**tmp;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		ft_clear_list(env);
		exit(1);
	}
	tmp = sub_env(str);
	node->name = ft_strdup(tmp[0]);
	node->value = ft_strdup(tmp[1]);
	node->env_visibilty = stat;
	node->can_be_deleted = can_be_deleted;
	node->next = NULL;
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (node);
}

//check the env and creat a linked list for env ;)
t_env	*ft_creat_env_list(char **tenv)
{
	t_env	*env;

	env = NULL;
	if (tenv && tenv[0])
		if_env_exist(tenv, &env);
	else if (!tenv || !tenv[0])
		if_env_not_exist(&env);
	return (env);
}
