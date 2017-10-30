/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:48:06 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 16:31:50 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	macho_config(char *ptr, unsigned char *options)
{
	DEBUG
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number != MH_CIGAM_64 &&
			magic_number != MH_CIGAM &&
			magic_number != MH_MAGIC &&
			magic_number != MH_MAGIC_64)
		return (ERR_MAGIC);
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM)
		*options = *options | TO_SWAP;
	else
		*options = *options & ~TO_SWAP;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		*options = *options | IS_32;
	else
		*options = *options & ~IS_32;
	return (0);
}

char	open_file(char *file, char **ptr)
{
	DEBUG
	int			fd;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_OPEN);
	if (fstat(fd, &buf) == -1)
		return (ERR_FSTAT);
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (ERR_MMAP);
	return (0);
}

char	*get_type(int type)
{
	char	*n_type;

	if (type == N_UNDF || type == N_PBUD)
		n_type = "U";
	if (type == N_SECT)
		n_type = "T";
	if (type == N_ABS)
		n_type = "A";
	return (n_type);
}

int		handle_macho(char *file, t_a g)
{
	DEBUG
	char	*ptr;
	int		error_code;


	if ((error_code = open_file(file, &ptr)) != 0 ||
			(error_code = macho_config(ptr, &(g.opt))) != 0)
		handle_error(error_code);

	printBits(sizeof(g.opt), &(g.opt));
	if (g.opt & IS_32)
		handle_32(file, ptr, g);
	else
		handle_64(file, ptr, g);
	return (0);
}
