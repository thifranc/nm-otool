/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/26 10:37:52 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/otool.h"

int		utils_match_nsect(char *segname,
		char *sectname, t_a *g)
{
	if (ft_strcmpi(segname, sectname) == 0)
	{
		if (g->opt & OPT_D && !ft_strcmp(sectname, "__data"))
			return (1);
		else if (!ft_strcmp(sectname, "__text"))
			return (1);
	}
	return (0);
}

static void		print_content(struct section_64 *sect, char *ptr,
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
/*
	if (!g->is_lib && !g->is_fat)
		ft_printf("%s:\n", *(g->files));
*/
	while (i < size)
	{
		if (i % 16 == 0)
			dprintf(1, "\n%016llx\t", (sect->addr + i));
		dprintf(1, "%02x ", *(ptr + offset + i) & SECTION_TYPE);
		i++;
	}
	write(1, "\n", 1);
}

int		get_n_sect64(struct segment_command_64 *sg, char *ptr, t_a *g)
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
		if (utils_match_nsect(segname, sectname, g))
		{
			print_content(sec_64, ptr, g);
		}
		j++;
	}
	g->n_sect += j;
	return (0);
}

int		handle_64(char *ptr, t_a *g)
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
