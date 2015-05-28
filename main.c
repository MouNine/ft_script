cd /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 10:49:05 by eboeuf            #+#    #+#             */
/*   Updated: 2015/02/12 15:30:12 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void				ft_error(t_env *env, char *s, int stop)
{
	if (s)
	{
		write(2, s, ft_strlen(s));
		ttyreset(env);
	}
	if (stop)
	{
		write(2, "\n", 1);
		ttyreset(env);
		_exit(-1);
	}
}

void				recup_term(t_env *env)
{
	if (ioctl(0, TIOCGETA, &env->ttyorig) == -1)
		ft_error(env, "Error tcgetattr", 1);
	if (ioctl(0, TIOCGWINSZ, &env->winsize) == -1)
		ft_error(env, "Error winsize", 1);
}

void				ttyreset(t_env *env)
{
	if (ioctl(0, TIOCSETA, &env->ttyorig) == -1)
		write(2, "tcsetattr failed", ft_strlen("tcsetattr failed"));
	else
	{
		close(env->fdm);
		close(env->fds);
		close(env->scriptfd);
		_exit(0);
	}
}

int					main(int ac, char **av, char **envp)
{
	pid_t			childpid;
	t_env			env;

	recup_term(&env);
	if (envp[0] == NULL)
		ft_error(&env, "Env no found", 1);
	if ((childpid = pty_fork(&env)) == 0)
	{
		env.shell[0] = fill_env(envp, "SHELL");
		if (env.shell[0] == NULL)
			env.shell[0] = "/bin/zsh";
		env.shell[1] = NULL;
	}
	execve(env.shell[0], env.shell, envp);
	parse_args(&env, ac, av);
	open_script(&env);
	if (raw_mode(&env) == -1)
		ft_error(&env, "Raw mode failed", 1);
	if (env.file && access(env.file, W_OK))
		ft_error(&env, "ft_script: Error : Permission denied", 1);
	ft_header(&env);
	while (1)
		read_fd(&env);
	return (0);
}
