/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:29:03 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:19:20 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	ft_continu2(char *str, t_mini *shell, int who)
{
	if (who == 0)
	{
		shell->j = shell->i + 1;
		quote(str, &shell->i);
	}
	else if (who == 1)
	{
		if (str[shell->i] == '\'')
			ft_continu(str, shell, 2);
		else if (ft_separateur(str[shell->i]) == 2
			&& !not_alphanumeric(str[shell->i + 1])
			&& (ft_double_chev(str, shell->i) <= 0
				|| str[shell->i + 1] == '?'))
			give_me_the_money2(str, shell, 2);
		else
		{
			shell->new_str++;
			shell->i++;
		}
	}
}

int	ft_double_chev(char *str, int max)
{
	int	i;
	int	stock;

	i = 0;
	stock = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i] && str[i] == '<' && str[i + 1] == '<')
	{
		i = i + 2;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\"' || str[i] == '$')
		{
			if (str[i] == '\"')
				quote(str, &i);
			else if (str[i] == '$')
			{
				while (str[i] && str[i] != ' ')
					i++;
			}
			stock = i;
		}
	}
	return (stock - max);
}

int	help_final_string(t_mini *shell, char *str)
{
	ft_continu2(str, shell, 0);
	while (shell->j < (shell->i - 1))
	{
		ft_continu(str, shell, 1);
		if (ft_separateur(str[shell->j]) == 2
			&& !not_alphanumeric(str[shell->j + 1])
			&& ft_double_chev(str, shell->i - 1) <= 0)
		{
			if (str[shell->j + 1]
				&& ft_separateur(str[shell->j + 1]) != 2)
			{
				shell->j++;
				if (give_me_the_money2(str, shell, 1) == -1)
					return (0);
			}
			else
				shell->j++;
		}
		shell->new_str++;
		shell->j++;
	}
	return (1);
}

int	final_string(char *str, t_mini *shell)
{
	shell->new_str = 0;
	ft_continu(str, shell, 0);
	while (str[shell->i])
	{
		if (str[shell->i] == '\"')
		{
			if (help_final_string(shell, str) == 0)
				return (0);
		}
		else
			ft_continu2(str, shell, 1);
	}
	if (str[shell->i])
		return (0);
	return (shell->new_str);
}
