/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:53:30 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/19 10:27:06 by thifranc         ###   ########.fr       */
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
	union u_section
	{
		struct	section_64	sec_64;
		struct	section		sec_32;
	};

	union segment_cmd
	{
		struct	segment_command_64	seg_64;
		struct	segment_command		seg_32;
	};

	union u_section			*union_section;
	//union segment_cmd		*segment_cmd;


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
	printf("filesize == %lld sgmt cmd siize %lu && %lu && %lu\n", buf.st_size, sizeof(struct segment_command_64), sizeof(struct segment_command), sizeof(union segment_cmd));
	magic_number = *(int *)ptr;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i < (int)header->ncmds)
	{

		if (lc->cmd == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64 *)lc;
			printf("segment name ===> %s && size %u $$$ filesoze -- %llu &&& file of -> %llu && bn sections == %u\n", sg->segname, sg->cmdsize, sg->filesize, sg->fileoff, sg->nsects);

			union_section = (void*)sg;

			union_section = (void*)sg + sizeof(struct segment_command_64);
			dprintf(1, "%p \n", union_section);
			union_section = (union u_section *)(sg + 1);
			dprintf(1, "%p \n", union_section);
			union_section = (void*)sg + sizeof(union segment_cmd);
			dprintf(1, "%p \n", union_section);

			j = 0;
			while (j < (int)sg->nsects)
			{
				char *str = union_section->sec_64.sectname;
				printf("union_section name ==> 		%s\n", str);
				j++;
			}
		}
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command *)lc;
			j = 0;
			symbol_table = (void *)ptr + sc->symoff;
			stringtable = (void *)ptr + sc->stroff;
			printf("nb -> %u\n", sc->nsyms);
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



	return 0;

}
