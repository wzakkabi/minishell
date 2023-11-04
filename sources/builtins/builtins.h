/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 02:52:12 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/04 16:36:09 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <limits.h>
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif
# include "../minishell.h"

//utils.c
t_env	*get_env_var(t_env *env, char *key);
int		update_env_var(t_env *env, char *key, char *value);
int		unset_env_var(t_env **env, char *key);
int		add_env_var(t_env **env, char *key, char *value);

//cd.c
int		cd(t_ast *ast, t_env *env);

//pwd.c
int		pwd(t_ast *ast);

//exit.c
void	builtin_exit(t_ast *ast);

//env.c
int		builtin_env(t_env *env);

//export.c
int		export(t_ast *ast, t_env *env);

//unset.c
int		unset(t_ast *ast, t_env *env);

//echo.c
int		echo(t_ast *ast);
#endif