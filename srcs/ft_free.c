/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:32:16 by hasmith           #+#    #+#             */
/*   Updated: 2019/01/15 17:17:41 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Go through and merge unused space in small and med lists
*/

void	*free_defrag(void *start)
{
    void *bp = start;

    while (GET_END(HDRP(bp)) != 1) // Possibly need to change malloc so that I dont allocate on the last header when end == 1
    {
        void *new = bp;
        size_t size = 0;
        size_t old_size = GET_SIZE(HDRP(bp));//get rid of
        char end = 0;
        while (!GET_ALLOC(HDRP(new))) {
            size += GET_SIZE(HDRP(new));
            end = GET_END(HDRP(new));
            GET_SIZE(HDRP(bp)) = size;
            GET_END(HDRP(bp)) = end;
            printf("Concatinating: end = %d, old_size = %d; cur_size = %d\n", (int)end, (int)old_size, (int)size);
            if (end == 1)
                return (NULL);
            new = NEXT_BLKP(new);
        }
        bp = NEXT_BLKP(bp);
    }
    return (NULL);
}

int free_small_med(void *start, void *ptr)
{
	t_page *node;
	// t_page *tmp;

	node = start;
	while (node)
	{
        printf("\nIn new page\n");
        void *bp = node;
        void *start = node;
        while (GET_END(HDRP(bp)) != 1) // Possibly need to change malloc so that I dont allocate on the last header when end == 1
        {
            printf("\nIn while loop: end = %d, get_alloc = %d; ptr = %p, cur_ptr = %p\n", GET_END(HDRP(bp)), GET_ALLOC(HDRP(bp)), ptr, bp);
            if (GET_ALLOC(HDRP(bp)) && (bp == ptr)) {
                // set_allocated(bp, size, 0);
                printf("\n\n\n\nFOUND and will free\n");
                GET_ALLOC(HDRP(bp)) = 0;
                free_defrag(start);
                return (1);
            }
			// printf("SIZE: %d\n", (int)GET_SIZE(HDRP(bp)));
            bp = NEXT_BLKP(bp);
        }
		// node = node->next;
        node = NEXT_PG(node);
	}
    return (0);//not in
}

/*
** Free pointer memory and set as unallocated
*/

int ft_free(void *ptr)
{
    t_page *node;
    t_page *tmp;

    printf("Starting free function\n");
	if (free_small_med(allocated_data()->small, ptr))
    {
        printf("Small\n");
		return(1);
    }
    else if (free_small_med(allocated_data()->med, ptr))
    {
        printf("Med\n");
		return(1);
    }
    node = allocated_data()->large;
    // printf("Large: %p\n", node);
    // while (node){
    //     printf("lrg_ptr: %p\n", node);
    //     tmp = node;
	// 	node = NEXT_PG(node);
    // }


	while (node->next != NULL)
	{
        printf("In LARGE loop\n");
		if (ptr == node->next + 1)
		{
            printf("Freeing %p\n", node->next + 1);
			tmp = node->next->next;
			munmap(node->next, (char*)node->next->end - (char*)node->next);
            node->next = tmp;
			return (1);
		}
		node = node->next;
	}

	//iterate though node to get to NULL
	// while (NEXT_PG(node) != NULL)
	// {
    //     printf("In loop\n");
	// 	if (ptr == NEXT_PG(node))
	// 	{
    //         printf("ptr == next_pg\n");
	// 		tmp = NEXT_PG(NEXT_PG(node));
	// 		munmap(NEXT_PG(node), GET_SIZE(HDRP(NEXT_PG(node))));
    //         NEXT_PG(node) = tmp;
	// 		return (0);//(void)(NEXT_PG(node) = tmp));
	// 	}
	// 	node = NEXT_PG(node);
	// }
    // if (ptr == node)
    // {
    //     tmp = NEXT_PG(node);
    //     munmap(node, GET_SIZE(HDRP(node)));
    //     node = tmp;// is NULL
    // }
    return (0);
}