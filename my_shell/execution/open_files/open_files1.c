/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:01:22 by monabati          #+#    #+#             */
/*   Updated: 2025/06/29 13:26:50 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ambiguous(char *name)
{
	ft_print_err(name);
	ft_print_err(": ambiguous redirect\n");
	return (-1);
}

static int	open_files2(t_args *tmp, t_files *files, int *fd_in, int *fd_out)
{
	if (files->type == DELIMITER || files->type == 1e9)
	{
		if (*fd_in > -1)
			close(*fd_in);
		*fd_in = tmp->tmp_heredoc;
	}
	else if (files->type == OUTFILE)
	{
		if (*fd_out > -1)
			close(*fd_out);
		*fd_out = open(files->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*fd_out == -1)
			return (tmp->need_to_exit = 1, ft_print_err("minishell: "),
				perror(files->name), 1);
	}
	else if (files->type == TOBEAPPENDED)
	{
		if (*fd_out > -1)
			close(*fd_out);
		*fd_out = open(files->name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*fd_out == -1)
			return (tmp->need_to_exit = 1, ft_print_err("minishell: "),
				perror(files->name), 1);
	}
	return (0);
}

static int	open_files0(t_args *tmp, t_files *files, int *fd_in)
{
	if (files->type == INFILE)
	{
		if (*fd_in > -1)
			close(*fd_in);
		*fd_in = open(files->name, O_RDONLY);
		if (*fd_in == -1)
			return (tmp->need_to_exit = 1, ft_print_err("minishell: "),
				perror(files->name), 1);
	}
	return (0);
}

void	open_files1(t_args *tmp, t_files *files, int *fd_in, int *fd_out)
{
	while (files)
	{
		if (files->imbigious == 1)
		{
			if (*fd_in > -1)
				close(*fd_in);
			if (*fd_out > -1)
				close(*fd_out);
			ambiguous(files->name);
			(*fd_in = -1, *fd_out = -1, tmp->need_to_exit = 1);
			return ;
		}
		if (open_files0(tmp, files, fd_in) == 1)
			return ;
		else
			if (open_files2(tmp, files, fd_in, fd_out) == 1)
				return ;
		files = files->next;
	}
}
