/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/23 11:56:24 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	*get_type_64(char **s, struct nlist_64 smb_tab, t_a g)
{
	int	type;

	*(*s + 17) = ' ';
	type = smb_tab.n_type & N_TYPE;
	if (type == N_SECT)
	{
		type = smb_tab.n_sect;
		if (type == g.bss_sec)
			*(*s + 17) = 'B';
		else if (type == g.data_sec)
			*(*s + 17) = 'D';
		else if (type == g.text_sec)
			*(*s + 17) = 'T';
		else
			*(*s + 17) = 'S';
	}
	else
	{
		if (type == N_UNDF || type == N_PBUD)
			*(*s + 17) = 'U';
		if (type == N_ABS)
			*(*s + 17) = 'A';
		if (type == N_INDR)
			*(*s + 17) = 'I';
	}
	if (!(smb_tab.n_type & N_EXT))
		*(*s + 17) = ft_tolower(*(*s + 17));
	return (NULL);
}

char	*fill_str_64(struct nlist_64 symb_tab, char *strx_start, t_a g)
{
	int		type;
	char	*prefill;
	char	*s;

	if (symb_tab.n_type & N_STAB)
	{
		return ("");
	}
	if (!((s) = (char*)malloc(sizeof(char) * (19 + ft_strlen(strx_start)))))
		return (NULL);
	type = symb_tab.n_sect == NO_SECT ?
		symb_tab.n_type & N_TYPE :
		symb_tab.n_sect | N_SECT_MASK;
	prefill = symb_tab.n_value ?
		ft_ptrf("%0*x", symb_tab.n_value, 16) :
		"                ";
	s = ft_ptrf("%s   %s\n", prefill, strx_start);
	get_type_64(&s, symb_tab, g);
	return (s);
}

int		symtab_64(struct symtab_command sc, char *ptr,
		t_a *g)
{
	struct nlist_64	*st;
	struct nlist_64	st_clean;
	char			*stringtable;
	int				j;

	j = 0;
	g->nsyms = (int)sc.nsyms;
	if (!(g->output = (char**)malloc(sizeof(char *) * sc.nsyms)))
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
		st_clean = swap_st_64(st[j], g->opt);
		if (!((g->output)[j] = fill_str_64(st_clean,
				stringtable + st_clean.n_un.n_strx, *g)))
			return (ERR_MALLOC);
		j++;
	}
	return (0);
}

int		get_n_sect64(struct segment_command_64 *sg, t_a *g)
{
	struct section_64	*sec_64;
	char				*segname;
	char				*sectname;
	long long unsigned	j;

	segname = sg->segname;
	sec_64 = (void*)sg + sizeof(struct segment_command_64);
	j = 0;
	while (j < swaptest((int)sg->nsects, g->opt))
	{
		sectname = sec_64[j].sectname;
		utils_match_nsect(segname, sectname, g, j);
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
	g->n_sect = 0;
	while (i < swaptest((int)header->ncmds, g->opt))
	{
		lc_clean = swap_lc(lc, g->opt);
		if (lc_clean.cmd == LC_SEGMENT_64)
			get_n_sect64((struct segment_command_64 *)lc, g);
		if (lc_clean.cmd == LC_SYMTAB)
			symtab_64(swap_sc((struct symtab_command *)lc, g->opt), ptr, g);
		if (!is_compromised(g->filesize,
					(long)ptr, (long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	quickSort(&(g->output), 0, g->nsyms - 1, *g);
	print_tab(g->output, *g);
	return (0);
}
