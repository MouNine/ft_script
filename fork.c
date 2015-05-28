/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:57:30 by eboeuf            #+#    #+#             */
/*   Updated: 2015/04/23 11:44:43 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

int					raw_mode(t_env *env)
{
	t_term			t;

	if (ioctl(0, TIOCGETA, &t) == -1)
		return (-1);
	if (&env->ttyorig != NULL)
		env->ttyorig = t;
	t.c_lflag &= ~(ICANON | ECHONL | ISIG | IEXTEN | ECHO);
	t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	t.c_cflag &= ~(CSIZE | PARENB);
	t.c_cflag |= CS8;
	t.c_cc[VMIN] = 1;
	t.c_cc[VTIME] = 0;
	ioctl(0, TIOCSETA, &t);
	return (0);
}

int					read_fd(t_env *env)
{
	fd_set			fd_in;
	char			input[256];
	int				nread;

	FD_SET(0, &fd_in);
	FD_SET(env->fdm, &fd_in);
	if (select(env->fdm + 1, &fd_in, NULL, NULL, NULL) == -1)
		ft_error(env, "Error select", 1);
	if (FD_ISSET(0, &fd_in))
	{
		if ((nread = read(0, input, 256)) <= 0)
			ft_error(env, "Error read stdin", 1);
		write(env->fdm, input, nread);
	}
	if (FD_ISSET(env->fdm, &fd_in))
	{
		if ((nread = read(env->fdm, input, 256)) <= 0)
		{
			ft_footer(env);
			ttyreset(env);
		}
		write(1, input, nread);
		write(env->scriptfd, input, nread);
	}
	return (0);
}

pid_t				pty_fork_son(t_env *env)
{
	if (setsid() == -1)
		ft_error(env, "Error setsid", 1);
	if ((env->fds = open(env->ptsname, O_RDWR)) == -1)
		ft_error(env, "Error open slave", 1);
	if ((ioctl(env->fds, TIOCSCTTY, 0)) == -1)
		ft_error(env, "Error tiocstty", 1);
	if (ioctl(env->fds, TIOCSETA, &env->ttyorig) == -1)
		ft_error(env, "Set slave tty attributes fail", 1);
	if (ioctl(env->fds, TIOCSWINSZ, &env->winsize) == -1)
		ft_error(env, "Set slave tty window size fail", 1);
	if ((dup2(env->fds, 0)) != 0)
		ft_error(env, "Error stdin", 1);
	if ((dup2(env->fds, 1)) != 1)
		ft_error(env, "Error stdout", 1);
	if ((dup2(env->fds, 2) != 2))
		ft_error(env, "Error stderr", 1);
	if (env->fds > 2)
		close(env->fds);
	return (0);
}

pid_t				pty_fork(t_env *env)
{
	int				fdm;
	pid_t			childpid;

	fdm = init_pty(env, 128);
	if ((childpid = fork()) == -1)
	{
		close(fdm);
		ft_error(env, "Fork failed", 1);
	}
	else if (childpid != 0)
	{
		env->fdm = fdm;
		return (childpid);
	}
	else
	{
		pty_fork_son(env);
		close(fdm);
	}
	return (0);
}
