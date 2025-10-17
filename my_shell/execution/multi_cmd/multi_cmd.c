/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:43:24 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:45 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	multi_cmd(t_args **parcing, int *tmp, t_env **env, t_garbage **garb_coll)
{
	t_pipes	pipes;
	int		status;
	int		id;

	pipes.pipes = creat_pipe(parsing_size(*parcing) - 1, garb_coll);
	if (!pipes.pipes)
		return (1);
	pipes.std[0] = tmp[0];
	pipes.std[1] = tmp[1];
	first_child(parcing, pipes, env, garb_coll);
	in_middle_childs(parcing, pipes, env, garb_coll);
	id = last_child(parcing, pipes, env, garb_coll);
	close_pipes(pipes.pipes);
	waitpid(id, &status, 0);
	while (wait(NULL) != -1)
		;
	return (get_exit_status(status));
}
