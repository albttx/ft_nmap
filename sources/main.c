/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 19:31:19 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int		usage(char *name)
{
	printf("Usage %s [options] ip\n", name);
	printf("    --help\n");
	printf("    --ip       [ip]\n");
	printf("    -f/--file  [file] list of IP\n");
	printf("    -p/--ports [port number / port range] : default 1-1024\n");
	printf("    --thread   [nb of thread] : default 0 - max 250\n");
	printf("    --scan     [type] (SYN, NULL, ACK, FIN, XMAS, UDP) : default all\n");
	return (-1);
}

static void		init(void)
{
	ft_bzero(&g_env, sizeof(g_env));
}

int		main(int ac, char **av)
{
	init();
	if (ac > 1 && parser(av))
	{
		/*ft_nmap();*/
		puts("ft_nmap();");
	}
	else
		return (usage(av[0]));
	return (0);
}
