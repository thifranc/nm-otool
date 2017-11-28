/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:40:59 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/28 20:51:13 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/otool.h"

static void		print_content32(struct section *sect, char *ptr,
	t_a *g)
{
	uint64_t	size;
	uint32_t	offset;
	uint64_t	addr;
	uint64_t	i;

	i = 0;
	size = swaptest(sect->size, g->opt);
	offset = swaptest(sect->offset, g->opt);
	addr = swaptest(sect->addr, g->opt);
	if ((!(g->opt & IS_LIB) && !(g->opt & IS_FAT)) ||
		((g->opt & IS_FAT) && !(g->opt & NO_X86_64)))
		ft_putstrdel(ft_ptrf("%s:\n", g->title));
	if (g->opt & IS_FAT && g->opt & NO_X86_64)
		ft_putstrdel(ft_ptrf("%s (architecture %s):\n", g->title, g->cputype));
	ft_putstrdel(ft_ptrf("Contents of (%s,%s) section",
				sect->segname, sect->sectname));
	while (i < size)
	{
		if (i % 16 == 0)
			ft_putstrdel(ft_ptrf("\n%0*x\t", (addr + i), 16));
		ft_putstrdel(ft_ptrf("%0*x ", *(ptr + offset + i) & SECTION_TYPE, 2));
		i++;
	}
	write(1, "\n", 1);
}

int				get_n_sect32(struct segment_command *sg, char *ptr, t_a *g)
{
	struct section		*sec_32;
	char				*segname;
	char				*sectname;
	long long unsigned	j;

	sec_32 = (void*)sg + sizeof(struct segment_command);
	j = 0;
	while (j < swaptest((int)sg->nsects, g->opt))
	{
		sectname = sec_32[j].sectname;
		segname = sec_32[j].segname;
		if (ft_strcmpi(segname, sectname) == 0 &&
			((g->opt & OPT_D && !ft_strcmp(sectname, "__data"))
				|| !ft_strcmp(sectname, "__text")))
			print_content32(sec_32, ptr, g);
		j++;
	}
	g->n_sect += j;
	return (0);
}

int				handle_32(char *ptr, t_a *g)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct load_command		lc_clean;
	long long unsigned		i;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	while (i < swaptest((int)header->ncmds, g->opt))
	{
		lc_clean = swap_lc(lc, g->opt);
		if (lc_clean.cmd == LC_SEGMENT)
			get_n_sect32((struct segment_command *)lc, ptr, g);
		if (!is_compromised(g->filesize,
					(long)ptr, (long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	return (0);
}
