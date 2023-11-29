/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forki.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:46:10 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 19:46:17 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

void	child_alone(t_mini *shell)
{
	int		status;

	status = 0;
	shell->fork = fork();
	run_signals(2);
	if (shell->fork < 0)
		return ;
	else if (shell->fork == 0)
	{
		you_need_hd(shell);
		dup_files(shell);
		if (shell->all->wordi[0])
		{
			ft_exec(shell);
			g_ret_val = 127;
		}
		else
			g_ret_val = 0;
		close_child(shell);
		exit(g_ret_val);
	}
	waitpid(shell->fork, &status, 0);
	if (WIFEXITED(status))
		g_ret_val = WEXITSTATUS(status);
}

void	just_one_process(t_mini *shell)
{
	free_double_char(shell->heredoc_tab);
	shell->heredoc_tab = NULL;
	if (shell->all->builtin)
	{
		dup_files(shell);
		ft_builtin(shell);
	}
	else
		child_alone(shell);
	dup2(shell->before, 0);
	dup2(shell->after, 1);
	close_child_alone(shell);
}

void	our_child(t_mini *shell)
{
	dup2(shell->pipe_fd[1], 1);
	close(shell->pipe_fd[0]);
	dup_files(shell);
	if (shell->all->builtin)
		ft_builtin(shell);
	else if (shell->all->wordi[0])
	{
		ft_exec(shell);
		g_ret_val = 127;
	}
	close_child(shell);
	close(shell->pipe_fd[1]);
	exit(g_ret_val);
}

void	fork_with_us(t_mini *shell)
{
	if (pipe(shell->pipe_fd) == -1)
		perror("pipe");
	shell->fork = fork();
	run_signals(2);
	if (shell->fork < 0)
		return ;
	else if (shell->fork == 0)
		our_child(shell);
	else
	{
		dup2(shell->pipe_fd[0], 0);
		close(shell->pipe_fd[1]);
	}
	close(shell->pipe_fd[1]);
	close(shell->pipe_fd[0]);
}

void	ft_last(t_mini *shell)
{
	int		status;

	status = 0;
	shell->fork = fork();
	run_signals(2);
	if (shell->fork == 0)
	{
		you_need_hd(shell);
		dup_files(shell);
		if (shell->all->builtin)
			ft_builtin(shell);
		else if (shell->all->wordi[0])
		{
			ft_exec(shell);
			g_ret_val = 127;
		}
		else
			g_ret_val = 0;
		close_child(shell);
		exit(g_ret_val);
	}
}
