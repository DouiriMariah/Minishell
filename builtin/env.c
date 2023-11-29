/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:45:59 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 04:15:07 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

void	ft_cut_env(t_mini *shell)
{
	int			i;
	char		**split;
	t_ecosystem	*tmp;

	split = NULL;
	i = 0;
	while (shell->envp[i])
	{
		split = ft_split(shell->envp[i], '=');
		tmp = ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1]));
		if (i == 0)
		{
			shell->envir = tmp;
			shell->head = shell->envir;
		}
		else
		{
			shell->envir->next = tmp;
			shell->envir = shell->envir->next;
		}
		free_double_char(split);
		i++;
	}
	shell->env_length = i + 1;
}

char	*get_env(char *str, t_mini *shell)
{
	t_ecosystem	*tmp;

	if (!str)
		return (NULL);
	tmp = shell->head;
	while (tmp)
	{
		if (twin_char(tmp->tree, str))
		{
			if (!tmp->leaf)
				return ("(null)");
			return (tmp->leaf);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_print_env(t_mini*shell)
{
	t_ecosystem	*tmp;

	tmp = shell->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->tree, tmp->leaf);
		tmp = tmp->next;
	}
}

void	ft_env(t_mini *shell)
{
	if (shell->all->wordi[0])
	{
		if (shell->all->wordi[0][0] == '-' && shell->all->wordi[0][1])
		{
			error_message(B_ERR_ENV1, shell->all->wordi[0], A_ERR_ENV1, 2);
			g_ret_val = 125;
			return ;
		}
		error_message(B_ERR_ENV2, shell->all->wordi[0], A_ERR_ENV2, 2);
		g_ret_val = 127;
		return ;
	}
	ft_print_env(shell);
	g_ret_val = 0;
}

void	update_env(t_mini *shell)
{
	int			i;
	t_ecosystem	*tmp;
	char		*str;

	i = 0;
	str = NULL;
	free_double_char(shell->envp);
	shell->envp = NULL;
	shell->envp = malloc(sizeof(char *) * (shell->env_length + 1));
	if (!shell->envp)
		return ;
	tmp = shell->head;
	while (tmp)
	{
		str = ft_strjoin(tmp->tree, "=");
		shell->envp[i] = ft_strjoin(str, tmp->leaf);
		tmp = tmp->next;
		free(str);
		str = NULL;
		i++;
	}
	shell->envp[i] = 0;
}
