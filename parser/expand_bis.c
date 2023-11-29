/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:19 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 16:19:22 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	if_tmp_one(t_mini *shell, char *str)
{
	while (shell->j < shell->i - 1 && str[shell->j] != '$')
	{
		if (ft_separateur(str[shell->j]) != 2)
			shell->new_str++;
		shell->j++;
	}
	if (ft_double_chev(str, shell->i - 1) > 0)
	{
		while (shell->j < shell->i - 1)
		{
			shell->new_str++;
			shell->j++;
		}
	}
}

void	ft_continu(char *str, t_mini *shell, int tmp)
{
	if (tmp == 0)
	{
		shell->i = 0;
		shell->j = 0;
		shell->old_str = 0;
		shell->old_str = ft_strlen(str);
		shell->newi = NULL;
	}
	else if (tmp == 1)
		if_tmp_one(shell, str);
	else if (tmp == 2)
	{
		shell->j = shell->i + 1;
		quote(str, &shell->i);
		shell->new_str += shell->i - shell->j -1;
	}
}

void	fill_tmp_gm2(t_mini *shell, char *str, int who, char *tmp)
{
	int	v;

	v = 0;
	if (who == 1)
	{
		shell->j++;
		while (!ft_separateur(str[shell->j]) && shell->i - 1 > shell->j)
			tmp[v++] = str[shell->j++];
	}
	else if (who == 2)
	{
		shell->i++;
		if (str[shell->i] == '?')
			tmp[v++] = str[shell->i++];
		else
		{
			while (str[shell->i] && !ft_separateur(str[shell->i]))
				tmp[v++] = str[shell->i++];
		}
	}
	tmp[v] = '\0';
}

void	money_2_help(t_mini *shell, char *tmp)
{
	int		i;

	i = 0;
	if (tmp[0] == '?')
	{
		shell->newi = ft_itoa(g_ret_val);
		shell->dol = 1;
	}
	else if (tmp)
	{
		shell->dol = 0;
		shell->newi = get_env(tmp, shell);
	}
	if (shell->newi)
	{
		while (shell->newi && shell->newi[i])
		{
			shell->newi[i] = -shell->newi[i];
			i++;
		}
	}
	shell->new_str = shell->new_str + ft_strlen(shell->newi);
	free(tmp);
}

int	give_me_the_money2(char *str, t_mini *shell, int who)
{
	int		v;
	char	*tmp;

	v = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (shell->old_str + 1));
	if (!tmp)
		return (-1);
	if (shell->dol)
	{
		free(shell->newi);
		shell->newi = NULL;
	}
	fill_tmp_gm2(shell, str, who, tmp);
	shell->dol = 0;
	money_2_help(shell, tmp);
	return (0);
}
