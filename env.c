/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:23:00 by eboeuf            #+#    #+#             */
/*   Updated: 2015/02/11 15:40:55 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

char				*fill_env(char **env, char *envp)
{
	char			**tmp;
	int				i;

	i = 0;
	while (*env[i])
	{
		if (!ft_strncmp(envp, env[i], ft_strlen(envp)))
		{
			tmp = ft_strsplit(env[i], '=');
			return (tmp[1]);
		}
		i++;
	}
	return (0);
}
