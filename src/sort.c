/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:41:41 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 18:15:27 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"
 
// A utility function to swap two elements
void swap(char **a, char **b)
{
    char *t;

	t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (char **arr, int low, int high, t_a g)
{
    char *pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
	int	jump;
 
	jump = g.opt & IS_32 ? 11 : 19;
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
		// element of comparison  PUT HOME FUNCTION HERE
        if (ft_strcmp(arr[j] + jump, pivot + jump) < 0)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
		else if (ft_strcmp(arr[j] + jump, pivot + jump) == 0
				&& ft_strcmp(arr[j], pivot) <= 0)
		{
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
		}
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(char ***arr, int low, int high, t_a g)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(*arr, low, high, g);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1, g);
        quickSort(arr, pi + 1, high, g);
    }
}

/* USAGE EXAMPLE
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("Sorted array: n");
    printArray(arr, n);
    return 0;
}
*/
