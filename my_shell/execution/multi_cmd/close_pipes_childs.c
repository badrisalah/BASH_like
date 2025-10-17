/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_childs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:06 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:26 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe_first_child(int **pipes)
{
	int	i;

	i = 1;
	close(pipes[0][0]);
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	middle_pipe_close(int **pipes, int num)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		if (i == (num - 1))
		{
			close(pipes[i][1]);
		}
		else if (i == num)
		{
			close(pipes[i][0]);
		}
		else
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

int	close_pipe_last_child(int **pipes)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (pipes[len])
		len++;
	while (i < len)
	{
		if (i == (len - 1))
		{
			close(pipes[i][1]);
		}
		else
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
	return (len - 1);
}
