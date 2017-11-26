/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/26 18:14:18 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

char	*get_type_64(char **s, struct nlist_64 smb_tab, t_a g)
{
	int	type;

	type = smb_tab.n_type & N_TYPE;
	*(*s + 17) = get_type(type, g, smb_tab.n_sect);
	if (!(smb_tab.n_type & N_EXT))
		*(*s + 17) = ft_tolower(*(*s + 17));
	return (NULL);
}

char	*do_str_64(struct nlist_64 symb_tab, char *strx_start, t_a g)
{
	int		type;
	char	*prefill;
	char	*s;

	if (symb_tab.n_type & N_STAB)
		return ("");
	if (!((s) = (char*)malloc(sizeof(char) * (19 + ft_strlen(strx_start)))))
		return (NULL);
	type = symb_tab.n_sect == NO_SECT ?
		symb_tab.n_type & N_TYPE :
		symb_tab.n_sect | N_SECT_MASK;
	prefill = ((symb_tab.n_type & N_TYPE) == N_PBUD) ||
		((symb_tab.n_type & N_TYPE) == N_UNDF) ?
		"                " :
		ft_ptrf("%0*x", symb_tab.n_value, 16);
	s = ft_ptrf("%s   %s\n", prefill, strx_start);
	get_type_64(&s, symb_tab, g);
	return (s);
}

int		symtab_64(struct symtab_command sc, char *ptr, t_a *g, int j)
{
	struct nlist_64	*st;
	struct nlist_64	st_c;
	char			*strtbl;

	g->nsyms = (int)sc.nsyms;
	if (!(g->output = (char**)malloc(sizeof(char *) * sc.nsyms)))
		return (ERR_MALLOC);
	if (!is_compromised(g->filesize, 0, 0, sc.symoff) &&
		!is_compromised(g->filesize, 0, 0, sc.stroff))
	{
		st = (void *)ptr + sc.symoff;
		strtbl = (void *)ptr + sc.stroff;
	}
	else
		return (ERR_IS_COMPROMISED);
	while (++j < g->nsyms)
	{
		st_c = swap_st_64(st[j], g->opt);
		if (st_c.n_un.n_strx >= g->filesize - sc.stroff)
			return (ERR_IS_COMPROMISED);
		if (!((g->output)[j] = do_str_64(st_c, strtbl + st_c.n_un.n_strx, *g)))
			return (ERR_MALLOC);
	}
	return (0);
}

int		get_n_sect64(struct segment_command_64 *sg, t_a *g)
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
	int						error_code;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	init_g_struct(g);
	while (i < swaptest((int)header->ncmds, g->opt))
	{
		lc_clean = swap_lc(lc, g->opt);
		if ((error_code = handle_lc(lc_clean, lc, g, ptr)) != 0)
			return (error_code);
		if (!is_compromised(g->filesize, (long)ptr,
					(long)((void*)lc + lc_clean.cmdsize), 0))
			lc = (void *)lc + lc_clean.cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	quick_sort(&(g->output), 0, g->nsyms - 1, *g);
	print_tab(g->output, *g);
	return (0);
}
