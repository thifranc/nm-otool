/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/30 17:13:25 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void		print_content64(uint64_t offset,
		struct section_64 *sect, char *ptr, t_a *g)
{
	uint64_t	addr;
	uint64_t	i;
	uint64_t	size;

	i = 0;
	addr = swaptest(sect->addr, g->opt);
	size = swaptest(sect->size, g->opt);
	print_title(*g, sect->sectname, sect->segname);
	if (g->cputype && !ft_strcmp(g->cputype, "ppc"))
		print_ppc_style(size, offset, addr, ptr);
	else
	{
		while (i < size)
		{
			if (i % 16 == 0)
				ft_putstrdel(ft_ptrf("\n%0*x\t", (addr + i), 16));
			ft_putstrdel(ft_ptrf("%0*x ",
						*(ptr + offset + i) & SECTION_TYPE, 2));
			i++;
		}
	}
	write(1, "\n", 1);
}

int				get_n_sect64(struct segment_command_64 *sg, char *ptr, t_a *g)
{
	struct section_64	*sec_64;
	char				*segname;
	char				*sectname;
	long long unsigned	j;

	sec_64 = (void*)sg + sizeof(struct segment_command_64);
	j = 0;
	while (j < swaptest((int)sg->nsects, g->opt))
	{
		sectname = sec_64[j].sectname;
		segname = sec_64[j].segname;
		if (ft_strcmpi(segname, sectname) == 0
				&& !ft_strcmp(sectname, "__text"))
			print_content64(swaptest(sec_64->offset, g->opt), sec_64, ptr, g);
		j++;
	}
	g->n_sect += j;
	return (0);
}

int				handle_64(char *ptr, t_a *g)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct load_command		lc_clean;
	long long unsigned		i;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < swaptest((int)header->ncmds, g->opt))
	{
		lc_clean = swap_lc(lc, g->opt);
		if (lc_clean.cmd == LC_SEGMENT_64)
			get_n_sect64((struct segment_command_64 *)lc, ptr, g);
		if (!is_compromised(g->filesize,
					(long)ptr, (long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	return (0);
}
