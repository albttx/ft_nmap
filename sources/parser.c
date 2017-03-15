/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:22:20 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/15 14:39:56 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <sys/stat.h>
#include <sys/mman.h>

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

static void	parse_thread(char *arg)
{
	g_env.thread = ft_atoi(arg);
	if (g_env.thread < 0 || g_env.thread > 250)
	{
		fprintf(stderr, "thread must be between 0 and 250\n");
		exit(EXIT_FAILURE);
	}
}

static void	parse_scantype(char *arg)
{
	char	**types;
	int		y;

	types = ft_strsplit(arg, '-');
	g_env.type_flags = 0;
	for (y = 0; types[y]; y++)
	{
		if (ft_strequ("SYN", types[y]))
			g_env.type_flags |= SYN;
		else if (ft_strequ("NULL", types[y]))
			g_env.type_flags |= NUL;
		else if (ft_strequ("ACK", types[y]))
			g_env.type_flags |= ACK;
		else if (ft_strequ("FIN", types[y]))
			g_env.type_flags |= FIN;
		else if (ft_strequ("XMAS", types[y]))
			g_env.type_flags |= XMAS;
		else if (ft_strequ("UDP", types[y]))
			g_env.type_flags |= UDP;
	}
	ft_freetab(types);
}

static void		fill_ipurl(t_ip *ip, const char *addr)
{
	ft_bzero(ip, sizeof(*ip));
	ip->ipv4name = hostname_to_ip(addr);
	if (ip->ipv4name == NULL)
	{
		fprintf(stderr, "Invalid url: %s\n", addr);
		exit(EXIT_FAILURE);
		return ;
	}
	if (ft_strequ(addr, ip->ipv4name) != 1)
		ip->hostname = ft_strdup(addr);
}

void			parse_file(char *arg)
{
	char			*file;
	char			**addrs;
	struct stat		buf;
	int				fd;
	int				y;
	t_ip			url;

	if (g_env.ip != NULL)
	{
		fprintf(stderr, "IP already set with --ip\n");
		exit(EXIT_FAILURE);
	}

	fd = open(arg, O_RDONLY);
	if (fd <= 0 || fstat(fd, &buf) < 0)
	{
		fprintf(stderr, "Failed to open %s\n", arg);
		exit(EXIT_FAILURE);
	}
	file = (char *)mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	addrs = ft_strsplit(file, '\n');
	for (y = 0; addrs[y]; y++)
	{
		fill_ipurl(&url, addrs[y]);
		ft_lstadd_end(&g_env.ip, ft_lstnew(&url, sizeof(url)));
	}

	close(fd);
	munmap(file, buf.st_size);
}

static void	parse_ip(char *arg)
{
	t_ip	url;

	if (g_env.ip != NULL)
	{
		fprintf(stderr, "IP already set with file\n");
		exit(EXIT_FAILURE);
	}
	fill_ipurl(&url, arg);
	ft_lstadd_end(&g_env.ip, ft_lstnew(&url, sizeof(url)));
}

int			parser(char **av)
{
	int		y;

	for (y = 0; av[y]; y++)
	{
		if (ft_strequ("-h", av[y]) || ft_strequ("--help", av[y]))
			return (-1);
		else if (ft_strequ("-f", av[y]) || ft_strequ("--file", av[y]))
			parse_file(av[++y]);
		else if (ft_strequ("-p", av[y]) || ft_strequ("--ports", av[y]))
			parse_ports(av[++y]);
		else if (ft_strequ("-t", av[y]) || ft_strequ("--thread", av[y]))
			parse_thread(av[++y]);
		else if (ft_strequ("--scan", av[y]))
			parse_scantype(av[++y]);
		else if (ft_strequ("--ip", av[y]))
			parse_ip(av[++y]);
		else
		{
			if (hostname_to_ip(av[y]) != NULL)
			{
				parse_ip(av[y]);
				break ;
			}
		}
	}
	return (1);
}
