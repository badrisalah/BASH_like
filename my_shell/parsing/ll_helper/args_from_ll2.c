/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_from_ll2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:09:18 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/18 14:26:28 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	list_add_files(t_files **list, t_line *temp, int tp, t_garbage **g)
{
	t_files	*new_node;
	t_files	*current;

	new_node = ft_malloc(sizeof(t_files), g);
	new_node->name = ft_strdup_g(temp->line, g);
	new_node->imbigious = 0;
	if (temp->token.imbigious)
		new_node->imbigious = 1;
	new_node->type = tp;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
