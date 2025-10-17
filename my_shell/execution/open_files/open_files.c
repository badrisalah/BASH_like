/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:34:16 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:06 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_herdoc2(t_files **files, t_env **env, t_garbage **garb_coll)
{
	t_files	*tmp;
	int		herdoc_fd;

	tmp = *files;
	herdoc_fd = -2;
	while (tmp)
	{
		if (herdoc_fd > -1)
			close(herdoc_fd);
		if (tmp->type == DELIMITER || tmp->type == 1e9)
		{
			herdoc_fd = here_doc(tmp->name, tmp->type, env, garb_coll);
		}
		tmp = tmp->next;
		if (g_sig == 130)
			return (close(herdoc_fd), -130);
	}
	return (herdoc_fd);
}

static void	open_herdoc(t_args **parsing, t_env **env, t_garbage **garb_coll)
{
	t_args	*tmp;

	tmp = *parsing;
	while (tmp)
	{
		tmp->tmp_heredoc = open_herdoc2(&tmp->files, env, garb_coll);
		if (tmp->tmp_heredoc == -1)
			tmp->need_to_exit = 1;
		else
			tmp->need_to_exit = 0;
		tmp = tmp->next;
		if (g_sig == 130)
			return ;
	}
}

void	open_files(t_args **parcing)
{
	int		fd_in;
	int		fd_out;
	t_args	*tmp;
	t_files	*files;

	tmp = *parcing;
	while (tmp)
	{
		if (tmp->need_to_exit == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		fd_in = -2;
		fd_out = -2;
		files = tmp->files;
		tmp->need_to_exit = 0;
		open_files1(tmp, files, &fd_in, &fd_out);
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
}

void	open_file(t_args **parcing, t_env **env, t_garbage **garb_coll)
{
	open_herdoc(parcing, env, garb_coll);
	if (g_sig == 130)
		return ;
	open_files(parcing);
}
