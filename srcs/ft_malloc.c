/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:32:16 by hasmith           #+#    #+#             */
/*   Updated: 2019/01/18 19:01:10 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void set_allocated(void *bp, size_t size, char end) {
    size_t extra_size = GET_SIZE(HDRP(bp)) - size;
    if (extra_size > ALIGN(1 + OVERHEAD)) {
        GET_SIZE(HDRP(bp)) = size;
		GET_ALLOC(HDRP((bp))) = 1;
        GET_END(HDRP(bp)) = 0;
		printf("CHECCKING!!\n");
		printf("size = %d!!\n", (int)GET_SIZE(HDRP(bp)));//This is the problem. Too large and it is trying to add it to the end of memory
        GET_SIZE(HDRP(NEXT_BLKP(bp))) = extra_size;
		printf("CHECCKING2!!\n");
        GET_ALLOC(HDRP(NEXT_BLKP(bp))) = 0;
        GET_END(HDRP(NEXT_BLKP(bp))) = end;
		printf("Last_size: %lu\n", extra_size);
    }
    // GET_ALLOC(HDRP(bp)) = 1;
}

t_pages *data = NULL;
t_pages		*allocated_data()
{
	if (!data)
	{
		printf("INN1\n");
		// data = (t_pages*)mmap(NULL, sizeof(t_pages) + sizeof(t_page) + OVERHEAD + (getpagesize() * 100 * SMALL_PAGE_SIZE) + (getpagesize() * 100 * MED_PAGE_SIZE), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data = (t_pages*)mmap(NULL, sizeof(t_pages), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("INN2: data: %p\n", data);
		// data->small_max = getpagesize() * 100 * SMALL_PAGE_SIZE;
		data->small_max = getpagesize() * 1 * SMALL_PAGE_SIZE;//breaks
		// data->small = (t_page*)data + sizeof(t_pages) + 1;
		data->small = (t_page*)mmap(NULL, data->small_max, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data->small->end = data->small + data->small_max;
		data->small->next = NULL;
		data->small = data->small + sizeof(t_page) + OVERHEAD + 1;
		
		printf("INN3: data->small: %p\n", data->small);
        GET_SIZE(HDRP(data->small)) = (data->small_max) - OVERHEAD - sizeof(t_page);
        GET_ALLOC(HDRP(data->small)) = 0;
        GET_END(HDRP(data->small)) = 1;
		printf("INN3BBB\n");
		// data->med_max = getpagesize() * 100 * MED_PAGE_SIZE;
		data->med_max = getpagesize() * 1 * MED_PAGE_SIZE;///breaks
		printf("INN3CCC\n");
		// data->med = (t_page*)END_PG(data->small) + 1;////////????????
		data->med = (t_page*)mmap(NULL, data->med_max, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("INN3DDDD\n");
		data->med->end = (void*)(data->med + data->med_max);
		printf("INN3EEEEEE\n");
		data->med->next = NULL;
		printf("INN4\n");
		data->med = data->med + sizeof(t_page) + OVERHEAD + 1;
		
		printf("INN5\n");
        GET_SIZE(HDRP(data->med)) = (data->med_max) - OVERHEAD - sizeof(t_page);
		printf("INN6\n");
        GET_ALLOC(HDRP(data->med)) = 0;
        GET_END(HDRP(data->med)) = 1;
		printf("INN7\n");

		// data->large = (t_page*)END_PG(data->med) + 1;
		data->large = (t_page*)mmap(NULL, sizeof(t_page) + OVERHEAD + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data->large->next = NULL;
		data->large->end = data->large + sizeof(t_page) + OVERHEAD + 1;
		printf("Original ptr for larg: %p, and larg->next: %p\n", data->large, data->large->next);
		data->large += sizeof(t_page) + OVERHEAD + 1;
		GET_SIZE(HDRP(data->large)) = 0;
		GET_ALLOC(HDRP(data->large)) = 1;
		printf("Finding next large: %p, size: %d, allocated: %d\n", NEXT_PG(data->large), (int)GET_SIZE(HDRP(data->large)),(int)GET_ALLOC(HDRP(data->large)));


		printf("t_pages: %p, small ptr: %p, med ptr: %p\n", data, data->small+OVERHEAD, data->med+OVERHEAD);
	}
	return (data);
}
// t_pages *data = NULL;
// t_pages		*allocated_data()
// {
// 	if (!data)
// 	{
// 		printf("INN1\n");
// 		data = mmap(NULL, sizeof(t_pages), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 		printf("INN2: data: %p\n", data);
// 		data->small_max = getpagesize() * 100 * SMALL_PAGE_SIZE;
// 		data->small = (t_page*)mmap(NULL, /*sizeof(t_page) + OVERHEAD + */getpagesize() * 100 * SMALL_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 		data->small->end = data->small + data->small_max;
// 		data->small->next = NULL;
// 		data->small = data->small + sizeof(t_page) + OVERHEAD + 1;
		
