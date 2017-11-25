/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:57:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/25 15:17:59 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

char	open_file(char *file, char **ptr, t_a *g)
{
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

void	identify_file(char *file, char *ptr, t_a *g)
{
	unsigned int	mg_nb;

	g->title = file;
	mg_nb = *(int *)ptr;
	if (mg_nb == FAT_MAGIC || mg_nb == FAT_MAGIC_64
			|| mg_nb == FAT_CIGAM || mg_nb == FAT_CIGAM_64)
		g->opt = g->opt | IS_FAT;
	else
		g->opt = g->opt & ~IS_FAT;
	if (ft_strncmp(ARMAG, (char*)ptr, 8) == 0)
		g->opt = g->opt | IS_LIB;
	else
		g->opt = g->opt & ~IS_LIB;
}

int		handle_file(char *file, t_a *g)
{
	int				error_code;
	char			*ptr;

	if ((error_code = open_file(file, &ptr, g)) != 0)
		return (error_code);
	else
	{
		identify_file(file, ptr, g);
		if (g->opt & IS_FAT)
			error_code = handle_fat(ptr, g);
		else if (g->opt & IS_LIB)
			error_code = handle_lib(ptr, g);
		else
			error_code = handle_macho(ptr, g);
		munmap(ptr, g->filesize);
	}
	return (error_code ? error_code : 0);
}

int		handle_all_args(int ac, char **av, t_a *g)
{
	int		i;
	int		error;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-')
		{
			if ((error = handle_file(av[i], g)) != 0)
			{
				handle_error(error, av[i]);
				g->opt = g->opt | HAS_ONE_ERROR;
			}
			else
			{
				init_g_struct(g);
			}
		}
		i++;
	}
	return (g->opt & HAS_ONE_ERROR ? 1 : 0);
}

int		main(int ac, char **av)
{
	t_a		g;

	if (ac == 1)
	{
		av[1] = "a.out";
		ac = 2;
	}
	if ((g.opt = parser(ac, av)) & ERR_MULTI_OPT)
		return (handle_error(g.opt, "for the option"));
	else
		return (handle_all_args(ac, av, &g));
}
