/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:27:25 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/26 09:35:56 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

int		get_options(char *arg)
{
	int		i;
	int		opt;

	i = 0;
	opt = 0;
	while (arg[i])
	{
		if (arg[i] == 'r')
			opt = opt & OPT_R ? opt | ERR_MULTI_OPT : opt | OPT_R;
		else if (arg[i] == 'j')
			opt = opt & OPT_J ? opt | ERR_MULTI_OPT : opt | OPT_J;
		else if (arg[i] == 'u')
			opt = opt & OPT_U ? opt | ERR_MULTI_OPT : opt | OPT_U;
		else if (arg[i] == 'p')
			opt = opt & OPT_P ? opt | ERR_MULTI_OPT : opt | OPT_P;
		else if (arg[i] == 'n')
			opt = opt & OPT_N ? opt | ERR_MULTI_OPT : opt | OPT_N;
		i++;
	}
	return (opt);
}

void	print_bits(int size, void *ptr)
{
	unsigned char	*b;
	unsigned char	byte;
	int				i;
	int				j;

	b = (unsigned char *)ptr;
	i = 0;
	j = 7;
	while (i < size)
	{
		while (j >= 0)
		{
			byte = (b[i] >> j) & 1;
			byte ? write(1, "1", 1) : write(1, "0", 1);
			j--;
		}
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

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
		if (av[i][0] == '-')
		{
			options = options | get_options(av[i] + 1);
			if (options & ERR_MULTI_OPT)
				return (options);
		} else
		{
			files++;
		}
		i++;
	}
	if (files > 1)
		options = options | MANY_ARGS;
	return (options);
}
