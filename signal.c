/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:40:37 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 14:48:19 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(int a)
{
	if (a == SIGINT)
	{
		if (g_signo[1] == 0)
		{
			g_signo[1] = 1;
			close(g_signo[0]);
		}
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, test);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

// void	close_doc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_signo = 1;
// 		rl_replace_line("", 0);
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	doc_signal(void)
// {
// 	signal(SIGINT, close_doc);
// }
