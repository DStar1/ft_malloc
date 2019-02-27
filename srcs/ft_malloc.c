/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:32:16 by hasmith           #+#    #+#             */
/*   Updated: 2019/02/26 20:50:01 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void set_allocated(void *bp, size_t size, char end) {
    size_t extra_size = GET_SIZE(HDRP(bp)) - size;
	GET_SIZE(HDRP(bp)) = size;
	GET_ALLOC(HDRP((bp))) = 1;
	GET_END(HDRP(bp)) = 0;
	GET_SIZE(HDRP(NEXT_BLKP(bp))) = extra_size;
	GET_ALLOC(HDRP(NEXT_BLKP(bp))) = 0;
	GET_END(HDRP(NEXT_BLKP(bp))) = end;
}

t_pages *data = NULL;
int SIZE_ALLOC = 1;// for debug, adding new pages. Will be 100
t_pages		*allocated_data()
{
	if (!data)
	{
		data = (t_pages*)mmap(NULL, sizeof(t_pages) + sizeof(t_page) + 1 + (getpagesize() * SIZE_ALLOC * SMALL_PAGE_SIZE) + (getpagesize() * SIZE_ALLOC * MED_PAGE_SIZE), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

		data->small_max = getpagesize() * SIZE_ALLOC * SMALL_PAGE_SIZE;
		// void *pEnd =(data+sizeof(t_pages) + sizeof(t_page) + 1 + (getpagesize() * SIZE_ALLOC * SMALL_PAGE_SIZE) + (getpagesize() * SIZE_ALLOC * MED_PAGE_SIZE));
		data->small = (t_page*)(data + sizeof(t_pages) + 1);
		data->small->end = (void*)data->small + data->small_max;
		data->small->next = NULL;
		data->small = data->small + sizeof(t_page) + OVERHEAD + 1;
        GET_SIZE(HDRP(data->small)) = (data->small_max) - OVERHEAD - sizeof(t_page);
        GET_ALLOC(HDRP(data->small)) = 0;
        GET_END(HDRP(data->small)) = 1;

		data->med_max = getpagesize() * SIZE_ALLOC * MED_PAGE_SIZE;//change to * 100
		data->med = (t_page*)(END_PG(data->small) + 1);
		data->med->end = (END_PG(data->small) + data->med_max); 
		data->med->next = NULL;
		data->med = data->med + sizeof(t_page) + OVERHEAD + 1;
        GET_SIZE(HDRP(data->med)) = (data->med_max) - OVERHEAD - sizeof(t_page);
        GET_ALLOC(HDRP(data->med)) = 0;
        GET_END(HDRP(data->med)) = 1;
	
		data->large = (t_page*)(END_PG(data->med) + 1);
		data->large->next = NULL;
		data->large->end = data->large + sizeof(t_page);
		// data->large = data->large + sizeof(t_page) + OVERHEAD + 1;
		// GET_SIZE(HDRP(data->large)) = 0;
		// GET_ALLOC(HDRP(data->large)) = 1;
		// printf("INNN7 %p == %p?\n", pEnd, data->large);
	}
	return (data);
}

t_page *add_page(size_t size) {
    t_page *bp = (t_page*)mmap(NULL, size + OVERHEAD + sizeof(t_page)/*plus OVERHEAD and t_page)*/, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	bp->next = NULL;
	bp->end = bp + size;
    bp = bp + sizeof(t_page) + OVERHEAD + 1;
    GET_SIZE(HDRP(bp)) = size - sizeof(t_page) - OVERHEAD;
    GET_ALLOC(HDRP(bp)) = 0;
    GET_END(HDRP(bp)) = 1;

    return (bp);
}

static void	*small_med_link(t_page *start, long size, long max)
{
	t_page *node;
	t_page *last;

	node = start;
	last = node;
	while (node)
	{
		printf("IIINNNNN   SSSSSMMMMAAAALLLL MED\n");
        void *bp = node;
        while (GET_END(HDRP(bp)) != 1) {
            if (!GET_ALLOC(HDRP(bp))
            && ((int)GET_SIZE(HDRP(bp)) >= size)) {
				printf("\nNOT END\n");
                set_allocated(bp, size, 0);
                return bp;
            }
			printf("SIZE: %d\n", (int)GET_SIZE(HDRP(bp)));
			printf("\nstr: %s\n", (char*)bp);
            bp = NEXT_BLKP(bp);
        }
		if (GET_END(HDRP(bp)) == 1){
            if (!GET_ALLOC(HDRP(bp))
            && ((int)GET_SIZE(HDRP(bp)) >= size)) {
				printf("\nEND\n");
                set_allocated(bp, size, 1);
                return bp;
            }
		}
		printf("SIZE2: %d\n", (int)GET_SIZE(HDRP(node)));
		last = node;
		node = NEXT_PG(node);
		printf("Next Node: %p\n", node);
	}
	printf("Trying to allocate new page\n");
    NEXT_PG(last) = add_page(max);
	printf("Allocated new page\n");
    set_allocated(NEXT_PG(last), size, 1); ////This problem will go away if you add back the right page sizes
	printf("set new page with memory\n");
    return (NEXT_PG(last));
}

void	*ft_malloc(size_t size)
{
	t_page *node;

	size += OVERHEAD;
	printf("SSSSSIIIIZZZZEEEE: %d\n", (int)size);
	if (size <= SMALL_SIZE){
		printf("OVERHEAD size = %d\n", (int)OVERHEAD);
		printf("Size small: %d, Size med: %d\n", (int)GET_SIZE(HDRP(allocated_data()->small)), (int)GET_SIZE(HDRP(allocated_data()->med)));
		return(small_med_link(allocated_data()->small, size, allocated_data()->small_max));}
	if (size <= MED_SIZE){
		printf("Size med: %d\n", (int)allocated_data()->med_max);
		return(small_med_link(allocated_data()->med, size, allocated_data()->med_max));
	}
	node = allocated_data()->large;
	//iterate though node to get to NULL
	printf("Lrg node: %p\n", node);
	printf("Should be same as orig larg ptr: %p, and next should be the same: %p\n", (t_page *)(node - OVERHEAD - sizeof(t_page)), NEXT_PG(node));
	//iterate though node to get to NULL
	while (node->next)
	{
		node = node->next;
	}
	// node->next = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	node->next = mmap(NULL, size + sizeof(t_page) + OVERHEAD, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node->next == NULL) {errno = ENOMEM; return(NULL);}
	node->next->end = (t_page*)((char*)node->next + size + sizeof(t_page) + OVERHEAD);
	node->next->next = NULL;
	node->next += sizeof(t_page) + OVERHEAD + 1;
	GET_SIZE(HDRP(node->next)) = 0;
	GET_ALLOC(HDRP(node->next)) = 1;
	return (node->next + 1);
}
