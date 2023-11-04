/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:40:37 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/04 11:47:28 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(int a)
{
	if (a == SIGINT)
	{
		if (g_signo[1] == 0 && g_signo[2] != 0)
		{
			g_signo[1] = 1;
			close(g_signo[0]);
		}
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		if (g_signo[2] == 0)
			rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, test);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
