/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:15:14 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:56 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this funcs creat a copy of env and print them and free the copy
t_env	*env_copy2(t_env *tmp)
{
	t_env	*new_node;

	if (!tmp)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		return (NULL);
	}
	new_node->name = ft_strdup(tmp->name);
	new_node->value = ft_strdup(tmp->value);
	new_node->env_visibilty = tmp->env_visibilty;
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_copy(t_env *env)
{
	t_env	*cpy;
	t_env	*tmp;
	t_env	*current;

	tmp = env;
	cpy = env_copy2(tmp);
	if (!cpy)
		return (cpy);
	current = cpy;
	while (tmp)
	{
		tmp = tmp->next;
		if (current)
		{
			current->next = env_copy2(tmp);
		}
		if (current->next)
		{
			current = current->next;
		}
	}
	return (cpy);
}

static void	ft_swap_nodes(t_env *env, t_env *env1)
{
	char	*name;
	char	*value;
	int		visibilty;

	name = env->name;
	value = env->value;
	visibilty = env->env_visibilty;
	env->name = env1->name;
	env->value = env1->value;
	env->env_visibilty = env1->env_visibilty;
	env1->name = name;
	env1->value = value;
	env1->env_visibilty = visibilty;
}

static void	sort_list(t_env **cpy)
{
	t_env	*tmp;
	t_env	*current;
	int		list_size;

	if (!(*cpy))
		return ;
	tmp = *cpy;
	current = *cpy;
	list_size = ft_list_size(tmp);
	while (list_size > 0)
	{
		tmp = current;
		while (tmp)
		{
			if (tmp->next)
			{
				if (ft_strcmp(tmp->name, tmp->next->name) > 0)
				{
					ft_swap_nodes(tmp, tmp->next);
				}
			}
			tmp = tmp->next;
		}
		list_size--;
	}
}

int	print_env(t_env **env)
{
	t_env	*tmp;
	t_env	*cpy;

	if (!env || !*env)
		return (0);
	cpy = env_copy(*env);
	if (!cpy)
		return (1);
	(sort_list(&cpy), tmp = cpy);
	while (cpy)
	{
		if (cpy->env_visibilty == 1)
		{
			if (!cpy->value)
			{
				(printf("declare -x %s\n", cpy->name), cpy = cpy->next);
				continue ;
			}
			else
				printf("declare -x %s=\"%s\"\n", cpy->name, cpy->value);
		}
		cpy = cpy->next;
	}
	ft_clear_list(&tmp);
	return (0);
}
