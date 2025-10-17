/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:50:20 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:10 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	ft_clear_list(t_env **env)
{
	t_env	*current;
	t_env	*tmp;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		tmp = current;
		current = current->next;
		ft_del_node(tmp);
	}
	*env = NULL;
}
