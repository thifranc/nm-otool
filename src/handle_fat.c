/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:06:17 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/16 11:13:55 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"
/*
	All structures defined here are always written
	and read to/from disk in big endian order

	<mach/machine.h> is needed here for the cpu_type_t and cpu_subtype_t types
*/

char	*arch_name(int arch, int options)
{
	char	*name;

	dprintf(1, "recevied ");
	printBits(sizeof(arch), &arch);
	dprintf(1, "\n");
	name = "failed";
	options = 1;
	if (arch == CPU_TYPE_MC680x0 )
		name = "mc680x0";
	if (arch == CPU_TYPE_X86 || arch == CPU_TYPE_I386 )
		name = "X86";
	if (arch == CPU_TYPE_MC98000 )
		name = "mc98000";
	if (arch == CPU_TYPE_MC88000 )
		name = "mc88000";
	if (arch == CPU_TYPE_HPPA )
		name = "hppa";
	if (arch == CPU_TYPE_ARM )
		name = "arm";
	if (arch == CPU_TYPE_SPARC )
		name = "sparc";
	if (arch == CPU_TYPE_I860 )
		name = "i860";
	if (arch == CPU_TYPE_POWERPC )
		name = "powerpc";

	dprintf(1, "arch is == %s\n", name);
	return (name);
}

char	*arch_name_64(int arch, int options)
{
	char	*name;

	name = "failed";
	options = 1;
	if (arch == CPU_TYPE_MC680x0 )
		name = "mc680x0";
	if (arch == CPU_TYPE_X86_64 )
		name = "x86_64";
	if (arch == CPU_TYPE_MC98000 )
		name = "mc98000";
	if (arch == CPU_TYPE_MC88000 )
		name = "mc88000";
	if (arch == CPU_TYPE_HPPA )
		name = "hppa";
	if (arch == CPU_TYPE_ARM64 )
		name = "arm_64";
	if (arch == CPU_TYPE_SPARC )
		name = "sparc";
	if (arch == CPU_TYPE_I860 )
		name = "i860";
	if (arch == CPU_TYPE_POWERPC64 )
		name = "powerpc_64";

	dprintf(1, "arch is == %s\n", name);
	return (name);
}

int		fat_arch(char *ptr, t_a g, int archs)
{
	struct fat_arch	*arch;
	int				i;

	i = 0;
	dprintf(1, "is 32\n");
	arch = (struct fat_arch *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	arch_name(swap_bits(arch->cputype & CPU_ARCH_MASK), g.opt);
	while (i < archs)
	{
		handle_macho((void *)ptr + swap_bits(arch->offset), g);
		i++;
	}
	return (0);
}

int		fat_arch_64(char *ptr, t_a g, int archs)
{
	struct fat_arch_64	*arch;
	int					i;

	i = 0;
	dprintf(1, "is 64\n");
	arch = (struct fat_arch_64 *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	arch_name(swap_bits(arch->cputype & CPU_ARCH_MASK), g.opt);
	while (i < archs)
	{
		handle_macho((void *)ptr + swap_bits(arch->offset), g);
		i++;
	}
	return (0);
}

int		handle_fat(char *ptr, t_a g)
{
	struct fat_header	*fat;
	int					i;

	i = 0;
	fat = (struct fat_header *)ptr;
	if (fat->magic == FAT_MAGIC_64 ||
		fat->magic == FAT_CIGAM_64)
	{
		fat_arch_64(ptr, g, swap_bits(fat->nfat_arch));
	}
	else
	{
		fat_arch(ptr, g, swap_bits(fat->nfat_arch));
	}
	return (0);
}
