/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:03:01 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:42 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_file(t_args **parcing)
{
	t_args	*tmp;

	tmp = *parcing;
	while (tmp)
	{
		if (tmp->tmp_heredoc >= 0)
			close(tmp->tmp_heredoc);
		if (tmp->fd_in >= 0)
			close(tmp->fd_in);
		if (tmp->fd_out >= 0)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
}

int	parsing_size(t_args *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

static int	dup_std(int *std_tmp)
{
	std_tmp[0] = dup(STDIN_FILENO);
	std_tmp[1] = dup(STDOUT_FILENO);
	if (std_tmp[0] == -1 || std_tmp[1] == -1)
	{
		perror("dup");
		return (1);
	}
	return (0);
}

static void	dup2_std(int *std_tmp)
{
	if (dup2(std_tmp[0], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(std_tmp[1], STDOUT_FILENO) == -1)
		perror("dup2");
	(close(std_tmp[0]), close(std_tmp[1]));
}

void	execution(t_args **parsing, t_env **env, t_garbage **garb_coll)
{
	int	status;
	int	parsing_lst_size;
	int	std_tmp[2];

	parsing_lst_size = parsing_size(*parsing);
	if (parsing_lst_size == 0)
		return ;
	open_file(parsing, env, garb_coll);
	if (g_sig == 130)
	{
		env_update_value("?", ft_itoa(130), env);
		return ;
	}
	status = dup_std(std_tmp);
	if (status == 0)
	{
		if (parsing_lst_size == 1)
			status = execution_one(parsing, env, garb_coll, std_tmp);
		else if (parsing_lst_size != 0)
			status = multi_cmd(parsing, std_tmp, env, garb_coll);
	}
	env_update_value("?", ft_itoa(status), env);
	close_file(parsing);
	dup2_std(std_tmp);
}
