/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:49:09 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 19:49:13 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

int	open_files(t_mini *shell, int type, char *sep)
{
	if (type == FILE_IN)
	{
		if (shell->all->file1 != 0)
			close(shell->all->file1);
		shell->all->file1 = open(sep, O_RDONLY, 0644);
		return (shell->all->file1);
	}
	else if (type == FILEOUT)
	{
		if (shell->all->file2 != 1)
			close(shell->all->file2);
		shell->all->file2 = open(sep, O_CREAT | O_RDWR | O_TRUNC, 0644);
		return (shell->all->file2);
	}
	else if (type == FILE_APPEND)
	{
		if (shell->all->file2 != 1)
			close(shell->all->file2);
		shell->all->file2 = open(sep, O_CREAT | O_RDWR | O_APPEND, 0644);
		return (shell->all->file2);
	}
	return (0);
}

void	*pre_check(t_mini *shell)
{
	t_tokenisation	*tmp;

	tmp = shell->all->head_process;
	shell->all->file1 = 0;
	shell->all->file2 = 1;
	while (tmp)
	{
		if (tmp->type == FILE_IN)
		{
			if (open_files(shell, tmp->type, tmp->separated) == -1)
				return (perror(tmp->separated), g_ret_val = errno, NULL);
		}
		else if (tmp->type == FILE_APPEND || tmp->type == FILEOUT)
		{
			if (open_files(shell, tmp->type, tmp->separated) == -1)
				return (perror(tmp->separated), g_ret_val = errno, NULL);
		}
		else if (tmp->type == HEREDOC)
		{
			shell->heredoc_tab[shell->v] = NULL;
			shell->heredoc_tab[shell->v++] = ft_strdup(tmp->separated);
		}
		tmp = tmp->next;
	}
	return ("good");
}

void	*find_last_heredoc(t_mini *shell)
{
	shell->all = shell->head_all;
	shell->heredoc_tab = NULL;
	shell->heredoc_tab = malloc(sizeof(char *) * (shell->nb_heredoc + 1));
	if (!shell->heredoc_tab)
		return (NULL);
	shell->v = 0;
	while (shell->all)
	{
		if (!pre_check(shell))
		{
			g_ret_val = 1;
			return (NULL);
		}
		shell->all = shell->all->next;
	}
	shell->heredoc_tab[shell->v] = 0;
	return ("good");
}

int	are_you_finished(t_mini *shell, char *str)
{
	static int	nb_heredoc = 0;
	char		*path;
	char		*itoto;

	if (ft_strcmp(str, shell->heredoc_tab[nb_heredoc]) == 0)
	{
		nb_heredoc++;
		if (!shell->heredoc_tab[nb_heredoc])
		{
			if (nb_heredoc == shell->nb_heredoc)
				nb_heredoc = 0;
			return (1);
		}
		close(shell->stock_hdoc);
		shell->stock_hdoc = 0;
		itoto = ft_itoa(nb_heredoc + 1);
		path = ft_strjoin("/tmp/.tmp.heredoc", itoto);
		shell->stock_hdoc = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		free(itoto);
		free(path);
		return (2);
	}
	return (0);
}
