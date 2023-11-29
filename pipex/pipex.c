/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:36:07 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 04:46:21 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	you_need_hd(t_mini *shell)
{
	char	*path;
	char	*itoto;
	int		fd;

	itoto = NULL;
	path = NULL;
	fd = 0;
	if (have_you_hd(shell) > 0)
	{
		itoto = ft_itoa(shell->nb_heredoc);
		path = ft_strjoin("/tmp/.tmp.heredoc", itoto);
		fd = open(path, O_RDONLY, 0644);
		dup2(fd, 0);
		close(fd);
		free(itoto);
		free(path);
	}
}

void	are_you_builtin(t_mini *shell, char **builtin)
{
	t_tokenisation	*tmp;

	tmp = shell->all->head_process;
	while (tmp)
	{
		if (tmp->type == BUILTIN)
		{
			*builtin = tmp->separated;
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_builtin(t_mini *shell)
{
	char			*builtin;

	builtin = NULL;
	are_you_builtin(shell, &builtin);
	if (twin_char(builtin, "echo"))
		return (ft_echo(shell));
	if (twin_char(builtin, "cd"))
	{
		g_ret_val = 0;
		return (ft_cd(shell));
	}
	if (twin_char(builtin, "pwd"))
		return (ft_pwd(shell));
	if (twin_char(builtin, "export"))
		return (ft_export(shell->all->wordi, shell));
	if (twin_char(builtin, "unset"))
		return (ft_unset(shell->all->wordi, shell));
	if (twin_char(builtin, "env"))
		return (ft_env(shell));
	if (twin_char(builtin, "exit"))
		return (ft_exit(shell));
	return ;
}

void	*help_organisation(t_mini *shell, int part)
{
	if (part == 1)
	{
		shell->before = dup(0);
		shell->after = dup(1);
		if (!find_last_heredoc(shell))
			return (NULL);
		shell->all = shell->head_all;
		if (shell->nb_heredoc)
			ft_heredoc(shell);
	}
	else if (part == 2)
	{
		g_ret_val = 0;
		ft_last(shell);
		dup2(shell->before, 0);
		dup2(shell->after, 1);
		close(shell->before);
		close(shell->after);
		ft_close(shell);
	}
	return ("good");
}

void	*ft_organisation(t_mini *shell)
{
	shell->status = 0;
	if (help_organisation(shell, 1) == NULL)
		return (NULL);
	if (shell->nb_process == 1)
		return (just_one_process(shell), "good");
	while (shell->all->next)
	{
		g_ret_val = 0;
		if (have_you_hd(shell) == 0)
			fork_with_us(shell);
		else
			fork_with_hd(shell);
		shell->all = shell->all->next;
	}
	help_organisation(shell, 2);
	while (errno != ECHILD)
	{
		wait(&shell->status);
		if (WIFEXITED(shell->status))
			g_ret_val = WEXITSTATUS(shell->status);
	}
	free_double_char(shell->heredoc_tab);
	shell->heredoc_tab = NULL;
	return ("good");
}
