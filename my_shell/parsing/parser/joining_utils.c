/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:44:40 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/13 13:39:29 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	process_line(t_line *node, t_garbage **gcole)
{
	char	*tmp;

	tmp = NULL;
	node->token.quotes = 0;
	if (node->line[0] == '\'')
	{
		node->token.tok = 12;
		node->token.quotes = 1e9;
		tmp = node->line;
		node->line = ft_strtrim_g(tmp, "\'", gcole);
	}
	else if (node->line[0] == '\"')
	{
		node->token.tok = 13;
		node->token.quotes = 1e9 - 1;
		tmp = node->line;
		node->line = ft_strtrim_g(tmp, "\"", gcole);
	}
	else if (node->line[0] == '$')
		node->token.tok = 14;
}

t_line	*s_or_d_or_v(t_line **ll, t_garbage **gcol)
{
	t_line	*current;

	if (!ll)
		return (NULL);
	current = *ll;
	while (current)
	{
		process_line(current, gcol);
		current = current->next;
	}
	return (*ll);
}

void	append_line_node(t_line **head, t_line *new_node)
{
	t_line	*temp;

	temp = NULL;
	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_line	*new_line_node(char *line, int tok, t_garbage **gcol)
{
	t_line	*node;

	node = ft_malloc(sizeof(t_line), gcol);
	if (!node)
		return (NULL);
	node->line = line;
	node->token.tok = tok;
	node->next = NULL;
	return (node);
}
