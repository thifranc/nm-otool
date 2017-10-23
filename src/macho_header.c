/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:37:57 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/23 18:51:29 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	macho_config(char *ptr, int *options)
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

int		handle_macho(char *file, int options)
{
	DEBUG
	char	*ptr;
	int		error_code;


	if ((error_code = open_file(file, &ptr)) != 0 ||
			(error_code = macho_config(ptr, &options)) != 0)
		handle_error(error_code);

	/*
	if (options & IS_32)
		handle_32(file, &ptr, options);
	else
	*/
		handle_64(file, ptr, options);
	return (0);
}
