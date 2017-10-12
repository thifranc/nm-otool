/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:53:30 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/12 20:09:47 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm-otool.h"

int		main(int ac, char **av)
{
	int			fd;
	struct stat	buf;
	char		*ptr;
	int			magic_number;

	if (ac == 0)
		return 0;
	if ((fd = open(av[1], O_RDONLY)) == -1)	
		return -1;
	if (fstat(fd, &buf) == -1)
		return -1;
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return -1;
	magic_number = *(int *)ptr;
	printf("%x ", magic_number);
	if (magic_number == (int)MH_MAGIC + 1)
	{
		printf("on est bon !");
	} else {
		printf("failed !");
	}

	return 0;

}
