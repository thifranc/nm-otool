/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 18:37:48 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		symtab_64(struct symtab_command *sc, char *ptr, char ***all_string)
{
	DEBUG
	struct	nlist_64	*symbol_table;
	char				*stringtable;
	int					type;
	int					j;

	if (!(*all_string = (char**)malloc(sizeof(char *) * sc->nsyms)))
		return (ERR_MALLOC);

	symbol_table = (void *)ptr + sc->symoff;
	stringtable = (void *)ptr + sc->stroff;

	j = 0;
	while (j < (int)sc->nsyms)
	{
		
		if (!((*all_string)[j] = (char*)malloc(sizeof(char)
			* (19 + ft_strlen(stringtable + symbol_table[j].n_un.n_strx)))))
			return (ERR_MALLOC);
		type = symbol_table[j].n_type & N_TYPE;

		(*all_string)[j] = ft_ptrf("%s %s %s\n",
			symbol_table[j].n_value ?
				ft_ptrf("%0*x", symbol_table[j].n_value, 16) :
				"                ",
			get_type(type), stringtable + symbol_table[j].n_un.n_strx);
		j++;
	}
	j = 0;
	while (j < (int)sc->nsyms)
	{
		dprintf(1, "%s", (*all_string)[j]);
		j++;
	}
	return (0);
}

int		get_n_sect(int nsects, char *segname, t_a *g, struct section_64 *sec_64)
{
	int		j;
	char	*sectname;

	j = 0;
	while (j < nsects)
	{
		sectname = sec_64[j].sectname;
		if (ft_strcmpi(segname, sectname) == 0)
		{
			if (!ft_strcmp(sectname, "__data"))
				g->data_sec = g->n_sect + j + 1;
			else if (!ft_strcmp(sectname, "__text"))
				g->text_sec = g->n_sect + j + 1;
			else if (!ft_strcmp(sectname, "__bss"))
				g->bss_sec = g->n_sect + j + 1;
		}
		j++;
	}
	g->n_sect += j;
	return (0);
}

int		get_n_sect64(struct segment_command_64* sg ,t_a *g)
{
	struct	section_64	*sec_64;
	char	*segname;

	segname = sg->segname;
	sec_64 = (void*)sg + sizeof(struct segment_command_64);

	get_n_sect((int)sg->nsects, segname, g, sec_64);
	return (0);
}

int		handle_64(char *title, char *ptr, t_a g)
{
	DEBUG
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	int						i;
	char					**output;

	dprintf(1, "%s, %d\n", title, g.opt);
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
			dprintf(1, "sections are : bss %d | text %d | data %d \n", (int)g.bss_sec, (int)g.text_sec, (int)g.data_sec);
			symtab_64((struct symtab_command *)lc, ptr, &output);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (0);
}
