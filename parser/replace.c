/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:02:26 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:17:01 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	sep(char c)
{
	if (c == ' ')
		return (2);
	else if (c == '\"')
		return (3);
	else if (c == '\'')
		return (4);
	else if (not_alphanumeric(c))
		return (5);
	return (0);
}

char	*ft_strjoini(char *s1, char *s2, t_mini *shell)
{
	char	*res;
	int		i;
	int		v;

	res = malloc((shell->new_str + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	v = 0;
	while (s1 && s1[i])
	{
		res[v] = s1[i];
		i++;
		v++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		res[v] = s2[i];
		i++;
		v++;
	}
	res[v] = '\0';
	return (res);
}

void	fill_new_str(t_mini *shell, char *str)
{
	shell->v = 0;
	shell->i = 0;
	shell->j = 0;
	shell->final_str = NULL;
	shell->final_str = malloc(sizeof(char) * (shell->new_str + 1));
	if (!shell->final_str)
		return ;
	shell->v = 0;
	while (shell->v < shell->new_str && str[shell->i])
	{
		if (str[shell->i] && !sep(str[shell->i]))
			condi(shell, str, 1);
		else if (str[shell->i] == '\"')
			second_condi(shell, str);
		else if (sep(str[shell->i]) == 4)
			condi(shell, str, 3);
		else if (sep(str[shell->i]) == 5)
			third_condi(shell, str, 4);
		else
			third_condi(shell, str, 5);
	}
	shell->final_str[shell->v] = '\0';
}
