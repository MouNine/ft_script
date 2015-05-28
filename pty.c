/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 12:43:29 by eboeuf            #+#    #+#             */
/*   Updated: 2015/04/23 11:48:12 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

int					init_pty(t_env *env, int bufsize)
{
	struct stat		sbuf;
	char			*sname;
	int				fdm;

	if ((fdm = open("/dev/ptmx", O_RDWR | O_NOCTTY)) == -1)
		ft_error(env, "Error open pty master", 1);
	if ((ioctl(fdm, TIOCPTYGRANT)) == -1)
		ft_error(env, "Error granpt slave", 1);
	if ((ioctl(fdm, TIOCPTYUNLK)) == -1)
		ft_error(env, "Error unlock slave", 1);
	sname = NULL;
	if (ioctl(fdm, TIOCPTYGNAME, env->ptsname) != 0)
	{
		if ((stat(env->ptsname, &sbuf)) == 0)
			sname = env->ptsname;
	}
	if (ft_strlen(sname) < (size_t)bufsize)
		ft_strncpy(env->ptsname, sname, bufsize);
	else
		ft_error(env, "Ptsname overflow", 1);
	if ((env->fds = open(env->ptsname, O_RDWR)) == -1)
		ft_error(env, "Error open fds", 1);
	return (fdm);
}
