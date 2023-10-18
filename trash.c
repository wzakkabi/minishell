// int how_many(char *s, int c)
// {
// 	int x = 0;
// 	int find = 0;

// 	if(!s)
// 		return 0;
// 	while(s[x])
// 	{
// 		if(s[x] == 39)
// 		{
// 			x++;
// 			while(s[x] && s[x] != 39)
// 				x++;
// 		}
// 		if(s[x] == 34)
// 		{
// 			x++;
// 			while(s[x] && s[x] != 34)
// 			{
// 				if(s[x] == c)
// 					find++;
// 				x++;
// 			}
// 		}
// 		if(s[x] == c)
// 			find++;
// 		x++;
// 	}
// 	return find;
// }

/*
while(token->next != NULL)
	{//&& token->word[x] || token->word[x + 1] != ' ' && token->word[x] == '$' && token->word[x]

		dollar = how_many(token->word, '$');
		while(dollar != 0&& token->word)
		{
			while(token->word[x] != '$' )
				x++;
			printf("%d,\n", x);
			c_p_dollar = ++x;
			c_p_key = 0;
			while(token->word[x + c_p_key] != ' ' && token->word[x + c_p_key] != '$' && token->word[x + c_p_key] != '\t' && token->word[x + c_p_key] && token->word[x + c_p_key] != 34)
				c_p_key++;
			key = ft_substr2(token->word, c_p_dollar, c_p_key + x);
			test = get_env_var(env, key);
			if(test)
			{
				new_word = malloc((ft_strlen(token->word) - c_p_key) + ft_strlen(test->value));
				x = 0;
				while(token->word[x] != '$' && token->word)
					new_word[y++] = token->word[x++];
				while(test->value[i])
					new_word[y++] = test->value[i++];
				while(token->word[x + c_p_key])
					new_word[y++] = token->word[x + ++c_p_key];
				new_word[y] = 0;
			}
			else
			{
				new_word = malloc((ft_strlen(token->word) - c_p_key));
				x = 0;
				while(token->word[x] != '$' && token->word)
					new_word[y++] = token->word[x++];
				while(token->word[x + c_p_key])
					new_word[y++] = token->word[x + ++c_p_key];
				new_word[y] = 0;
			}
			free(token->word);
			free(key);
			token->word = new_word;
			dollar--;
			c_p_dollar = 0;
			c_p_key = 0;
			y = 0;
			i = 0;
			x = 0;
		}
		x = 0;
		token = token->next;
	}
*/

// void	check_expand(t_lexer *token, t_env *env)
// {
// 	int x = 0, y = 0, i = 0, dollar = 0;
// 	int c_p_dollar = 0, c_p_key = 0;
// 	char *key;
// 	char *new_word;
// 	t_env *test;

// 	while(token->next)
// 	{
// 		if(token->token == LESS_LESS)
// 		{
// 			token = token->next;
// 			token = token->next;
// 		}
// 		else
// 		{
// 			dollar = how_many(token->word, '$');
// 			while(dollar != 0)
// 			{
// 				while(token->word[x] != '$')
// 					x++;
// 				if(token->word[x + 1] == ' ' || token->word[x + 1] == '\t' || token->word[x + 1] == '\0' || token->word[x + 1] == 34)
// 					x++;
// 				else
// 				{
// 					c_p_dollar = ++x;
// 					c_p_key = 0;
// 					while(token->word[x + c_p_key] != ' ' && token->word[x + c_p_key] != '$' && token->word[x + c_p_key] != '\t' && token->word[x + c_p_key] && token->word[x + c_p_key] != 34)
// 						c_p_key++;
// 					key = ft_substr2(token->word, c_p_dollar, c_p_key + x);
// 					test = get_env_var(env, key);
// 					if(test)
// 					{
// 						new_word = malloc((ft_strlen(token->word) - c_p_key) + ft_strlen(test->value));
// 						c_p_dollar = 0;
// 						while(c_p_dollar < x - 1)
// 							new_word[y++] = token->word[c_p_dollar++];					
// 						while(test->value[i])
// 							new_word[y++] = test->value[i++];
// 						while(token->word[c_p_dollar + c_p_key])
// 							new_word[y++] = token->word[c_p_dollar + ++c_p_key];
// 						new_word[y] = 0;
// 					}
// 					else
// 					{
// 						new_word = malloc((ft_strlen(token->word) - c_p_key));
// 						c_p_dollar = 0;
// 						while(c_p_dollar < x - 1)
// 							new_word[y++] = token->word[c_p_dollar++];
// 						while(token->word[c_p_dollar + c_p_key])
// 							new_word[y++] = token->word[c_p_dollar + ++c_p_key];
// 						new_word[y] = 0;
// 					}
// 					free(token->word);
// 					free(key);
// 					token->word = new_word;
// 					dollar--;
// 					c_p_dollar = 0;
// 					c_p_key = 0;
// 					y = 0;
// 					i = 0;
// 				}
// 				dollar = how_many(token->word + x, '$');
// 			}
// 			token = token->next;
// 			dollar = 0;
// 		}
// 	}
	