// 		printf("INN3: data->small: %p\n", data->small);
//         GET_SIZE(HDRP(data->small)) = sizeof(t_page) + (getpagesize() * 100 * SMALL_PAGE_SIZE) - OVERHEAD;
//         GET_ALLOC(HDRP(data->small)) = 0;
//         GET_END(HDRP(data->small)) = 1;
// 		data->med_max = getpagesize() * 100 * MED_PAGE_SIZE;
// 		data->med = (t_page*)mmap(NULL, /*sizeof(t_page) + OVERHEAD + */getpagesize() * 100 * MED_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 		data->med->end = data->med + data->med_max;
// 		data->med->next = NULL;
// 		data->med = data->med + sizeof(t_page) + OVERHEAD + 1;
// 		// data->med = block_header;
// 		// data->med += OVERHEAD + 1;
// 		printf("INN4: %p\n", data->med);
// 		// data->med->end = data->med + 1;
		
// 		printf("INN5\n");
//         GET_SIZE(HDRP(data->med)) = sizeof(t_page) + (getpagesize() * 100 * MED_PAGE_SIZE) - OVERHEAD;
// 		printf("INN6\n");
//         GET_ALLOC(HDRP(data->med)) = 0;
//         GET_END(HDRP(data->med)) = 1;
// 		printf("INN7\n");
// 		// data->large = (t_page*)(data->med_max + OVERHEAD + 1);
// 		// // data->large->end = data->large + 1;

// 		// data->large = NULL;
// 		data->large = (t_page*)mmap(NULL, sizeof(t_page) + OVERHEAD, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 		data->large->next = (t_page*)mmap(NULL, sizeof(t_page) + OVERHEAD, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);;///////////////
// 		data->large->end = data->large + sizeof(t_page) + OVERHEAD;
// 		printf("Original ptr for larg: %p, and larg->next: %p\n", data->large, data->large->next);
// 		data->large += sizeof(t_page) + OVERHEAD + 1;
// 		GET_SIZE(HDRP(data->large)) = 0;
// 		GET_ALLOC(HDRP(data->large)) = 1;
// 		printf("Finding next large: %p, size: %d, allocated: %d\n", NEXT_PG(data->large), (int)GET_SIZE(HDRP(data->large)),(int)GET_ALLOC(HDRP(data->large)));

// // 0x101071000

// 		// data->large = NULL;

//         // // GET_SIZE(HDRP(data->large)) = 0;
//         // GET_ALLOC(HDRP(data->large)) = 0;
//         // GET_END(HDRP(data->large)) = 1;

// 		printf("t_pages: %p, small ptr: %p, med ptr: %p\n", data, data->small+OVERHEAD, data->med+OVERHEAD);
// 	}
// 	return (data);
// }

