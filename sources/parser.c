/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:22:20 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 20:27:40 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void	parse_ports(char *arg)
{
	char	**p;

	if (ft_strchr(arg, '-') == NULL)
	{
		g_env.port[0] = ft_atoi(arg);
		g_env.port[1] = g_env.port[0];
		return ;
	}
	p = ft_strsplit(arg, '-');
	g_env.port[0] = ft_atoi(p[0]);
	g_env.port[1] = ft_atoi(p[1]);
	if (g_env.port[0] > g_env.port[1])
	{
		fprintf(stderr, "Your port range %d-%d is backwards.\n",
				g_env.port[0], g_env.port[1]);
		ft_freetab(p);
		exit(EXIT_FAILURE);
	}
	if ((g_env.port[1] - g_env.port[0]) > 1024)
	{
		fprintf(stderr, "Your port range %d-%d is too long, max is 1024.\n",
				g_env.port[0], g_env.port[1]);
		ft_freetab(p);
		exit(EXIT_FAILURE);
	}
	ft_freetab(p);
}

int			parser(char **av)
{
	int		y;

	for (y = 0; av[y]; y++)
	{
		if (ft_strequ("--help", av[y]))
			return (-1);
		else if (ft_strequ("-f", av[y]) || ft_strequ("--file", av[y]))
			parse_file(av[++y]);
		else if (ft_strequ("-p", av[y]) || ft_strequ("--ports", av[y]))
			parse_ports(av[++y]);
	}
	return (1);
}
