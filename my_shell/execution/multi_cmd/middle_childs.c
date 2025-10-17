/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:30:43 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:42 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redirection_middle1(t_args *parcing, t_pipes pipes,
	int cmd_count, int *status)
{
	if (parcing->fd_in != -2 && parcing->fd_out == -2)
	{
		if (dup2(parcing->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		if (dup2(pipes.pipes[cmd_count][1], STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[cmd_count - 1][0]);
		close(pipes.pipes[cmd_count][1]);
		close(parcing->fd_in);
	}
	else if (parcing->fd_in == -2 && parcing->fd_out != -2)
	{
		if (dup2(pipes.pipes[cmd_count - 1][0], STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		if (dup2(parcing->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(pipes.pipes[cmd_count - 1][0]);
		close(pipes.pipes[cmd_count][1]);
		close(parcing->fd_out);
	}
}

static int	redirection_middle(t_args *parcing, t_pipes pipes, int cmd_count)
{
	int	status;

	status = 0;
	if (parcing->fd_in == -2 && parcing->fd_out == -2)
	{
		if (dup2(pipes.pipes[cmd_count - 1][0], STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		if (dup2(pipes.pipes[cmd_count][1], STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[cmd_count - 1][0]);
		close(pipes.pipes[cmd_count][1]);
	}
	else if (parcing->fd_in != -2 && parcing->fd_out != -2)
	{
		if (dup2(parcing->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		if (dup2(parcing->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(pipes.pipes[cmd_count - 1][0]);
		close(pipes.pipes[cmd_count][1]);
		(close(parcing->fd_in), close(parcing->fd_out));
	}
	else
		redirection_middle1(parcing, pipes, cmd_count, &status);
	return (status);
}

static int	exec_middle_child(t_args *tmp, int *std,
	t_env **env, t_garbage **garb_coll)
{
	char	**envp;
	char	*cmd_path;
	int		check;
	int		status;

	if (tmp->need_to_exit == 1)
		return (tmp->need_to_exit);
	status = exec_built_in(tmp->args, std, env, garb_coll);
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

void	in_middle_childs1(t_args *tmp, t_pipes pipes,
	int cmd_count, t_env_garb middle)
{
	int	status;

	if (!tmp->args || !tmp->args[0])
	{
		if (tmp->need_to_exit == 1)
			exit(tmp->need_to_exit);
		exit(0);
	}
	if (tmp->need_to_exit == 1)
		exit(tmp->need_to_exit);
	middle_pipe_close(pipes.pipes, cmd_count);
	redirection_middle(tmp, pipes, cmd_count);
	status = exec_middle_child(tmp, pipes.std, middle.env, middle.garb_coll);
	free_middle_child(pipes, cmd_count, middle.env, middle.garb_coll);
	exit(status);
}

void	in_middle_childs(t_args **parcing, t_pipes pipes,
	t_env **env, t_garbage **garb_coll)
{
	t_args		*tmp;
	t_env_garb	middle;
	int			cmd_count;
	int			id;

	cmd_count = 1;
	tmp = (*parcing)->next;
	(1) && (middle.env = env, middle.garb_coll = garb_coll);
	g_sig = 1;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		id = fork();
		if (id == 0)
		{
			signals_reset();
			in_middle_childs1(tmp, pipes, cmd_count, middle);
		}
		else if (id == -1)
			perror("fork");
		tmp = tmp->next;
		cmd_count++;
	}
}
