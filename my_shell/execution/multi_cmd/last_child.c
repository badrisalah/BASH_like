/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:49:33 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:38 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redirection1(t_args *parcing, t_pipes pipes,
	int last_pipe, int *status)
{
	if (parcing->fd_in != -2 && parcing->fd_out == -2)
	{
		if (dup2(parcing->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[last_pipe][0]);
		close(parcing->fd_in);
	}
	else if (parcing->fd_in == -2 && parcing->fd_out != -2)
	{
		if (dup2(pipes.pipes[last_pipe][0], STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		if (dup2(parcing->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[last_pipe][0]);
		close(parcing->fd_out);
	}
}

static int	redirection(t_args *parcing, t_pipes pipes, int last_pipe)
{
	int	status;

	status = 0;
	if (parcing->fd_in == -2 && parcing->fd_out == -2)
	{
		if (dup2(pipes.pipes[last_pipe][0], STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[last_pipe][0]);
	}
	else if (parcing->fd_in != -2 && parcing->fd_out != -2)
	{
		if (dup2(parcing->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		if (dup2(parcing->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[last_pipe][0]);
		(close(parcing->fd_in), close(parcing->fd_out));
	}
	else
		redirection1(parcing, pipes, last_pipe, &status);
	return (status);
}

static int	exec_last(t_args *tmp, int *std, t_env **env, t_garbage **garb_coll)
{
	int		status;
	int		check;
	char	*cmd_path;
	char	**envp;

	status = 0;
	status = exec_built_in(tmp->args, std, env, garb_coll);
	if (status == -1)
	{
		envp = switch_list_to_double(env, garb_coll);
		cmd_path = get_cmd_path(tmp->args[0], env, garb_coll);
		check = check_cmd(tmp->args[0], cmd_path, env, garb_coll);
		if (check != 0)
			return (check);
		if (execve(cmd_path, tmp->args, envp) == -1)
			perror(tmp->args[0]);
		return (127);
	}
	return (status);
}

void	last_child1(t_args *tmp, t_pipes pipes, t_env_garb env_garb)
{
	int	status;
	int	last_pipe;

	if (!tmp->args || !tmp->args[0])
	{
		if (tmp->need_to_exit == 1)
			exit(tmp->need_to_exit);
		exit(0);
	}
	if (tmp->need_to_exit == 1)
		exit(tmp->need_to_exit);
	last_pipe = close_pipe_last_child(pipes.pipes);
	status = redirection(tmp, pipes, last_pipe);
	if (status != 1)
		status = exec_last(tmp, pipes.std,
				env_garb.env, env_garb.garb_coll);
	close(pipes.pipes[last_pipe][0]);
	(close(pipes.std[0]), close(pipes.std[1]));
	garbage_clear(env_garb.garb_coll);
	ft_clear_list(env_garb.env);
	exit(status);
}

int	last_child(t_args **parcing, t_pipes pipes,
	t_env **env, t_garbage **garb_coll)
{
	t_args		*tmp;
	t_env_garb	env_garb;
	int			id;

	tmp = last_cmd(parcing);
	(1) && (env_garb.env = env, env_garb.garb_coll = garb_coll);
	g_sig = 1;
	id = fork();
	if (id == 0)
	{
		signals_reset();
		last_child1(tmp, pipes, env_garb);
	}
	else if (id == -1)
		perror("fork");
	return (id);
}
