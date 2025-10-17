/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:49:14 by sabadri           #+#    #+#             */
/*   Updated: 2025/05/30 01:56:07 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_line	*handle_token_10(t_line *c, int *syn_error)
{
	*syn_error = 1;
	if (!c->next)
		return (NULL);
	c = c->next;
	if (c->token.tok == 1 && c->next)
		c = c->next;
	if (c && (c->token.tok == 3 || (c->token.tok >= 12 && c->token.tok <= 14)))
	{
		c->token.tok = 11;
		(*syn_error)++;
	}
	else
		return (NULL);
	return (c);
}

char	*handle_pipe(int *i, t_garbage **gcol)
{
	(*i)++;
	return (ft_strdup_g("|", gcol));
}

int	pipe_handle(int *syn_error, t_line *current)
{
	if (current->next)
	{
		current = current->next;
		if (current->token.tok == t_SPACE)
			current = current->next;
		if (current && (current->token.tok != PIPE && current->token.tok != 1))
		{
			(*syn_error)++;
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

t_line	*handle_pipe_token(t_line *current, int *syn_error)
{
	*syn_error = 1;
	if (!pipe_handle(syn_error, current))
		return (NULL);
	return (current);
}
