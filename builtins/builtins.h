/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:52:12 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/01 15:09:16 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <limits.h>
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif
# include "../minishell.h"

//for test rn
// typedef struct env
// {
// 	char		*key;
// 	char		*value;
// 	struct env	*next;
// }	t_env;

//utils.c
t_env	*get_env_var(t_env *env, char *key);
int		update_env_var(t_env *env, char *key, char *value);
int		unset_env_var(t_env **env, char *key);
int		add_env_var(t_env **env, char *key, char *value);

//cd.c
int		cd(t_ast *ast, t_env *env);

//pwd.c
int		pwd(t_ast *ast, t_env *env);
#endif