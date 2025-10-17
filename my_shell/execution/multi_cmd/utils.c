/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:32:30 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:48 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_middle_child(t_pipes pipes, int cmd_count,
	t_env **env, t_garbage **garb_coll)
{
	close(pipes.pipes[cmd_count - 1][0]);
	close(pipes.pipes[cmd_count][1]);
	close(pipes.std[0]);
	close(pipes.std[1]);
	garbage_clear(garb_coll);
	ft_clear_list(env);
}

t_args	*last_cmd(t_args **cmds)
{
	t_args	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
