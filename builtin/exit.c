/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:45:11 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 04:19:33 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	free_exit(t_mini *shell)
{
	int	i;

	i = 3;
	if (shell->dol)
	{
		free(shell->newi);
		shell->newi = NULL;
	}
	shell->dol = 0;
	ft_free_env(shell->head, shell);
	while (i < 123)
		close(i++);
	rl_clear_history();
}

void	ft_exit(t_mini *shell)
{
	write(1, "exit\n", 5);
	if (shell->all->wordi[0])
	{
		if (shell->all->wordi[1])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			g_ret_val = 1;
			return ;
		}
		if (!shell->all->wordi[1] && ft_atoi(shell->all->wordi[0]))
		{
			g_ret_val = ft_atoi(shell->all->wordi[0]);
			if (g_ret_val > 255 || g_ret_val < 0)
				g_ret_val = 255;
		}
		else
		{
			error_message(B_ERR_EXIT, shell->all->wordi[0], A_ERR_EXIT, 2);
			g_ret_val = 2;
		}
	}
	ft_free_test(shell);
	free_exit(shell);
	exit(g_ret_val);
}

void	error_message(char *b_w, char *wordi, char *a_w, int fd)
{
	char	*first;
	char	*joined;

	first = ft_strjoin(b_w, wordi);
	joined = ft_strjoin(first, a_w);
	free(first);
	ft_putstr_fd(joined, fd);
	free(joined);
}
