/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:27:25 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/26 16:11:54 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/otool.h"

int		parser(int ac, char **av)
{
	int i;
	int options;
	int files;

	i = 1;
	options = 0;
	files = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] && av[i][1] == 'd')
			options = options | OPT_D;
		else
			files++;
		i++;
	}
	if (files > 1)
		options = options | MANY_ARGS;
	return (options);
}
