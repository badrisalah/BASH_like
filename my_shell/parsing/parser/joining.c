/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:46:59 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/14 14:23:45 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_command_tokens(t_line **current_ptr, t_garbage **gcol)
{
	char	*joined;
	char	*tmp;
	t_line	*current;

	current = *current_ptr;
	joined = ft_strdup_g("", gcol);
	if (!joined)
		return (NULL);
	while (current && (current->token.tok == COMMAND
			|| current->token.tok >= 12))
	{
		tmp = ft_strjoin_g(joined, current->line, gcol);
		joined = tmp;
		current = current->next;
	}
	*current_ptr = current;
	return (joined);
}

static char	*join_special_tokens(t_line **current_ptr, t_garbage **gcol)
{
	t_line	*current;
	char	*joined;
	char	*tmp;
	char	*joined_cmds;

	current = *current_ptr;
	joined = ft_strdup_g("", gcol);
	if (!joined)
		return (NULL);
	if (current && (current->token.tok >= 7 && current->token.tok <= 10))
	{
		tmp = ft_strjoin_g(joined, current->line, gcol);
		joined = tmp;
		current = current->next;
	}
	*current_ptr = current;
	joined_cmds = join_command_tokens(current_ptr, gcol);
	tmp = ft_strjoin_g(joined, joined_cmds, gcol);
	joined = tmp;
	return (joined);
}

static t_line	*process_token_group(t_line **current, t_garbage **gcol)
{
	t_line	*new_node;
	char	*joined;
	int		node_token_type;
	int		quotes;
	int		imbigious;

	node_token_type = (*current)->token.tok;
	quotes = (*current)->token.quotes;
	imbigious = (*current)->token.imbigious;
	joined = NULL;
	if (node_token_type == COMMAND || node_token_type >= 12)
		joined = join_command_tokens(current, gcol);
	else if (node_token_type >= 7 && node_token_type <= 10)
		joined = join_special_tokens(current, gcol);
	else
	{
		joined = (*current)->line;
		*current = (*current)->next;
	}
	if (!joined)
		return (NULL);
	new_node = new_line_node(joined, node_token_type, gcol);
	new_node->token.quotes = quotes;
	new_node->token.imbigious = imbigious;
	return (new_node);
}

t_line	*final_joining(t_line **ll, t_garbage **g)
{
	t_line	*result;
	t_line	*c;
	t_line	*node;
	t_line	*snode;

	if (!ll || !(*ll))
		return (NULL);
	result = NULL;
	c = *ll;
	while (c)
	{
		node = process_token_group(&c, g);
		if (node)
			append_line_node(&result, node);
		if (c && (c->token.tok == t_SPACE
				|| c->token.tok == PIPE))
		{
			snode = new_line_node(ft_strdup_g(c->line, g), c->token.tok, g);
			snode->token.quotes = c->token.quotes;
			append_line_node(&result, snode);
			c = c->next;
		}
	}
	return (result);
}
