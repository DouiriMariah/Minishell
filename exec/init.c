/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:32:35 by amattei           #+#    #+#             */
/*   Updated: 2022/08/22 04:36:42 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	copy_env(t_mini *shell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->envp = NULL;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return ;
	i = 0;
	while (env[i])
	{
		shell->envp[i] = ft_strdup(env[i]);
		i++;
	}
	shell->envp[i] = 0;
}

void	init_env(char **env, t_mini *shell)
{
	if (env[0])
	{
		copy_env(shell, env);
		ft_cut_env(shell);
	}
	else
	{
		shell->envp = malloc(sizeof(char *) * 4);
		if (!shell->envp)
			return ;
		shell->envp[0] = ft_strdup(ENV_I);
		shell->envp[1] = ft_strdup("SHLVL=1");
		shell->envp[2] = ft_strdup("_=/usr/bin/env");
		shell->envp[3] = 0;
		ft_cut_env(shell);
		ft_print_env(shell);
		shell->env_length = 3;
	}
}

void	init_data(char **env, t_mini *shell)
{
	shell->nb_process = 1;
	shell->old_str = 0;
	shell->new_str = 0;
	shell->newi = NULL;
	shell->final_str = NULL;
	shell->head = NULL;
	shell->process = NULL;
	shell->head_all = NULL;
	shell->after = 0;
	shell->before = 0;
	shell->dol = 0;
	shell->status = 0;
	g_ret_val = 0;
	init_env(env, shell);
}
