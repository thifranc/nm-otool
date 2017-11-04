/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:40:59 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/04 10:58:04 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	*fill_str_32(struct nlist symb_tab, char *strx_start, t_a g)
{
	DEBUG
	int		type;
	char	*prefill;
	char	*s;

	if (!((s) = (char*)malloc(sizeof(char) * (19 + ft_strlen(strx_start)))))
		return (NULL);
	type = symb_tab.n_sect == NO_SECT ?
		symb_tab.n_type & N_TYPE:
		symb_tab.n_sect | N_SECT_MASK;

	prefill = symb_tab.n_value ?
		ft_ptrf("%0*x", symb_tab.n_value, 16) :
		"                ",

	s = ft_ptrf("%s %s %s\n", prefill,
		get_type(type, g), strx_start);
	return (s);
}

int		symtab_32(struct symtab_command sc, char *ptr, char ***all_string, t_a *g)
{
	DEBUG
	struct	nlist			*st;
	struct	nlist			st_clean;
	char					*stringtable;
	int						j;

	j = 0;
	g->nsyms = (int)sc.nsyms;
	if (!(*all_string = (char**)malloc(sizeof(char *) * sc.nsyms)))
		return (ERR_MALLOC);
	if (!is_compromised(g->filesize, 0, 0, sc.symoff) &&
			!is_compromised(g->filesize, 0, 0, sc.stroff))
	{
		st = (void *)ptr + sc.symoff;
		stringtable = (void *)ptr + sc.stroff;
	}
	else
		return (ERR_IS_COMPROMISED);
	while (j < g->nsyms)
	{
		st_clean = swap_st(st[j], g->opt);
		if (!((*all_string)[j] = fill_str_32(st_clean,
				stringtable + st_clean.n_un.n_strx, *g)))
			return (ERR_MALLOC);
		j++;
	}
	return (0);
}

int		get_n_sect32(struct segment_command* sg ,t_a *g)
{
	DEBUG
	struct	section	*sec_32;
	char			*segname;
	char			*sectname;
	int				j;


	segname = sg->segname;
	sec_32 = (void*)sg + sizeof(struct segment_command);

	j = 0;
	while (j < swaptest((int)sg->nsects, g->opt))
	{
		sectname = sec_32[j].sectname;
		utils_match_nsect(segname, sectname, g, j);
		j++;
	}
	g->n_sect += j;
	return (0);
}

int		handle_32(char *ptr, t_a g)
{
	DEBUG
	struct	mach_header		*header;
	struct	load_command	*lc;
	struct	load_command	lc_clean;
	int						i;
	char					**output;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header);

	i = 0;
	g.n_sect = 0;
	while (i < swaptest((int)header->ncmds, g.opt))
	{
		lc_clean = swap_lc(lc, g.opt);
		if (lc_clean.cmd == LC_SEGMENT)
		{
			get_n_sect32((struct segment_command *)lc, &g);
		}
		if (lc_clean.cmd == LC_SYMTAB)
		{
			dprintf(1,
			"sections are : bss %d | text %d | data %d \n",
			(int)g.bss_sec, (int)g.text_sec, (int)g.data_sec);
			symtab_32(swap_sc((struct symtab_command *)lc, g.opt), ptr, &output, &g);
		}
		if (!is_compromised(g.filesize,
					(long)ptr, (long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	print_tab(output, g.nsyms);
	return (0);
}
