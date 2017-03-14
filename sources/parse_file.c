/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 20:24:18 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 20:58:04 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <sys/stat.h>
#include <sys/mman.h>

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
	printf("addr=> %s - %s\n", ip->ipv4name, ip->hostname);
}

void			parse_file(char *arg)
{
	char			*file;
	char			**addrs;
	struct stat		buf;
	int				fd;
	int				y;
	t_ip			url;

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
