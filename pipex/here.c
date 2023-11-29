/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 05:17:34 by amattei           #+#    #+#             */
/*   Updated: 2022/08/22 05:17:51 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	have_you_hd(t_mini *shell)
{
	int				nb_d;
	t_tokenisation	*tmp;

	nb_d = 0;
	tmp = shell->all->head_process;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			nb_d++;
		tmp = tmp->next;
	}
	shell->nb_heredoc += nb_d;
	return (nb_d);
}

void	loop_in_hd(t_mini *shell)
{
	int		ayf;
	char	*line;

	ayf = 0;
	line = NULL;
	while (42)
	{
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd(ERR_HD_EOF, 2);
			break ;
		}	
		ayf = are_you_finished(shell, line);
		if (ayf == 1)
			break ;
		else if (ayf == 0)
			write(shell->stock_hdoc, line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
}

void	ft_heredoc(t_mini *shell)
{
	char	*path;

	shell->good_stdout = dup(1);
	path = "/tmp/.tmp.heredoc1";
	shell->stock_hdoc = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	run_signals(4);
	loop_in_hd(shell);
	shell->nb_heredoc = 0;
	dup2(shell->good_stdout, 1);
	shell->good_stdout = 0;
}

void	child_hd(t_mini *shell)
{
	int		fd;
	char	*path;
	char	*itoto;

	itoto = NULL;
	path = NULL;
	fd = 0;
	itoto = ft_itoa(shell->nb_heredoc);
	path = ft_strjoin("/tmp/.tmp.heredoc", itoto);
	fd = open(path, O_RDONLY, 0644);
	dup2(fd, 0);
	close(fd);
	free(itoto);
	free(path);
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
}

void	fork_with_hd(t_mini *shell)
{
	if (pipe(shell->pipe_fd) == -1)
		perror("pipe");
	shell->fork = fork();
	run_signals(2);
	if (shell->fork < 0)
		return ;
	else if (shell->fork == 0)
	{
		child_hd(shell);
		close_child(shell);
		close(shell->pipe_fd[1]);
		exit(g_ret_val);
	}
	else
	{
		dup2(shell->pipe_fd[0], 0);
		close(shell->pipe_fd[1]);
	}
	close(shell->pipe_fd[0]);
}
