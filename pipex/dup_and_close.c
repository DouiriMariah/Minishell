/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 01:45:56 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:09:18 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_files(t_mini *shell)
{
	if (shell->all->file1 != 0)
		dup2(shell->all->file1, 0);
	if (shell->all->file2 != 1)
		dup2(shell->all->file2, 1);
}

void	close_child(t_mini *shell)
{
	int	i;

	i = 3;
	while (i < 123)
		close(i++);
	free_double_char(shell->heredoc_tab);
	ft_free_test(shell);
	free_exit(shell);
	close(shell->after);
	close(shell->before);
}

void	close_child_alone(t_mini *shell)
{
	int	i;

	i = 3;
	while (i < 123)
		close(i++);
	close(shell->after);
	close(shell->before);
}

void	ft_close(t_mini *shell)
{
	t_exec	*tmp;

	tmp = shell->head_all;
	while (tmp)
	{
		if (tmp->file1 != 0)
			close(tmp->file1);
		if (tmp->file2 != 1)
			close(tmp->file2);
		tmp = tmp->next;
	}
}