// }

// t_lexer	*remove_emty_node(t_lexer *token)
// {
// 	t_lexer *test;
	
// 	while(token->next)
// 	{
// 		if(token->token == -1 && ft_strlen(token->word) == 0)
// 		{
// 			test = token;
// 			if(token->prev)
// 			{
// 				token->prev->next = token->next;
// 				token->next->prev = token->prev;
// 			}
// 			else
// 			{
// 				token = token->next;
// 				token->prev = NULL;
// 			}
// 			 if(test->word)
// 			 	free(test->word);
// 			free(test);
// 			test = NULL;
// 		}
// 		token = token->next;
// 	}
// 	while(token->prev)
// 		token = token->prev;
// 	return token;
// }

// void	remove_qost(t_lexer *token)
// {
// 	char *new_word;
// 	int x = 0, y = 0;
// 	int qst = 0;
// 	while (token->next)
// 	{
// 		while(token->word && token->word[x])
// 		{
// 			if(token->word[x] == 34 || token->word[x] == 39)
// 			{
// 				qst = token->word[x];
// 				new_word = malloc(ft_strlen(token->word) - 2 + 1);
// 				while(y < x)
// 				{
// 					new_word[y] = token->word[y];
// 					y++;
// 				}
// 				x++;
// 				while(token->word[x] && token->word[x] != qst)
// 					new_word[y++] = token->word[x++];
// 				x++;
// 				qst = 0;
// 				while(token->word[x + qst])
// 					new_word[y++] = token->word[x + qst++];
// 				new_word[y] = 0;
// 				y = 0;
// 				free(token->word);
// 				token->word = new_word;
// 			}
// 			x++;
// 		}
// 		y = 0;
// 		x = 0;
// 		token = token->next;
// 	}
// }



// t_lexer	*ft_token(char *ret)
// {
// 	t_vr_ft_token	t;

// 	t.cnt = ((t.y = 0), (t.lx = lxnewnode()), 0);
// 	while (ret[t.cnt])
// 	{
// 		t.no = token_or_not(ret[t.cnt], ret[t.cnt + 1]);
// 		if (ret[t.cnt] == 34 || ret[t.cnt] == 39)
// 		{
// 			t.no = ((t.qst = ret[t.cnt]), (t.cnt++), t.cnt);
// 			while (ret[t.cnt] != t.qst && ret[t.cnt])
// 				t.cnt++;
// 			if (ret[++t.cnt] == 0)
// 				t.lx = creat_node_word(t.lx, ret, t.y, t.cnt);
// 		}
// 		else if (t.no == 0 || t.no == 1 || t.no == 2 || t.no == 3 || t.no == 4)
// 		{
// 			t.lx = creat_node_token(ret[t.cnt], ret[t.cnt + 1], t.lx);
// 			if (t.no == 0 || t.no == 1)
// 				t.cnt += 2;
// 			else
// 				t.cnt++;
// 			t.y = t.cnt;
// 		}
// 		else if (ret[t.cnt] == ' ' || ret[t.cnt] == '\t')
// 			t.y = ((t.lx = creat_node_word(t.lx, ret, t.y, t.cnt)), t.cnt++, t.cnt);
// 		else
// 		{
// 			t.cnt++;
// 			if ((ret[t.cnt] == 0 && ret[t.cnt - 1] != ' ')
// 				&& (ret[t.cnt] == 0 && ret[t.cnt - 1] != '\t'))
// 				t.lx = creat_node_word(t.lx, ret, t.y, t.cnt);
// 		}
// 	}
// 	return (t.lx);
// }

