/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:05 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:39 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	env_list_size(t_env **env)
{
	t_env	*tmp;
	int		count;

	tmp = *env;
	count = 0;
	while (tmp)
	{
		if (tmp->value && tmp->env_visibilty == 1)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*double_join(char *name, char *value, t_garbage **garb_coll)
{
	char	*tmp;
	char	*join;

	tmp = ft_strjoin_g(name, "=", garb_coll);
	join = ft_strjoin_g(tmp, value, garb_coll);
	return (join);
}

char	**switch_list_to_double(t_env **env_list, t_garbage **garb_coll)
{
	t_env	*tmp;
	int		list_size;
	char	**env;
	int		i;

	tmp = *env_list;
	list_size = env_list_size(env_list);
	env = ft_malloc(sizeof(char *) * (list_size + 1), garb_coll);
	if (!env)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (tmp->value && tmp->env_visibilty == 1)
			env[i++] = double_join(tmp->name, tmp->value, garb_coll);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
