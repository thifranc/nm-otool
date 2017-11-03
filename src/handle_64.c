/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/03 11:08:01 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	*fill_str_64(struct nlist_64 symb_tab, char *strx_start, t_a g)
{
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

int		symtab_64(struct symtab_command *sc, char *ptr, char ***all_string, t_a *g)
{
	DEBUG
	struct	nlist_64	*symbol_table;
	char				*stringtable;
	int					j;

	j = 0;
	g->nsyms = (int)sc->nsyms;
	if (!(*all_string = (char**)malloc(sizeof(char *) * sc->nsyms)))
		return (ERR_MALLOC);
	if (!is_compromised(g->filesize, 0, 0, sc->symoff) &&
			!is_compromised(g->filesize, 0, 0, sc->stroff))
	{
		symbol_table = (void *)ptr + sc->symoff;
		stringtable = (void *)ptr + sc->stroff;
	}
	else
		return (ERR_IS_COMPROMISED);
	while (j < g->nsyms)
	{
		if (!((*all_string)[j] = fill_str_64(symbol_table[j],
				stringtable + symbol_table[j].n_un.n_strx, *g)))
			return (ERR_MALLOC);
		j++;
	}
	return (0);
}

int		get_n_sect64(struct segment_command_64* sg ,t_a *g)
{
	struct	section_64	*sec_64;
	char	*segname;
	char	*sectname;
	int		j;


	segname = sg->segname;
	sec_64 = (void*)sg + sizeof(struct segment_command_64);

	j = 0;
	while (j < (int)sg->nsects)
	{
		sectname = sec_64[j].sectname;
		utils_match_nsect(segname, sectname, g, j);
		j++;
	}
	g->n_sect += j;
	return (0);
}

int		handle_64(char *ptr, t_a g)
{
	DEBUG
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	int						i;
	char					**output;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);

	i = 0;
	g.n_sect = 0;
	while (i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			get_n_sect64((struct segment_command_64 *)lc, &g);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			dprintf(1,
			"sections are : bss %d | text %d | data %d \n",
			(int)g.bss_sec, (int)g.text_sec, (int)g.data_sec);
			symtab_64((struct symtab_command *)lc, ptr, &output, &g);
		}
		if (!is_compromised(g.filesize,
					(int)ptr, (int)((void*)lc + lc->cmdsize), 0))
			lc = (void *)lc + lc->cmdsize;
		else
			return (ERR_IS_COMPROMISED);
		i++;
	}
	print_tab(output, g.nsyms);
	return (0);
}
