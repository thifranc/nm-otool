/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:57:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 15:33:03 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	open_file(char *file, char **ptr, t_a *g)
{
	//DEBUG
	int			fd;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_OPEN);
	if (fstat(fd, &buf) == -1)
		return (ERR_FSTAT);
	g->filesize = buf.st_size;
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (ERR_MMAP);
	return (0);
}

int		handle_file(char *file, t_a g)
{
	//DEBUG
	int		error_code;
	char	*ptr;
	unsigned int	magic_number;

	if ((error_code = open_file(file, &ptr, &g)) != 0)
		return (handle_error(error_code));
	else
	{
		g.title = file;
		magic_number = *(int *)ptr;
		if (magic_number == FAT_MAGIC ||
			magic_number == FAT_MAGIC_64 ||
			magic_number == FAT_CIGAM ||
			magic_number == FAT_CIGAM_64
				)
		{
			//dprintf(1, "is fat file\n");
			g.opt = g.opt | IS_FAT;
			handle_fat(ptr, g);
		}
		else
		{
			//dprintf(1, "is classic macho file\n");
			g.opt = g.opt & ~IS_FAT;
			handle_macho(ptr, g);
		}
	}
	munmap(ptr, g.filesize);
	return (0);
}

int		main(int ac, char **av)
{
	//DEBUG
	t_a		 g;
	int		i;
	int		error;

	i = 1;
	if (ac == 1)
	{
		av[1] = "a.out";
		ac = 2;
	}
	if ((g.opt = parser(ac, av)) >= ERR_MULTI_OPT)
		return (handle_error(g.opt));
	while (i < ac)
	{
		if (av[i][0] != '-')
		{
			if ((error = handle_file(av[i], g)) != 0)
				handle_error(error);
		}
		i++;
	}
	return (0);
}
