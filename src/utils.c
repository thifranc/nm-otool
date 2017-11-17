/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 16:32:12 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	*get_cpu_string(int cputype)
{
	char	*ret;

	ret = "";
	ret = cputype == CPU_TYPE_VAX ? "vax" : ret;
	ret = cputype == CPU_TYPE_MC680x0 ? "mc680x0" : ret;
	ret = cputype == CPU_TYPE_X86 ? "x86" : ret;
	ret = cputype == CPU_TYPE_I386 ? "i386" : ret;
	ret = cputype == CPU_TYPE_X86_64 ? "x86_64" : ret;
	ret = cputype == CPU_TYPE_MC98000 ? "mc98000" : ret;
	ret = cputype == CPU_TYPE_HPPA ? "hppa" : ret;
	ret = cputype == CPU_TYPE_ARM ? "arm" : ret;
	ret = cputype == CPU_TYPE_ARM64 ? "arm64" : ret;
	ret = cputype == CPU_TYPE_MC88000 ? "mc88000" : ret;
	ret = cputype == CPU_TYPE_SPARC ? "sparc" : ret;
	ret = cputype == CPU_TYPE_I860 ? "i860" : ret;
	ret = cputype == CPU_TYPE_POWERPC ? "ppc" : ret;
	ret = cputype == CPU_TYPE_POWERPC64 ? "ppc64" : ret;
	return (ret);
}

void	print_tab(char **tab, struct s_a g)
{
	int		i;
	char	*title;

	i = 0;
	title = "";
	if (g.opt & MANY_ARGS)
		title = ft_ptrf("\n%s\n", g.title);
	if (g.opt & MANY_ARCHS)
		title = ft_ptrf("\n%s (for architecture %s)\n", g.title, g.cputype);
	ft_putstr(title);
	while (i < g.nsyms)
	{
		ft_putstr(tab[i]);
		i++;
	}
}

void	utils_match_nsect(char *segname, char *sectname, t_a *g, int cur)
{
	if (ft_strcmpi(segname, sectname) == 0)
	{
		if (!ft_strcmp(sectname, "__data"))
			g->data_sec = g->n_sect + cur + 1;
		else if (!ft_strcmp(sectname, "__text"))
			g->text_sec = g->n_sect + cur + 1;
	}
	else if (!ft_strcmp(segname, "__DATA") && !ft_strcmp(sectname, "__bss"))
		g->bss_sec = g->n_sect + cur + 1;
}

struct load_command	swap_lc(struct load_command *lc, char opt)
{
	struct load_command	lc_clean;

	lc_clean = *lc;
	lc_clean.cmd = swaptest(lc->cmd, opt);
	lc_clean.cmdsize = swaptest(lc->cmdsize, opt);
	return (lc_clean);
}

struct symtab_command	swap_sc(struct symtab_command *sc, char opt)
{
	struct symtab_command	sc_clean;

	sc_clean = *sc;
	sc_clean.symoff = swaptest(sc->symoff, opt);
	sc_clean.stroff = swaptest(sc->stroff, opt);
	sc_clean.nsyms = swaptest(sc->nsyms, opt);
	return (sc_clean);
}

struct nlist	swap_st(struct nlist st, char opt)
{
	struct nlist	st_clean;

	st_clean = st;
	//st_clean.n_sect = swaptest(st.n_sect, opt);
	//st_clean.n_type = swaptest(st.n_type, opt);
	st_clean.n_value = swaptest(st.n_value, opt);
	st_clean.n_un.n_strx = swaptest(st.n_un.n_strx, opt);
	return (st_clean);
}

struct nlist_64	swap_st_64(struct nlist_64 st, char opt)
{
	struct nlist_64	st_clean;

	st_clean = st;
	//st_clean.n_sect = swaptest(st.n_sect, opt);
	//st_clean.n_type = swaptest(st.n_type, opt);
	st_clean.n_value = swaptest(st.n_value, opt);
	st_clean.n_un.n_strx = swaptest(st.n_un.n_strx, opt);
	return (st_clean);
}
/*
 * move byte 3 to byte 0
 * move byte 1 to byte 2
 * move byte 2 to byte 1
 * move byte 0 to byte 3
 */

long long unsigned		swap_bits(long long int num)
{
	return ((num>>24)&0xff) |
		((num<<8)&0xff0000) |
		((num>>8)&0xff00) |
		((num<<24)&0xff000000);
}

long long unsigned		swaptest(long long int a, char options)
{
	if (options & TO_SWAP)
		return (swap_bits(a));
	else
		return (a);
}


