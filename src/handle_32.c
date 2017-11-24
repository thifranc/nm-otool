/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:40:59 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/24 15:58:30 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	*get_type_32(char **s, struct nlist smb_tab, t_a g)
{
	int		type;

	type = smb_tab.n_type & N_TYPE;
	*(*s + 9) = get_type(type, g, smb_tab.n_sect);
	if (!(smb_tab.n_type & N_EXT))
		*(*s + 9) = ft_tolower(*(*s + 9));
	return (NULL);
}

char	*fill_str_32(struct nlist symb_tab, char *strx_start, t_a g)
{
	int		type;
	char	*prefill;
	char	*s;

	if (symb_tab.n_type & N_STAB)
		return ("");
	if (!((s) = (char*)malloc(sizeof(char) * (11 + ft_strlen(strx_start)))))
		return (NULL);
	type = symb_tab.n_sect == NO_SECT ?
		symb_tab.n_type & N_TYPE :
		symb_tab.n_sect | N_SECT_MASK;
	prefill = symb_tab.n_value ?
		ft_ptrf("%0*x", symb_tab.n_value, 8) :
		"        ";
	s = ft_ptrf("%s   %s\n", prefill, strx_start);
	get_type_32(&s, symb_tab, g);
	return (s);
}

int		symtab_32(struct symtab_command sc, char *ptr, t_a *g)
{
	struct nlist			*st;
	struct nlist			st_c;
	char					*strtbl;
	int						j;

	j = -1;
	g->nsyms = (int)sc.nsyms;
	if (!(g->output = (char**)malloc(sizeof(char *) * sc.nsyms)))
		return (ERR_MALLOC);
	if (!is_compromised(g->filesize, 0, 0, sc.symoff) &&
		!is_compromised(g->filesize, 0, 0, sc.stroff) &&
		st_c.n_un.n_strx < g->filesize - sc.stroff)
	{
		st = (void *)ptr + sc.symoff;
		strtbl = (void *)ptr + sc.stroff;
	}
	else
		return (ERR_IS_COMPROMISED);
	while (++j < g->nsyms)
	{
		st_c = swap_st(st[j], g->opt);
		if (!((g->output)[j] = fill_str_32(st_c, strtbl + st_c.n_un.n_strx, *g)))
			return (ERR_MALLOC);
	}
	return (0);
}

int		get_n_sect32(struct segment_command *sg, t_a *g)
{
	struct section		*sec_32;
	char				*segname;
	char				*sectname;
	long long unsigned	j;

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

int		handle_32(char *ptr, t_a *g)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct load_command		lc_clean;
	long long unsigned		i;
	int						error_code;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	init_g_struct(g);
	while (i < swaptest((int)header->ncmds, g->opt))
	{
		lc_clean = swap_lc(lc, g->opt);
		if ((error_code = handle_lc(lc_clean, lc, g, ptr)) != 0)
			return (error_code);
		if (!is_compromised(g->filesize,
					(long)ptr, (long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	quick_sort(&(g->output), 0, g->nsyms - 1, *g);
	print_tab(g->output, *g);
	return (0);
}
