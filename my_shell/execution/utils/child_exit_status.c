/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:42:40 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:33 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		return (WTERMSIG(status) + 128);
	}
	if (!WIFEXITED(status))
		return (1);
	return (WEXITSTATUS(status));
}
