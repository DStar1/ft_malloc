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

	node = start;
	while (node)
	{
        void *bp = node;
        void *start1 = node;
        while (GET_END(HDRP(bp)) != 1) // Possibly need to change malloc so that I dont allocate on the last header when end == 1
        {
            if (GET_ALLOC(HDRP(bp)) && (bp == ptr)) {
                printf("\n\n\n\nFOUND and will free\n");
                GET_ALLOC(HDRP(bp)) = 0;
                free_defrag(start1);
                return (1);
            }
            bp = NEXT_BLKP(bp);
        }
        node = NEXT_PG(node);
	}
    return (0);
}

/*
** Free pointer memory and set as unallocated
*/

int ft_free(void *ptr)
{
    t_page *node;
    t_page *tmp;

    // printf("Starting free function\n");
	if (free_small_med(allocated_data()->small, ptr))
    {
        // printf("Small\n");
		return(1);
    }
    else if (free_small_med(allocated_data()->med, ptr))
    {
        // printf("Med\n");
		return(1);
    }
    node = allocated_data()->large;

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
    return (0);
}