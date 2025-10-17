/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_from_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:12:25 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/17 12:17:09 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_args(t_line *temp)
{
	int	size;

	size = 0;
	while (temp && temp->token.tok != PIPE)
	{
		if (temp->token.tok == COMMAND || temp->token.tok >= 12)
			size++;
		else if (temp->token.tok == PIPE)
			break ;
		temp = temp->next;
	}
	return (size);
}

static void	fill_files(t_args *node, t_line *temp, t_garbage **g)
{
	while (temp && temp->token.tok != PIPE)
	{
		if (temp->token.tok == INFILE)
			list_add_files(&node->files, temp, INFILE, g);
		else if (temp->token.tok == DELIMITER)
		{	
			if (temp->token.quotes == 1e9)
				list_add_files(&node->files, temp, 1e9, g);
			else
				list_add_files(&node->files, temp, DELIMITER, g);
		}
		else if (temp->token.tok == OUTFILE)
			list_add_files(&node->files, temp, OUTFILE, g);
		else if (temp->token.tok == TOBEAPPENDED)
			list_add_files(&node->files, temp, TOBEAPPENDED, g);
		temp = temp->next;
	}
}

static void	fill_args(t_args *node, t_line *temp, t_garbage **gcol)
{
	int	i;

	i = 0;
	while (temp && temp->token.tok != PIPE)
	{
		if (temp->token.tok == COMMAND || temp->token.tok >= 12)
		{
			node->args[i] = ft_strdup_g(temp->line, gcol);
			i++;
		}
		temp = temp->next;
	}
	node->args[i] = NULL;
}

static t_args	*create_args_node(t_line *ll, t_garbage **gcol)
{
	int		size;
	t_args	*new_node;

	if (!ll)
		return (NULL);
	size = count_args(ll);
	new_node = ft_malloc(sizeof(t_args), gcol);
	if (!new_node)
		return (NULL);
	new_node->args = ft_malloc(sizeof(char *) * (size + 1), gcol);
	if (!new_node->args)
		return (NULL);
	new_node->files = NULL;
	new_node->files = NULL;
	fill_files(new_node, ll, gcol);
	fill_args(new_node, ll, gcol);
	new_node->next = NULL;
	return (new_node);
}

t_args	*ll_to_args(t_line **ll, t_garbage **gcol)
{
	t_args	*head;
	t_args	*current;
	t_args	*new_node;

	if (!ll || !(*ll))
		return (NULL);
	head = NULL;
	current = NULL;
	while (*ll)
	{
		new_node = create_args_node(*ll, gcol);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		while (*ll && (*ll)->token.tok != PIPE)
			*ll = (*ll)->next;
		if (*ll && (*ll)->token.tok == PIPE)
			*ll = (*ll)->next;
	}
	return (head);
}
