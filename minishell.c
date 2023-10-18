/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:30:45 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/10/18 04:43:39 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

t_ast	*newnode(void)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->str = (char **)calloc(sizeof(char *), 500);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lxnewnode(void)
{
	t_lexer		*new;
	static int	i;

	i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->num_node = i;
	new->next = NULL;
	new->prev = NULL;
	i++;
	return (new);
}

t_env	*envnode(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void ft_print(t_lexer *lx)
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

void ft_printast(t_ast *lx)
{
	int x = 0;
	while(lx->prev != NULL)
		lx = lx->prev;
	while(lx != NULL)
	{
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
		printf("%d\n", lx->builtins);
		x = 0;
		lx = lx->next;
	}
}





void    minishell_loop(t_ast *tool, t_lexer *token, t_env *env)
{
	char *input;
	
	input = readline("minishell~>");
	if(input == NULL || input[0] == 0 || check_quote(input) == 1)
	{
		free(input);
		minishell_loop(tool, token, env);
	}
	token = ft_token(input);
	while(token->prev != NULL)
		token = token->prev;
	check_syntax_error(token);
	check_expand(token, env);
	remove_qost(token, 0, 0, 0);
	//ft_print(token);
	//token = remove_emty_node(token);
	tool = split_to_ast(token);
	if(check_syntax_error_again(tool) != 0)
		minishell_loop(tool, token, env);
	ft_printast(tool);
	//execute(tool, env);
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

int main(int c, char **av, char **grep_env)
{
	t_ast *tool;
	t_lexer *token;
	t_env *env;
	
	
	if (c > 1 || av[1])
	{
		printf("this program dont take paramiter");
		exit(0);
	}
	env = envnode();
	make_env_node(grep_env, env);
	// while(env->next)
	// {
	// 	printf("node->key == (%s)", env->key);
	// 	printf("node->value == (%s)\n", env->value);
	// 	env = env->next;
	// }
	//exit(0);
	minishell_loop(tool, token, env);
	return 0;
}