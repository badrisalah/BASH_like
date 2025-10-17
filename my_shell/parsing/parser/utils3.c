/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:47:23 by sabadri           #+#    #+#             */
/*   Updated: 2025/05/30 01:57:16 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_line	*handle_token_5(t_line *current, int *syn_error);
t_line	*handle_token_6(t_line *current, int *syn_error);
t_line	*handle_token_4(t_line *current, int *syn_error);
t_line	*handle_token_10(t_line *current, int *syn_error);

t_line	*handle_token_5(t_line *current, int *syn_error)
{
	*syn_error = 1;
	if (!current->next)
		return (NULL);
	current = current->next;
	if (current->token.tok == 1 && current->next)
		current = current->next;
	if (current && (current->token.tok == 3
			|| (current->token.tok >= 12 && current->token.tok <= 14)))
	{
		current->token.tok = 7;
		(*syn_error)++;
	}
	else
		return (NULL);
	return (current);
}

t_line	*handle_token_6(t_line *current, int *syn_error)
{
	*syn_error = 1;
	if (!current->next)
		return (NULL);
	current = current->next;
	if (current->token.tok == 1 && current->next)
		current = current->next;
	if (current && (current->token.tok == 3
			|| (current->token.tok >= 12 && current->token.tok <= 14)))
	{
		current->token.tok = 8;
		(*syn_error)++;
	}
	else
		return (NULL);
	return (current);
}

t_line	*handle_token_4(t_line *current, int *syn_error)
{
	*syn_error = 1;
	if (!current->next)
		return (NULL);
	current = current->next;
	if (current->token.tok == 1 && current->next)
		current = current->next;
	if (current && (current->token.tok == 3
			|| (current->token.tok >= 12 && current->token.tok <= 14)))
	{
		if (current->token.tok == SQUOTES || current->token.tok == DQUOTES)
			current->token.quotes = 1e9;
		current->token.tok = DELIMITER;
		(*syn_error)++;
	}
	else
		return (NULL);
	return (current);
}

static t_line	*process_token(t_line *current, int *syn_error)
{
	if (current->token.tok == PIPE)
		return (handle_pipe_token(current, syn_error));
	if (current->token.tok == 5)
		return (handle_token_5(current, syn_error));
	if (current->token.tok == 6)
		return (handle_token_6(current, syn_error));
	if (current->token.tok == 4)
		return (handle_token_4(current, syn_error));
	if (current->token.tok == 10)
		return (handle_token_10(current, syn_error));
	return (current);
}

int	second_llc(t_line **ll, t_env **tenv)
{
	t_line	*current;
	int		syn_error;

	(void)tenv;
	tenv = NULL;
	current = *ll;
	if (current && current->token.tok == 2)
		return (0);
	while (current)
	{
		syn_error = 0;
		current = process_token(current, &syn_error);
		if (!current)
			break ;
		current = current->next;
	}
	if (syn_error != 0x2 && syn_error != 0)
		return (0);
	return (1);
}
