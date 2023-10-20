/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/20 20:32:31 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

void	ft_free_token(t_lexer *lx)
{
	while (lx && lx->prev != NULL)
		lx = lx->prev;
	while (lx && lx->next)
	{
		if (lx->word)
			free(lx->word);
		if (lx->prev)
			free(lx->prev);
		lx = lx->next;
	}
	if (lx && lx->prev)
		free(lx->prev);
	if (lx)
		free(lx);
}

void	ft_free_ast(t_ast *tool)
{
	t_ast	*replace;

	while (tool->prev)
		tool = tool->prev;
	while (tool)
	{
		ft_free_token(tool->token);
		free(tool->str);
		ft_free_token(tool->redirections);
		replace = tool;
		tool = tool->next;
		free(replace);
	}
	free(tool);
}

void	ft_print(t_lexer *lx)
{
	while(lx->prev != NULL)
		lx = lx->prev;
	while(lx->next != NULL)
	{	
		if(lx->word != NULL )
			printf("word = (%s) %d\n", lx->word, lx->num_node);
		else
			printf("token = (%d) %d\n", lx->token, lx->num_node);
		lx = lx->next;
	}
}

void	ft_printast(t_ast *lx)
{
	int x = 0;
	int tree = 0;
	
	while(lx->prev != NULL)
		lx = lx->prev;
	while(lx != NULL)
	{
		printf("ast-------------------:>node == (%d)\n", tree++);
		while(lx->str[x])
		{
			printf("ast word == (%s)\n", lx->str[x]);
			x++;
		}
		while(lx->redirections && lx->redirections->prev)
			lx->redirections = lx->redirections->prev;
		while(lx->redirections)
		{
			printf("word = (%s) and token = (%d)\n", lx->redirections->word, lx->redirections->token);
			lx->redirections = lx->redirections->next;
		}
		x = 0;
		lx = lx->next;
	}
}


void	minishell_loop(t_env *env)
{
	t_ast	*tool;
	t_lexer	*token;
	char	*input;

	while (1)
	{
		input = readline("minishell~>");
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else if(input[0] == 0)
			ft_exit(env, 0);
		else if (check_quote(input, env) != 1)
		{
			add_history(input);
			token = ft_token(input);
			//ft_print(token);
			if(check_syntax_error(env, token) == 0)
			{
				check_expand(token, env);
				remove_qost(token, 0, 0, 0);
				tool = split_to_ast(token);
				if (check_syntax_error_again(tool) != 0)
				{
					ft_exit(env, 2);
					ft_free_ast(tool);
				}
				else
				{
					ft_printast(tool);
					//execute(tool, env);
					ft_free_ast(tool);
				}
			}
		}
		free(input);
	}
}

void	make_env_node(char **env, t_env *node)
{
	int	cnt_x;
	int	cnt_y;

	cnt_y = ((cnt_x = 0), 0);
	while (env[cnt_y])
	{
		while (env[cnt_y][cnt_x] != '=' && env[cnt_y][cnt_x])
			cnt_x++;
		node->key = ft_substr2(env[cnt_y], 0, cnt_x);
		node->value = ft_substr2(env[cnt_y], cnt_x + 1, ft_strlen(env[cnt_y]));
		node->print_or_not = 1;
		cnt_x = 0;
		cnt_y++;
		node->next = envnode();
		node->next->prev = node;
		node = node->next;
	}
	node->key = ft_substr("?", 0, 1);
	node->value = ft_itoa(0);
	node->print_or_not = 0;
}

void ft_exit(t_env *env, int return_status)
{
	t_env *tmp;
	tmp = get_env_var(env, "?");
	tmp->value = ft_itoa(return_status);
}

void	test(int a)
{
	if(a == SIGINT)
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

int	main(int c, char **av, char **grep_env)
{
	t_env	*env;

	if (c > 1 || av[1])
	{
		printf("this program dont take paramiter");
		exit(0);
	}
	ft_signal();
	env = envnode();
	make_env_node(grep_env, env);
	// while(env->next)
	// {
	// 	printf("node->key == (%s)", env->key);
	// 	printf("node->value == (%s)\n", env->value);
	// 	env = env->next;
	// }
	minishell_loop(env);
	return (0);
}