// t_lexer	*ft_token(char *ret)
// {
// 	int cnt = 0;
// 	t_lexer *lx;
// 	char *p;
// 	int y = 0;
// 	int test;
// 	int qst;
// 	lx = lxnewnode();
// 	while (ret[cnt])
// 	{
// 		test = token_or_not(ret[cnt], ret[cnt + 1]);
// 		if(ret[cnt] == 34 || ret[cnt] == 39)
// 		{
// 			test = ((qst = ret[cnt]),(cnt++), cnt);
// 			while(ret[cnt] != qst && ret[cnt])
// 				cnt++;
// 			if (ret[++cnt] == 0)
// 				lx = creat_node_word(lx, ret, y, cnt);
// 		}
// 		else if(test == 0 || test == 1 || test == 2 || test == 3 || test == 4)
// 		{
// 			lx = creat_node_token(ret[cnt], ret[cnt + 1], lx);
// 			if(test == 0 || test == 1)
// 				cnt += 2;
// 			else
// 				cnt++;
// 			y = cnt;
// 		}
// 		else if(ret[cnt] == ' ' || ret[cnt] == '\t')
// 			y = ((lx = creat_node_word(lx, ret, y, cnt)),cnt++, cnt);
// 		else
// 		{
// 			cnt++;
// 			if((ret[cnt] == 0 && ret[cnt - 1] != ' ') && (ret[cnt] == 0 && ret[cnt - 1] != '\t'))
// 				lx = creat_node_word(lx, ret, y, cnt);
// 		}
// 	}
// 	return lx;
// }

// t_lexer	*ft_token(char *ret) // dorijin XD
// {
// 	int cnt = 0;
// 	t_lexer *lx;
// 	char *p;
// 	int y = 0;
// 	int test;
// 	int qst;
// 	lx = lxnewnode();
// 	while (ret[cnt])
// 	{
// 		test = token_or_not(ret[cnt], ret[cnt + 1]);
// 		if(ret[cnt] == 34 || ret[cnt] == 39)
// 		{
// 			qst = ret[cnt];
// 			cnt++;
// 			test = cnt;
// 			while(ret[cnt] != qst && ret[cnt])
// 				cnt++;
// 			cnt++;
// 			if (ret[cnt] == 0)
// 			{
// 				lx = creat_node_word(lx, ret, y, cnt);
// 			}
// 		}
// 		else if(test == 0 || test == 1 || test == 2 || test == 3 || test == 4)
// 		{
// 			lx = creat_node_token(ret[cnt], ret[cnt + 1], lx);
// 			if(test == 0 || test == 1)
// 				cnt += 2;
// 			else
// 				cnt++;
// 			y = cnt;
// 		}
// 		else if(ret[cnt] == ' ' || ret[cnt] == '\t')
// 		{
// 			lx = creat_node_word(lx, ret, y, cnt);
// 			cnt++;
// 			y = cnt;
// 		}
// 		else
// 		{
// 			cnt++;
// 			if((ret[cnt] == 0 && ret[cnt - 1] != ' ') && (ret[cnt] == 0 && ret[cnt - 1] != '\t'))
// 			{
// 				lx = creat_node_word(lx, ret, y, cnt);
// 			}
// 		}
// 	}
// 	return lx;
// }

// t_lexer	*remove_emty_node(t_lexer *token)
// {
// 	t_lexer	*test;

// 	while (token->next)
// 	{
// 		if (token->token == -1 && ft_strlen(token->word) == 0)
// 		{
// 			test = token;
// 			if (token->prev)
// 			{
// 				token->prev->next = token->next;
// 				token->next->prev = token->prev;
// 			}
// 			else
// 			{
// 				token = token->next;
// 				token->prev = NULL;
// 			}
// 			free(test->word);
// 			free(test);
// 		}
// 		token = token->next;
// 	}
// 	while (token->prev)
// 		token = token->prev;
// 	return (token);
// }

// typedef struct s_expand
// {
// 	int		x;
// 	int		y;
// 	int		i;
// 	int		dollar;
// 	int		c_p_dollar;
// 	int		c_p_key;
// 	char	*key;
// 	char	*new_word;
// }t_ex;

// void	check_expand(t_lexer *token, t_env *env)
// {
// 	t_ex	ex;
// 	t_env	*test;

