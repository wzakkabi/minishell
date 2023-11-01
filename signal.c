/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:40:37 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/01 18:43:47 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(int a)
{
	if (a == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, &test);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
// void	close_doc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		write(1, "\n", 1);
// 		// rl_on_new_line();
// 		// rl_redisplay();
// 	}
// }

// void	signal2(void)
// {
// 	signal(SIGINT, close_doc);
// }