/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:45:47 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/19 01:44:55 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	export_option(char **str, t_mini *shell)
{
	(void)shell;
	if (str[0][0] == '-')
	{
		if (str[0][1])
		{
			error_message(B_ERR_EXPORT, str[0], A_ERR_EXPORT, 2);
			ft_putstr_fd("export: usage: export [-fn] ", 2);
			ft_putstr_fd("[name[=value] ...] or export -p\n", 2);
			g_ret_val = 2;
			return (1);
		}
		else
		{
			ft_putstr_fd("bash: export: `-': not a valid identifier\n", 1);
			g_ret_val = 1;
		}
	}
	return (0);
}

void	fillo_export(char *fillo, char *str, int j)
{
	int	v;

	v = 0;
	while (str[++j])
		fillo[v++] = str[j];
	fillo[v] = '\0';
}

int	fill_export(char *fill, char *str, t_mini *shell, int v)
{
	int	j;

	j = -1;
	while (str[++j] && j < v)
		fill[j] = str[j];
	fill[j] = '\0';
	if (get_env(fill, shell))
		ft_one_unset(fill, shell);
	return (j);
}

void	ft_export_bis(t_mini *shell, char *str)
{
	int		v;
	char	*fill;
	char	*fillo;

	v = ft_doublons(str, '=');
	fill = NULL;
	fillo = NULL;
	shell->env_length++;
	if (str && v != 0)
	{
		fill = malloc(sizeof(char) * (v + 1));
		fillo = malloc(sizeof(char) * (ft_strlen(str) - v));
		if (!fillo || !fill)
			return ;
		v = fill_export(fill, str, shell, v);
		fillo_export(fillo, str, v);
		ft_lst_add_back(shell, ft_lstnew(ft_strdup(fill), ft_strdup(fillo)));
		free(fill);
		free(fillo);
	}
	else if (v == 0)
		return ;
}

void	ft_export(char **str, t_mini *shell)
{
	int			i;

	i = 0;
	g_ret_val = 0;
	if (!str[0])
		return ;
	if (export_option(str, shell))
		return ;
	while (str[i])
	{
		if (str[i][0] == '-')
		{
			printf("bash: export: `%s': not a valid identifier\n", str[i]);
			g_ret_val = 1;
		}
		else
		{
			if (!(str[i][0] == '_' && (!str[i][1] || str[i][1] == '=')))
				ft_export_bis(shell, str[i]);
		}
		i++;
	}
	update_env(shell);
}
