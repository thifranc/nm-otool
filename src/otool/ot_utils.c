/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/30 15:26:55 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

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

void	print_classic64(int size, int offset, int addr, char *ptr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			ft_putstrdel(ft_ptrf("\n%0*x\t", (addr + i), 16));
		ft_putstrdel(ft_ptrf("%0*x ", *(ptr + offset + i) & SECTION_TYPE, 2));
		i++;
	}
}

void	print_classic32(int size, int offset, int addr, char *ptr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			ft_putstrdel(ft_ptrf("\n%0*x\t", (addr + i), 8));
		ft_putstrdel(ft_ptrf("%0*x ", *(ptr + offset + i) & SECTION_TYPE, 2));
		i++;
	}
}

void	print_ppc_style(int size, int offset, int addr, char *ptr)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			ft_putstrdel(ft_ptrf("\n%0*x\t", (addr + i), 8));
		ft_putstrdel(ft_ptrf("%0*x%s",
			*(ptr + offset + i) & SECTION_TYPE, 2, ((i + 1) % 4) ? "" : " "));
		i++;
	}
}
