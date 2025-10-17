/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:45:51 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:19 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_node(t_env *tmp, t_env *prv, t_env **env)
{
	if (tmp == *env)
		*env = (*env)->next;
	else if (tmp->next == NULL)
		prv->next = NULL;
	else
		prv->next = tmp->next;
	ft_del_node(tmp);
}

int	ft_unset(char **args, t_env **env)
{
	t_env	*tmp;
	t_env	*prv;
	int		i;

	i = 0;
	while (args[i])
	{
		tmp = *env;
		prv = *env;
		while (tmp)
		{
			if (tmp->can_be_deleted == 1
				&& ft_strcmp(tmp->name, args[i]) == 0)
			{
				delete_node(tmp, prv, env);
				break ;
			}
			prv = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
