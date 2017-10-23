/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:37:57 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/23 17:36:10 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	macho_config(int *ptr, int *options)
{
	int		magic_number;

	magic_number = *(int *)ptr;
	if (magic_number != MH_CIGAM_64 &&
			magic_number != MH_CIGAM &&
			magic_number != MH_MAGIC &&
			magic_number != MH_MAGIC_64)
		return (ERR_MAGIC);
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM)
		*options | TO_SWAP;
	else
		*options & ~TO_SWAP;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		*options | IS_32;
	else
		*options & ~IS_32;
	return (0);
}

char	open_file(char *file, char **ptr)
{
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
	char					*stringtable;
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	struct	symtab_command	*sc;
	struct	segment_command_64	*sg;
	struct	nlist_64		*symbol_table;
	int						type;
	int						i;
	int						j;

	char	*ptr;


	if ((error_code = open_file(file, &ptr)) != 0 ||
			(error_code = macho_config(ptr, &options)) != 0)
		handle_error(error_code);

	if (options & IS_32)
		handle_32(file, &ptr, options);
	else
		handle_64(file, &ptr, options);

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);

	while (i < (int)header->ncmds)
	{

		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command *)lc;
			j = 0;
			symbol_table = (void *)ptr + sc->symoff;
			stringtable = (void *)ptr + sc->stroff;
			while (j < (int)sc->nsyms)
			{
				if (symbol_table[j].n_value)
					printf("%016llx ", symbol_table[j].n_value);
				else
					printf("                 ");
				type = symbol_table[j].n_type & N_TYPE;
				if (type == N_UNDF || type == N_PBUD)
					printf("U  ");
				if (type == N_SECT)
					printf("T  ");
				printf("%s\n", stringtable + symbol_table[j].n_un.n_strx);
				j++;
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;

	}
	return (0);

}
