/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:41:41 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/23 18:15:17 by thifranc         ###   ########.fr       */
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

int		has_to_swap(char *first, char *second, int jump, int options)
{
	if (options & OPT_N)
		return (ft_strcmp(first, second) <= 0
				|| (ft_strcmp(first + jump, second + jump) == 0 && ft_strcmp(first, second) <= 0));
	if (ft_strcmp(first + jump, second + jump) < 0)
		return (options & OPT_R ? 0 : 1);
	else if (ft_strcmp(first + jump, second + jump) == 0 &&
			ft_strcmp(first, second) <= 0)
		return (options & OPT_R ? 0 : 1);
	else
		return (options & OPT_R ? 1 : 0);
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
		if (has_to_swap(arr[j], pivot, jump, g.opt))
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

	if (g.opt & OPT_P)
		return ;
	if (low < high)
	{
		pi = partition(*arr, low, high, g);
		quick_sort(arr, low, pi - 1, g);
		quick_sort(arr, pi + 1, high, g);
	}
}
