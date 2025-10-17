/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:35:22 by monabati          #+#    #+#             */
/*   Updated: 2025/06/29 13:30:07 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**creat_pipe(int num, t_garbage **garb_coll)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_malloc(sizeof(int *) * (num + 1), garb_coll);
	if (!pipes)
		return (NULL);
	while (i < num)
	{
		pipes[i] = ft_malloc(sizeof(int) * 2, garb_coll);
		i++;
	}
	pipes[num] = NULL;
	i = 0;
	while (i < num)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			close_pipes(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
