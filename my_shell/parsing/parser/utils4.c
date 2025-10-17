/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:47:31 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/12 21:27:21 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_line	*remove_emptyexp(t_line **head, t_garbage **gcol)
{
	t_line	*cur;
	t_line	*prev;

	(void)gcol;
	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->token.tok == EMPTY_EXP)
		{
			if (!prev)
				*head = cur->next;
			else
				prev->next = cur->next;
			cur = cur->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (*head);
}

static t_line	*copy_node(t_line *src, t_garbage **gcol)
{
	t_line	*new_node;

	new_node = ft_malloc(sizeof(t_line), gcol);
	new_node->line = ft_strdup_g(src->line, gcol);
	new_node->token.tok = src->token.tok;
	new_node->token.quotes = src->token.quotes;
	new_node->token.imbigious = src->token.imbigious;
	new_node->next = NULL;
	return (new_node);
}

static int	is_not_redirection(int tok)
{
	return (tok != IN_REDIRECT && tok != OUT_REDIRECT && tok != APPEND);
}

static t_line	*append_node_if_valid(t_line *current, t_line **head,
	t_line **tail, t_garbage **gcol)
{
	t_line	*new_node;

	if (is_not_redirection(current->token.tok))
	{
		new_node = copy_node(current, gcol);
		if (!new_node)
			return (NULL);
		if (!*head)
			*head = new_node;
		else
			(*tail)->next = new_node;
		*tail = new_node;
	}
	return (*tail);
}

t_line	*remove_redirections(t_line **ll, t_garbage **gcol)
{
	t_line	*head;
	t_line	*tail;
	t_line	*current;

	if (!ll || !*ll)
		return (NULL);
	head = NULL;
	tail = NULL;
	current = *ll;
	while (current)
	{
		tail = append_node_if_valid(current, &head, &tail, gcol);
		if (!tail && is_not_redirection(current->token.tok))
			return (NULL);
		current = current->next;
	}
	return (head);
}
