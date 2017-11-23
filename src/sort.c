/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:41:41 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/23 16:34:23 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

void	swap(char **a, char **b)
{
	char *t;

	t = *a;
	*a = *b;
	*b = t;
}

int		partition(char **arr, int low, int high, t_a g)
{
	char	*pivot;
	int		i;
	int		j;
	int		jump;

	pivot = arr[high];
	j = low;
	i = (low - 1);
	jump = g.opt & IS_32 ? 11 : 19;
	while (j <= high - 1)
	{
		if (ft_strcmp(arr[j] + jump, pivot + jump) < 0
			|| (
				ft_strcmp(arr[j] + jump, pivot + jump) == 0
				&& ft_strcmp(arr[j], pivot) <= 0))
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort(char ***arr, int low, int high, t_a g)
{
	int pi;

	if (low < high)
	{
		pi = partition(*arr, low, high, g);
		quick_sort(arr, low, pi - 1, g);
		quick_sort(arr, pi + 1, high, g);
	}
}
