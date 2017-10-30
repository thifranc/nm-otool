/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:53:30 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 14:58:48 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		main(int ac, char **av)
{
	int						fd;
	struct stat				buf;
	char					*ptr;
	char					*stringtable;
	int						magic_number;
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	struct	symtab_command	*sc;
	struct	segment_command_64	*sg;
	struct	nlist_64		*symbol_table;
	int						type;
	int						i;
	int						j;
	struct	section_64	*sec_64;

	union u_section			*union_section;

	i = 0;
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
	header = (struct mach_header_64 *)ptr;
	printf("%x --> is magic number\n", header->magic);
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i < (int)header->ncmds)
	{

		if (lc->cmd == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64 *)lc;
			char *segname = sg->segname;

			sec_64 = (void*)sg + sizeof(struct segment_command_64);

			j = 0;
			while (j < (int)sg->nsects)
			{
				char *sectname = sec_64[j].sectname;
				printf("segname = %s && sectname ==> %s\n", segname, sectname);
				j++;
			}
		}
		/*
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
		*/
		lc = (void *)lc + lc->cmdsize;
		i++;

	}



	return 0;

}
