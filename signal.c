/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:40:37 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/11/03 09:06:35 by wzakkabi         ###   ########.fr       */
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

void	close_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signo = 1;
		write(STDOUT_FILENO, 0, 1);
		rl_replace_line("", 0);
	}
}

void	doc_interrupt(int sig)
{
	(void)sig;
}

void	doc_signal(void)
{
	signal(SIGINT, close_doc);
	signal(SIGQUIT, doc_interrupt);
}
