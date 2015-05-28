/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:57:30 by eboeuf            #+#    #+#             */
/*   Updated: 2015/02/12 15:48:49 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void				open_script(t_env *env)
{
	int				fd;
	char			*file;

	file = (env->file) ? env->file : "typescript";
	if (env->a == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 00644);
	env->scriptfd = fd;
}

void				ft_usage(char flag)
{
	ft_putstr_fd("script: illegal option -- ", 2);
	ft_putchar_fd(flag, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: script [-aq] [-t time] [file [command ...]]", 2);
	_exit(-1);
}

void				parse_args(t_env *env, int ac, char **av)
{
	int				i;

	i = 0;
	env->a = 0;
	env->q = 0;
	env->file = NULL;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'a' && av[i][2] == 'q')
				env->q = (av[i][1] == 'a') ? 1 : env->q;
			else if (av[i][1] == 'a')
				env->a = (av[i][1] == 'a') ? 1 : env->a;
			else if (av[i][1] == 'q')
				env->q = (av[i][1] == 'q') ? 1 : env->q;
			else if (av[i][1] == '\0')
				env->file = av[i];
			else
				ft_usage(av[i][1]);
		}
		else if (av[i] != NULL && av[i][0] != '-')
			env->file = av[i];
	}
}
