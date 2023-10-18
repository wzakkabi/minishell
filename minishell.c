/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/18 04:50:02 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

void	minishell_loop(t_ast *tool, t_lexer *token, t_env *env)
{
	char	*input;

	input = readline("minishell~>");
	if (input == NULL || input[0] == 0 || check_quote(input) == 1)
	{
		free(input);
		minishell_loop(tool, token, env);
	}
	token = ft_token(input);
	while (token->prev != NULL)
		token = token->prev;
	check_syntax_error(token);
	check_expand(token, env);
	remove_qost(token, 0, 0, 0);
	tool = split_to_ast(token);
	if (check_syntax_error_again(tool) != 0)
		minishell_loop(tool, token, env);
	execute(tool, env);
}

void	make_env_node(char **env, t_env *node)
{
	int	cnt_x;
	int	cnt_y;

	cnt_x = 0;
	cnt_y = 0;
	while (env[cnt_y])
	{
		while (env[cnt_y][cnt_x] != '=' && env[cnt_y][cnt_x])
			cnt_x++;
		node->key = ft_substr2(env[cnt_y], 0, cnt_x);
		node->value = ft_substr2(env[cnt_y], cnt_x + 1, ft_strlen(env[cnt_y]));
		cnt_x = 0;
		cnt_y++;
		node->next = envnode();
		node->next->prev = node;
		node = node->next;
	}
}

int	main(int c, char **av, char **grep_env)
{
	t_ast	*tool;
	t_lexer	*token;
	t_env	*env;

	if (c > 1 || av[1])
	{
		printf("this program dont take paramiter");
		exit(0);
	}
	env = envnode();
	make_env_node(grep_env, env);
	minishell_loop(tool, token, env);
	return (0);
}
