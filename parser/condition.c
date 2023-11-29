/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:56:27 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 19:56:31 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

extern int	g_ret_val;

void	special_condi(t_mini *shell, char *str, int who)
{
	char	*tmp;

	tmp = NULL;
	if (who == 1)
		give_me_the_money2(str, shell, 2);
	else
		give_me_the_money2(str, shell, 1);
	shell->final_str[shell->v] = '\0';
	tmp = ft_strdup(shell->final_str);
	free(shell->final_str);
	shell->final_str = ft_strjoini(tmp, shell->newi, shell);
	free(tmp);
	tmp = NULL;
	shell->v = ft_strlen(shell->final_str);
}

void	second_condi(t_mini *shell, char *str)
{
	ft_continu2(str, shell, 0);
	while (shell->j < (shell->i - 1))
	{
		while (str[shell->j] && (str[shell->j] != '$'
				|| not_alphanumeric(str[shell->j + 1]))
			&& shell->j < (shell->i - 1))
		{
			shell->final_str[shell->v] = -str[shell->j];
			shell->j++;
			shell->v++;
		}
		if (ft_separateur(str[shell->j]) == 2
			&& !not_alphanumeric(str[shell->j + 1])
			&& ft_double_chev(str, shell->j) <= 0)
		{
			special_condi(shell, str, 2);
		}
		else if (ft_double_chev(str, shell->j) > 0)
		{
			while (str[shell->j] && shell->j < shell->i - 1)
				shell->final_str[shell->v++] = -str[shell->j++];
		}
	}
}

void	third_condi(t_mini *shell, char *str, int who)
{
	if (who == 4)
	{
		while (str[shell->i] && sep(str[shell->i]) == 5)
			shell->final_str[shell->v++] = str[shell->i++];
	}
	else if (who == 5)
	{
		while (str[shell->i] && str[shell->i] == ' ')
			shell->final_str[shell->v++] = str[shell->i++];
	}
}

void	condi(t_mini *shell, char *str, int who)
{
	if (who == 1)
	{
		if (str[shell->i] == '$' && !not_alphanumeric(str[shell->i + 1])
			&& ft_double_chev(str, shell->i) <= 0)
		{
			special_condi(shell, str, 1);
		}
		else
			shell->final_str[shell->v++] = str[shell->i++];
	}
	else if (who == 3)
	{
		ft_continu(str, shell, 2);
		while (str[shell->j] && str[shell->j] != '\'')
		{
			shell->final_str[shell->v] = -str[shell->j];
			shell->j++;
			shell->v++;
		}
	}
}
