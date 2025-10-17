/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:22:46 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:29 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Returns a char* value and stores its address in a garbage collector.
char	*env_search_value_g(char *name, t_env **env, t_garbage **garb_coll)
{
	t_env	*tmp;

	if (!env || !*env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			return (ft_strdup_g(tmp->value, garb_coll));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

// Returns a char* value (caller is responsible for freeing the memory).
char	*env_search_value(char *name, t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

//update env variable value
int	env_update_value(char *name, char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	free(value);
	return (-1);
}