// 	ex.x = ((ex.y = 0, ex.i = 0, ex.dollar = 0, ex.c_p_key = 0), 0);
// 	ex.c_p_dollar = 0;
// 	while (token->next)
// 	{
// 		if (token->token == LESS_LESS)
// 		{
// 			token = token->next;
// 			token = token->next;
// 		}
// 		else
// 		{
// 			ex.dollar = how_many(token->word, '$');
// 			while (ex.dollar != 0)
// 			{
// 				while (token->word[ex.x] != '$')
// 					ex.x++;
// 				if (token->word[ex.x + 1] == ' '
// 					|| token->word[ex.x + 1] == '\t'
// 					|| token->word[ex.x + 1] == '\0'
// 					|| token->word[ex.x + 1] == 34)
// 					ex.x++;
// 				else
// 				{
// 					ex.c_p_dollar = ++ex.x;
// 					ex.c_p_key = 0;
// 					while (token->word[ex.x + ex.c_p_key] != ' '
// 						&& token->word[ex.x + ex.c_p_key] != '$'
// 						&& token->word[ex.x + ex.c_p_key] != '\t'
// 						&& token->word[ex.x + ex.c_p_key]
// 						&& token->word[ex.x + ex.c_p_key] != 34
// 						&& token->word[ex.x + ex.c_p_key] != 39)
// 						ex.c_p_key++;
// 					ex.key = ft_substr2(token->word,
// 							ex.c_p_dollar, ex.c_p_key + ex.x);
// 					test = get_env_var(env, ex.key);
// 					if (test)
// 					{
// 						ex.new_word = malloc((ft_strlen(token->word) - ex.c_p_key) + ft_strlen(test->value));
// 						ex.c_p_dollar = 0;
// 						while (ex.c_p_dollar < ex.x - 1)
// 							ex.new_word[ex.y++] = token->word[ex.c_p_dollar++];					
// 						while (test->value[ex.i])
// 							ex.new_word[ex.y++] = test->value[ex.i++];
// 						while (token->word[ex.c_p_dollar + ex.c_p_key])
// 							ex.new_word[ex.y++] = token->word[ex.c_p_dollar + ++ex.c_p_key];
// 						ex.new_word[ex.y] = 0;
// 					}
// 					else
// 					{
// 						ex.new_word = malloc((ft_strlen(token->word) - ex.c_p_key));
// 						ex.c_p_dollar = 0;
// 						while (ex.c_p_dollar < ex.x - 1)
// 							ex.new_word[ex.y++] = token->word[ex.c_p_dollar++];
// 						while (token->word[ex.c_p_dollar + ex.c_p_key])
// 							ex.new_word[ex.y++] = token->word[ex.c_p_dollar + ++ex.c_p_key];
// 						ex.new_word[ex.y] = 0;
// 					}
// 					free(token->word);
// 					free(ex.key);
// 					token->word = ex.new_word;
// 					ex.dollar--;
// 					ex.c_p_dollar = 0;
// 					ex.c_p_key = 0;
// 					ex.y = 0;
// 					ex.i = 0;
// 				}
// 				ex.dollar = how_many(token->word + ex.x, '$');
// 			}
// 			token = token->next;
// 			ex.dollar = 0;
// 		}
// 	}
// }

// void	ft_print(t_lexer *lx)
// {
// 	while(lx->prev != NULL)
// 		lx = lx->prev;
// 	while(lx->next != NULL)
// 	{	
// 		if(lx->word != NULL )
// 			printf("word = (%s) %d\n", lx->word, lx->num_node);
// 		else
// 			printf("token = (%d) %d\n", lx->token, lx->num_node);
// 		lx = lx->next;
// 	}
// }
// void ft_printast(t_ast *lx)
// {
// 	int x = 0;
// 	while(lx->prev != NULL)
// 		lx = lx->prev;
// 	while(lx != NULL)
// 	{
// 		while(lx->str[x])
// 		{
// 			printf("ast word == (%s)\n", lx->str[x]);
// 			x++;
// 		}
// 		while(lx->redirections && lx->redirections->prev)
// 			lx->redirections = lx->redirections->prev;
// 		while(lx->redirections)
// 		{
// 			printf("word = (%s) and token = (%d)\n", lx->redirections->word, lx->redirections->token);
// 			lx->redirections = lx->redirections->next;
// 		}
// 		printf("%d\n", lx->builtins);
// 		x = 0;
// 		lx = lx->next;
// 	}
// }


// while(env->next)
	// {
	// 	printf("node->key == (%s)", env->key);
	// 	printf("node->value == (%s)\n", env->value);
	// 	env = env->next;
	// }
	//exit(0);