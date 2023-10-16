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