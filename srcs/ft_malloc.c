/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:32:16 by hasmith           #+#    #+#             */
/*   Updated: 2019/01/11 18:49:25 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void set_allocated(void *bp, size_t size) {
    size_t extra_size = GET_SIZE(HDRP(bp)) - size;
    if (extra_size > ALIGN(1 + OVERHEAD)) {
        GET_SIZE(HDRP(bp)) = size;
        GET_SIZE(HDRP(NEXT_BLKP(bp))) = extra_size;
        GET_ALLOC(HDRP(NEXT_BLKP(bp))) = 0;
    }
    GET_ALLOC(HDRP(bp)) = 1;
}

t_pages *data = NULL;
t_pages		*allocated_data()
{
	if (!data)
	{
		printf("INN1\n");
		data = mmap(NULL, sizeof(t_pages), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		printf("INN2: data: %p\n", data);
		data->small_max = getpagesize() * 100 * SMALL_PAGE_SIZE;
		data->small = (t_page*)mmap(NULL, getpagesize() * 100 * SMALL_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data->small = data->small + sizeof(t_page) + 1;		
		// data->small = block_header;
		data->small += OVERHEAD;
		// data->small->end = data->small + 2;
		data->small->next = NULL;
		printf("INN3: data->small: %p\n", data->small);
        GET_SIZE(HDRP(data->small)) = sizeof(t_page) + (getpagesize() * 100 * SMALL_PAGE_SIZE) - OVERHEAD;
        GET_ALLOC(HDRP(data->small)) = 0;
        GET_END(HDRP(data->small)) = 1;
		data->med_max = getpagesize() * 100 * MED_PAGE_SIZE;
		data->med = (t_page*)mmap(NULL, getpagesize() * 100 * MED_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data->med = data->med + sizeof(t_page) + 1;
		// data->med = block_header;
		data->med += OVERHEAD;
		printf("INN4: %p\n", data->med);
		// data->med->end = data->med + 1;
		data->med->next = NULL;
		printf("INN5\n");
        GET_SIZE(HDRP(data->med)) = sizeof(t_page) + (getpagesize() * 100 * MED_PAGE_SIZE) - OVERHEAD;
		printf("INN6\n");
        GET_ALLOC(HDRP(data->med)) = 0;
        GET_END(HDRP(data->med)) = 1;
		printf("INN7\n");
		// data->large = (t_page*)(data->med_max + OVERHEAD + 1);
		// // data->large->end = data->large + 1;
		// data->large->next = NULL;
        // // GET_SIZE(HDRP(data->large)) = 0;
        // GET_ALLOC(HDRP(data->large)) = 0;
        // GET_END(HDRP(data->large)) = 1;

		printf("t_pages: %p, small ptr: %p, med ptr: %p\n", data, data->small+OVERHEAD, data->med+OVERHEAD);
	}
	return (data);
}
// t_pages *data = NULL;
// t_pages		*allocated_data()
// {
// 	if (!data)
// 	{
// 		data = mmap(NULL, sizeof(t_pages) + getpagesize() * 100 * SMALL_PAGE_SIZE
// 					+ getpagesize() * 100 * MED_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// 		data->small_max = getpagesize() * 100 * SMALL_PAGE_SIZE;
// 		data->small = (t_page*)(data + sizeof(t_pages) + OVERHEAD + 1);
// 		// data->small->end = data->small + 2;
// 		data->small->next = NULL;
//         GET_SIZE(HDRP(data->small)) = SMALL_SIZE - OVERHEAD;
//         GET_ALLOC(HDRP(data->small)) = 0;
//         GET_END(HDRP(data->small)) = 1;
// 		data->med_max = getpagesize() * 100 * MED_PAGE_SIZE;
// 		data->med = (t_page*)(data->small_max + OVERHEAD + 1);
// 		// data->med->end = data->med + 1;
// 		data->med->next = NULL;
//         GET_SIZE(HDRP(data->med)) = MED_SIZE - OVERHEAD;
//         GET_ALLOC(HDRP(data->med)) = 0;
//         GET_END(HDRP(data->med)) = 1;
// 		data->large = (t_page*)(data->med_max + OVERHEAD + 1);
// 		// data->large->end = data->large + 1;
// 		data->large->next = NULL;
//         // GET_SIZE(HDRP(data->large)) = 0;
//         GET_ALLOC(HDRP(data->large)) = 0;
//         GET_END(HDRP(data->large)) = 1;
// 	}
// 	return (data);
// }

void *current_avail = NULL;
size_t current_avail_size = 0;
void *ft_malloc(size_t size) {
    size_t newsize = ALIGN(size);
    void *p;
    if (current_avail_size < newsize) {
        current_avail = mmap(0, CHUNK_ALIGN(newsize),
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
        -1, 0);
        current_avail_size = CHUNK_ALIGN(newsize);
    }
    p = current_avail;
	printf("%p\n", p);
    current_avail += newsize;
    current_avail_size -= newsize;
    return p;
}

void *add_page(size_t size) {
    void *bp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    bp += OVERHEAD + 1;
    GET_SIZE(HDRP(bp)) = size - OVERHEAD;
    GET_ALLOC(HDRP(bp)) = 0;
    GET_END(HDRP(bp)) = 1;
    return bp;
}

static void	*small_med_link(t_page *start, long size, long max)
{
	t_page *node;
	// t_page *tmp;

	node = start;
	while (node)
	{
        void *bp = node;
        while (GET_END(HDRP(bp)) != 1) {
            if (!GET_ALLOC(HDRP(bp))
            && ((int)GET_SIZE(HDRP(bp)) >= size)) {
                set_allocated(bp, size);
                return bp;
            }
            bp = NEXT_BLKP(bp);
        }
		node = node->next;
	}
	// if ((char*)node->end + size > (char*)start + max)
	// {
	// 	errno = ENOMEM;
	// 	return (NULL);
	// }
    node = add_page(max);
    set_allocated(node, size);
    return node;
}

void	*mm_malloc(size_t size)
{
	t_page *node;

	size += OVERHEAD;
	if (size <= SMALL_SIZE){
		printf("Size small: %d, Size med: %d\n", (int)GET_SIZE(HDRP(allocated_data()->med)), (int)GET_SIZE(HDRP(allocated_data()->med)));
		return(small_med_link(allocated_data()->small, size, allocated_data()->small_max));}
	if (size <= MED_SIZE)
		return(small_med_link(allocated_data()->med, size, allocated_data()->med_max));
	node = allocated_data()->large;
	//iterate though node to get to NULL
	while (node->next)
	{
		node = node->next;
	}
	node->next = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node->next == NULL) {errno = ENOMEM; return(NULL);}
	node->next->end = (t_page*)((char*)node->next + size);
	node->next->next = NULL;
	return (node->next+1);
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

