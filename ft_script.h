/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 12:50:01 by eboeuf            #+#    #+#             */
/*   Updated: 2015/02/12 15:48:15 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include "libft/includes/libft.h"

typedef struct termios	t_term;
typedef struct winsize	t_win;

typedef struct			s_env
{
	int					fdm;
	int					fds;
	char				ptsname[128];
	char				*shell[2];
	char				*file;
	char				**envp;
	int					scriptfd;
	int					a;
	int					q;
	t_term				ttyorig;
	t_win				winsize;
}						t_env;

void					recup_term(t_env *env);

char					*fill_env(char **env, char *envp);

int						init_pty(t_env *env, int bufsize);
int						raw_mode(t_env *env);
int						read_fd(t_env *env);
pid_t					pty_fork_son(t_env *env);
pid_t					pty_fork(t_env *env);

void					parse_args(t_env *env, int ac, char **av);
void					open_script(t_env *env);
void					ft_header(t_env *env);
void					ft_footer(t_env *env);
void					ft_usage(char flag);

void					ft_error(t_env *env, char *s, int stop);
void					ttyreset(t_env *env);
#endif
