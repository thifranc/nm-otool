/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:06:17 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/04 14:51:20 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"
/*
	All structures defined here are always written
	and read to/from disk in big endian order

	<mach/machine.h> is needed here for the cpu_type_t and cpu_subtype_t types
*/

int		fat_arch(char *ptr, t_a g, int archs)
{
	struct fat_arch	*arch;
	int				i;

	i = 0;
	arch = (struct fat_arch *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	dprintf(1, "%d && %lld && %d\n", g.filesize, swap_bits(arch->offset), arch->offset);
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
	arch = (struct fat_arch_64 *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	dprintf(1, "%d && %lld && %llu\n", g.filesize, swap_bits(arch->offset), arch->offset);
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
	dprintf(1, "first magic nb == %x\n", fat->magic);
	if (fat->magic == FAT_MAGIC_64 ||
		fat->magic == FAT_CIGAM_64)
	{
		dprintf(1, "64 type\n");
		fat_arch_64(ptr, g, swap_bits(fat->nfat_arch));
	}
	else
	{
		dprintf(1, "32 type\n");
		fat_arch(ptr, g, swap_bits(fat->nfat_arch));
	}
	return (0);
}
