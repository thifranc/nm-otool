/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:57:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 16:50:58 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		main(int ac, char **av)
{
	DEBUG
	struct s_a g;
	int		i;

	i = 1;
	if (ac == 1)
	{
		av[1] = "a.out";
		ac = 2;
	}
	if ((g.opt = parser(ac, av)) >= ERR_MULTI_OPT)
		return handle_error(g.opt);
	while (i < ac)
	{
		if (av[i][0] != '-')
			handle_macho(av[i], g);
		i++;
	}
	return (0);
}
