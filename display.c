/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:14:46 by eboeuf            #+#    #+#             */
/*   Updated: 2015/02/11 12:20:43 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void				ft_header(t_env *env)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (env->q == 0)
	{
		ft_putstr_fd("Script started, output file is ", 1);
		if (env->file != NULL)
			ft_putendl_fd(env->file, 1);
		else
			ft_putendl_fd("typescript", 1);
		ft_putstr_fd("Script started on ", env->scriptfd);
		ft_putendl_fd(ctime(&tv.tv_sec), env->scriptfd);
	}
}

void				ft_footer(t_env *env)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (env->q == 0)
	{
		ft_putstr_fd("\nScript done, output file is ", 1);
		if (env->file != NULL)
			ft_putendl_fd(env->file, 1);
		else
			ft_putendl_fd("typescript", 1);
		ft_putstr_fd("Script done on ", env->scriptfd);
		ft_putendl_fd(ctime(&tv.tv_sec), env->scriptfd);
	}
}
