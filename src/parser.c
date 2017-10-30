/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:27:25 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 15:16:47 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	get_options(char *arg)
{
	DEBUG
	int 	i;
	char	opt;

	i = 0;
	opt = 0;
	while (arg[i])
	{
		if (arg[i] == 'r')
			opt = opt & OPT_R ? (char)ERR_MULTI_OPT :  opt | OPT_R;
		else if (arg[i] == 'j')
			opt = opt & OPT_J ? (char)ERR_MULTI_OPT :  opt | OPT_J;
		else if (arg[i] == 'u')
			opt = opt & OPT_U ? (char)ERR_MULTI_OPT :  opt | OPT_U;
		else if (arg[i] == 'p')
			opt = opt & OPT_P ? (char)ERR_MULTI_OPT :  opt | OPT_P;
		else if (arg[i] == 'n')
			opt = opt & OPT_N ? (char)ERR_MULTI_OPT :  opt | OPT_N;
		i++;
	}
	return (opt);
}

//assumes little endian
void	printBits(size_t const size, void const * const ptr)
{
	DEBUG
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
			byte ? write(1, "1", 1) : write(1, "0", 1);
        }
		write(1, " ", 1);
    }
	write(1, "\n", 1);
}

int		parser(int ac, char **av)
{
	DEBUG
	int i;
	char options; 

	i = 0;
	while (i < ac)
	{
		j = i + 1;
		while (j++ < ac)
			if (ft_strcmp(av[i], av[j]) == 0)
				return (ERR_SAME_ARG);
		if (av[i][0] == '-')
		{
			ft_putstr(ft_ptrf( "this is options : %s\n", av[i]));
			options = get_options(av[i] + 1);
			if ((unsigned char)options == ERR_MULTI_OPT)
				return (ERR_MULTI_OPT);
		}
		i++;
	}
	return ((int)options);
}
