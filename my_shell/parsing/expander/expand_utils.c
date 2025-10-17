/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:18:49 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/16 14:50:31 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var_name(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?' || ft_isalnum(c));
}

static void	insert_space(t_line **current, t_garbage **g)
{
	t_line	*space_node;

	space_node = ft_malloc(sizeof(t_line), g);
	space_node->line = ft_strdup_g(" ", g);
	space_node->token.tok = t_SPACE;
	space_node->next = (*current)->next;
	(*current)->next = space_node;
	*current = space_node;
}

static void	insert_parts(t_line **current, char **split_arg, t_garbage **g)
{
	t_line	*new_node;
	int		i;

	i = 0;
	while (split_arg[i])
	{
		new_node = ft_malloc(sizeof(t_line), g);
		new_node->line = ft_strdup_g(split_arg[i], g);
		new_node->token.tok = COMMAND;
		new_node->next = (*current)->next;
		(*current)->next = new_node;
		*current = new_node;
		if (split_arg[i + 1])
			insert_space(current, g);
		i++;
	}
}

static int	split_and_expand_node(t_line *node, t_garbage **gcol)
{
	char	**split_arg;

	split_arg = ft_split_g(node->line, ' ', gcol);
	if (!split_arg)
		return (0);
	node->line = ft_strdup_g("", gcol);
	node->token.tok = COMMAND;
	insert_parts(&node, split_arg, gcol);
	return (1);
}

t_line	*split_var(t_line **ll, t_garbage **gcol)
{
	t_line	*current;

	current = *ll;
	while (current)
	{
		if (current->token.tok == EXPANDED && !(ft_strlen(current->line)))
			current->token.tok = EMPTY_EXP;
		else if (current->token.imbigious == 1)
		{
			if (count_word(current->line) > 1 || !ft_strlen(current->line))
				current->token.imbigious = 1;
			else
				current->token.imbigious = 0;
		}
		else if (current->token.tok == EXPANDED)
		{
			if (!split_and_expand_node(current, gcol))
				return (NULL);
		}
		current = current->next;
	}
	return (*ll);
}
