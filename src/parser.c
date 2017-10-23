/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:27:25 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/23 17:36:10 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	get_options(char *arg)
{
	int 	i;
	char	opt;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 'r')
			opt & OPT_R ? return(ERR_MULTI_OPT) :  opt = opt | OPT_R;
		else if (arg[i] == 'j')
			opt & OPT_J ? return(ERR_MULTI_OPT) :  opt = opt | OPT_J;
		else if (arg[i] == 'u')
			opt & OPT_U ? return(ERR_MULTI_OPT) :  opt = opt | OPT_U;
		else if (arg[i] == 'p')
			opt & OPT_P ? return(ERR_MULTI_OPT) :  opt = opt | OPT_P;
		else if (arg[i] == 'n')
			opt & OPT_N ? return(ERR_MULTI_OPT) :  opt = opt | OPT_N;
		i++;
	}
	return (opt);
}

//assumes little endian
void	printBits(size_t const size, void const * const ptr)
{
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
	int i;
	char options; 
	int both;

	i = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			dprintf(1, "this is options : %s\n", av[i]);
			options = get_options(av[i] + 1);
			if (options == ERR_MULTI_OPT)
				return (ERR_MULTI_OPT);
		}
		i++;
	}
	both = options;
	return (both);
}
