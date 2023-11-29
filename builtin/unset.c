/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:46:12 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/17 17:49:23 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	ft_unset(char **str, t_mini *shell)
{
	int	i;

	i = 0;
	g_ret_val = 0;
	while (str[i])
	{
		if (str[i][0] && str[i][0] == '_' && !str[i][1])
			;
		else
			ft_one_unset(str[i], shell);
		i++;
	}
}

void	unset_bis(t_ecosystem *unset, t_mini *shell, int who)
{
	t_ecosystem	*tmp;

	if (who == 1)
	{
		tmp = unset->next;
		unset->next = tmp->next;
	}
	if (who == 2)
	{
		tmp = unset;
	}
	free(tmp->tree);
	free(tmp->leaf);
	free(tmp);
	shell->env_length--;
}

void	ft_one_unset(char *str, t_mini *shell)
{
	t_ecosystem	*unset;

	unset = shell->head;
	if (get_env(str, shell))
	{
		if (twin_char(unset->tree, str))
		{
			shell->head = shell->head->next;
			unset_bis(unset, shell, 2);
			update_env(shell);
			return ;
		}
		while (unset && unset->next)
		{
			if (twin_char(unset->next->tree, str))
			{
				unset_bis(unset, shell, 1);
				break ;
			}
			unset = unset->next;
		}
		update_env(shell);
	}
}
