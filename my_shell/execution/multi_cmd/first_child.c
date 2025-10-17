/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:53:46 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:34 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redirection1(t_args *tmp, t_pipes pipes, int *status)
{
	if (tmp->fd_in != -2 && tmp->fd_out == -2)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		if (dup2(pipes.pipes[0][1], STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[0][1]);
		close(tmp->fd_in);
	}
	else if (tmp->fd_in == -2 && tmp->fd_out != -2)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[0][1]);
		close(tmp->fd_out);
	}
}

static int	redirection(t_args **parsing, t_pipes pipes)
{
	t_args	*tmp;
	int		status;

	tmp = *parsing;
	status = 0;
	if (tmp->fd_in == -2 && tmp->fd_out == -2)
	{
		if (dup2(pipes.pipes[0][1], STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[0][1]);
	}
	else if (tmp->fd_in != -2 && tmp->fd_out != -2)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[0][1]);
		(close(tmp->fd_in), close(tmp->fd_out));
	}
	else
		redirection1(tmp, pipes, &status);
	return (status);
}

int	exec_first(t_args *tmp, t_pipes pipes, t_env **env, t_garbage **garb_coll)
{
	int		status;
	char	**envp;
	char	*cmd_path;
	int		check;

	status = 0;
	status = exec_built_in(tmp->args, pipes.std, env, garb_coll);
	if (status == -1)
	{
		cmd_path = get_cmd_path(tmp->args[0], env, garb_coll);
		envp = switch_list_to_double(env, garb_coll);
		check = check_cmd(tmp->args[0], cmd_path, env, garb_coll);
		if (check != 0)
			return (check);
		if (execve(cmd_path, tmp->args, envp) == -1)
			perror(tmp->args[0]);
		return (127);
	}
	return (status);
}

void	first_child1(t_args **parcing, t_pipes pipes,
	t_env **env, t_garbage **garb_coll)
{
	int		status;
	t_args	*tmp;

	tmp = *parcing;
	if (!tmp->args || !tmp->args[0])
	{
		if (tmp->need_to_exit == 1)
			exit(tmp->need_to_exit);
		exit(0);
	}
	if (tmp->need_to_exit == 1)
		exit(tmp->need_to_exit);
	close_pipe_first_child(pipes.pipes);
	status = redirection(parcing, pipes);
	if (status != 1)
		status = exec_first(tmp, pipes, env, garb_coll);
	close(pipes.pipes[0][1]);
	(close(pipes.std[0]), close(pipes.std[1]));
	(garbage_clear(garb_coll), ft_clear_list(env));
	exit (status);
}

void	first_child(t_args **parcing, t_pipes pipes,
	t_env **env, t_garbage **garb_coll)
{
	int		id;

	g_sig = 1;
	id = fork();
	if (id == 0)
	{
		signals_reset();
		first_child1(parcing, pipes, env, garb_coll);
	}
	else if (id == -1)
		perror("fork");
}
