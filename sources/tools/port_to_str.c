/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 18:14:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/31 18:22:46 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

const char		*port_to_str(int port)
{
	if (port == OPEN)
		return ("open");
	else if (port == CLOSE)
		return ("close");
	else if (port == FILTERED)
		return ("filtered");
	else if (port == UNFILTERED)
		return ("unfiltered");
	return ("unknown");
}
