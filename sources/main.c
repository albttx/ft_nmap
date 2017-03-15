/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/15 14:36:02 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int		usage(char *name)
{
	printf("Usage %s [options] ip\n", name);
	printf("    --help\n");
	printf("    --ip        [ip]\n");
	printf("    -f/--file   [file] list of IP\n");
	printf("    -p/--ports  [port number / port range] : default 1-1024\n");
	printf("    -t/--thread [nb of thread] : default 0 - max 250\n");
	printf("    --scan      [type] (SYN, NULL, ACK, FIN, XMAS, UDP) : default all\n");
	printf("                ex: --scan SYN or --scan ACK-NULL-XMAS for multiple\n");
	return (-1);
}

static void		init(void)
{
	ft_bzero(&g_env, sizeof(g_env));
	g_env.thread = 0;
	g_env.port[0] = 0;
	g_env.port[1] = 1024;
	g_env.type_flags = SYN | NUL | ACK | FIN | XMAS | UDP;
}

int		main(int ac, char **av)
{
	init();
	if (ac > 1 && parser(av) == 1)
	{
		dbg_print_flags();
		dbg_print_ip();
	}
	else
		return (usage(av[0]));
	return (0);
}
