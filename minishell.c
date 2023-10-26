/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/26 10:18:42 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

void	minishell_loop_helper(t_env *env, t_ast *tool, t_lexer *token)
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
		execute(tool, env);
		ft_free_ast(tool);
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
		else if (input[0] == 0)
			ft_exit(env, 0);
		else if (input[0] != 0 && check_quote(input, env, 0) != 1)
		{
			add_history(input);
			token = ft_token(input);
			if (check_syntax_error(env, token) == 0)
				minishell_loop_helper(env, tool, token);
		}
		free(input);
	}
}

void	ft_exit(t_env *env, int return_status)
{
	t_env	*tmp;

	tmp = get_env_var(env, "?");
	if (tmp->value)
		free(tmp->value);
	tmp->value = ft_itoa(return_status);
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
	minishell_loop(env);
	return (0);
}