t_page *add_page(size_t size) {
    t_page *bp = (t_page*)mmap(NULL, size/*plus OVERHEAD and t_page)*/, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	bp->next = NULL;
	bp->end = bp + size;
    bp += sizeof(t_page) + OVERHEAD + 1;
    GET_SIZE(HDRP(bp)) = size - sizeof(t_page) - OVERHEAD;
    GET_ALLOC(HDRP(bp)) = 0;
    GET_END(HDRP(bp)) = 1;
    return (bp);
}

static void	*small_med_link(t_page *start, long size, long max)
{
	t_page *node;
	t_page *last;
	// t_page *tmp;

	node = start;
	last = node;
	while (node)
	{
		printf("IIINNNNN   SSSSSMMMMAAAALLLL MED\n");
        void *bp = node;
        while (GET_END(HDRP(bp)) != 1) {
            if (!GET_ALLOC(HDRP(bp))
            && ((int)GET_SIZE(HDRP(bp)) >= size)) {
                set_allocated(bp, size, 0);
                return bp;
            }
			printf("SIZE: %d\n", (int)GET_SIZE(HDRP(bp)));
            bp = NEXT_BLKP(bp);
        }
		if (GET_END(HDRP(bp)) == 1){
            if (!GET_ALLOC(HDRP(bp))
            && ((int)GET_SIZE(HDRP(bp)) >= size)) {
                set_allocated(bp, size, 1);
                return bp;
            }
		}
		printf("SIZE2: %d\n", (int)GET_SIZE(HDRP(node)));
		// node = node->next;
		last = node;
		node = NEXT_PG(node);
	}
	// if ((char*)node->end + size > (char*)start + max)
	// {
	// 	errno = ENOMEM;
	// 	return (NULL);
	// }
	printf("Trying to allocate new page\n");
    last->next = add_page(max);
	printf("Allocated new page\n");
    set_allocated(last->next, size, 1); ////This problem will go away if you add back the right page sizes
	printf("set new page with memory\n");
    return (last->next + 1);
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
	if (size <= MED_SIZE)
		return(small_med_link(allocated_data()->med, size, allocated_data()->med_max));
	node = allocated_data()->large;
	//iterate though node to get to NULL
	printf("Lrg node: %p\n", node);
	printf("Should be same as orig larg ptr: %p, and next should be the same: %p\n", (t_page *)(node - OVERHEAD - sizeof(t_page)), NEXT_PG(node));
	// while (node != NULL){
	// 	printf("large_string loop: %p, next node: %p\n", node, NEXT_PG(node));
	// 	node = NEXT_PG(node);
	// }
	// node = (t_page*)mmap(NULL, size + sizeof(t_page) + OVERHEAD, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	// if (node == NULL) {errno = ENOMEM; return(NULL);}
	// printf("AFTER Lrg node: %p\n", node);
	// node->next = NULL;
	// node += sizeof(t_page);
	// node += OVERHEAD + 1;
	// GET_SIZE(HDRP(node)) = size;
	// GET_ALLOC(HDRP(node)) = 1;//not_needed
	// GET_END(HDRP(node)) = 1;//not needed
	
// 0x10a98f220
// 0x10a98f220

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


// void set_allocated(void *bp, size_t size) {
//     size_t extra_size = GET_SIZE(HDRP(bp)) - size;
//     if (extra_size > ALIGN(1 + OVERHEAD)) {
//         GET_SIZE(HDRP(bp)) = size;
//         GET_SIZE(HDRP(NEXT_BLKP(bp))) = extra_size;
//         GET_ALLOC(HDRP(NEXT_BLKP(bp))) = 0;
//     }
//     GET_ALLOC(HDRP(bp)) = 1;
// }

// void extend(size_t new_size) {
//     size_t chunk_size = CHUNK_ALIGN(new_size);
//     void *bp = mmap(0, chunk_size,
//     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
//     -1, 0);
//     GET_SIZE(HDRP(bp)) = chunk_size;
//     GET_ALLOC(HDRP(bp)) = 0;
//     GET_SIZE(HDRP(NEXT_BLKP(bp))) = 0;
//     GET_ALLOC(HDRP(NEXT_BLKP(bp))) = 1;
// }

// void *first_bp;
// int mm_init() {
//     //  mmap(0, sizeof(block_header),
//     //  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
//     //  -1, 0);
//     //  first_bp = mmap(0, 0,
//     //  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
//     //  -1, 0);
//     first_bp = mmap(0, sizeof(block_header),
//     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
//     -1, 0);
//     GET_SIZE(HDRP(first_bp)) = 0;
//     GET_ALLOC(HDRP(first_bp)) = 1;
//     return 0;
// }

// void *mm_malloc(size_t size) {
//     int new_size = (int)ALIGN(size + OVERHEAD);
//     void *bp = first_bp;
//     while (GET_SIZE(HDRP(bp)) != 0) {
//         if (!GET_ALLOC(HDRP(bp))
//         && ((int)GET_SIZE(HDRP(bp)) >= new_size)) {
//             set_allocated(bp, new_size);
//             return bp;
//         }
//         bp = NEXT_BLKP(bp);
//     }
//     extend(new_size);
//     set_allocated(bp, new_size);
//     return bp;
// }


// void *current_avail = NULL;
// size_t current_avail_size = 0;
// void *ft_malloc(size_t size) {
//     size_t newsize = ALIGN(size);
//     void *p;
//     if (current_avail_size < newsize) {
//         current_avail = mmap(0, CHUNK_ALIGN(newsize),
//         PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
//         -1, 0);
//         current_avail_size = CHUNK_ALIGN(newsize);
//     }
//     p = current_avail;
//     current_avail += newsize;
//     current_avail_size -= newsize;
//     return p;
// }

