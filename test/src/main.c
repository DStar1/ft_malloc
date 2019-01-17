/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:39:44 by tanguy            #+#    #+#             */
/*   Updated: 2019/01/16 17:53:12 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

#define M (1024 * 1024)
#include <string.h>
void print(char *s)
{
	write(1, s, strlen(s));
}

// int main()
// {
// 	malloc(25);
// 	malloc(1024);
// 	malloc(1024 * 32);
// 	malloc(1024 * 1024);
// 	malloc(1024 * 1024 * 16);
// 	malloc(1024 * 1024 * 128);
// 	show_alloc_mem();
// 	return 0;
// }

// int	main()
// {
// 	char *addr;

// 	addr = malloc(16);
// 	free(NULL);
// 	free((void*)addr + 5);
// 	if (realloc((void*) + 5, 10) == NULL)
// 	{
// 		print("Bonjour\n");
// 	}
// 	return 0;
// }

// int		main()
// {
// 	// ft_printf("Project %s successfully created! \n", argv[0]);
// 	char *new = ft_malloc(sizeof(char)*9);
// 	strcpy(new, "harrison");
// 	printf("%s\n", new);
// 	// char *new2 = ft_malloc(sizeof(char)*9);
// 	// strcpy(new2, "notharry");
// 	// printf("%s, %s\n", new, new2);
// 	return (0);
// }
int		main()
{
	// ft_printf("Project %s successfully created! \n", argv[0]);
	char *new = ft_malloc(sizeof(char)*2);
	// char *new1 = ft_malloc(sizeof(char)*9);
	strcpy(new, "h");
	// printf("%s\n", new);
	char *new2 = ft_malloc(sizeof(char)*9);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(new2, "notharry");

	char *med5 = ft_malloc(SMALL_SIZE + 1);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(med5, "notharrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");


	char *new3 = ft_malloc(sizeof(char)*18);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(new3, "notharryfghdfhd");
	char *new4 = ft_malloc(sizeof(char)*27);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(new4, "notharrydfghdfghdfghdfgh");

	char *med6 = ft_malloc(SMALL_SIZE + 18);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(med6, "isharrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");
	char *med7 = ft_malloc(SMALL_SIZE + 6);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(med7, "wowharrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");

	char *lrg1 = ft_malloc(MED_SIZE + 6);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(lrg1, "lrg1harrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");

	char *lrg2 = ft_malloc(MED_SIZE + 16);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(lrg2, "lrg2harrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");	

	char *lrg3 = ft_malloc(MED_SIZE + 1);
	// char *new2 = ft_malloc((32 * 4096)+1);
	strcpy(lrg3, "lrg3harrydfghdfghdfghdfghkjfhslfkjahsflksfjhslkfhsfk");	

	printf("%s %p %d: %s %p %d: %s %p %lu: %s %p %lu:\n", new, new, new[0] - new[1], new2, new2, new2[0] - new2[8], new3, new3, sizeof(new3), new4, new4, sizeof(new4));
	printf("%s\n %p:  \n%s\n %p\n%s\n %p\n", med5, med5, med6, med6, med7, med7);
	printf("%s\n %p:  \n%s\n %p\n%s\n %p\n", lrg1, lrg1, lrg2, lrg2, lrg3, lrg3);

	// ft_free(med6);
	// ft_free(med7);
	// ft_free(lrg1);
	ft_free(lrg2);

	return (0);
}

// int	main()
// {
// 	char *addr1;
// 	char *addr2;
// 	char *addr3;

// 	addr1 = (char*)malloc(16 * M);
// 	strcpy(addr1, "Bonjour\n");
// 	print(addr1);
// 	addr2 = (char*)malloc(16 * M);
// 	addr3 = realloc(addr1, 128 * M);
// 	addr3[127 * M] = 42;
// 	print(addr3);
// 	return 0;
// }

// int	main()
// {
// 	int  i;
// 	char *addr;

// 	(void)addr;
// 	i = 0;
// 	while (i < 1024)
// 	{
// 		addr = (char*)malloc(1024);
// 		if (addr == NULL)
// 		{
// 			ft_putstr("NULL returned!\n");
// 			return 0;
// 		}
// 		addr[0] = 42;
// 		free(addr);
// 		i++;
// 	}
// 	return 0;
// }

// int	main()
// {
// 	int  i;
// 	char *addr;
// 	char *tmp;

// 	(void)addr;
// 	i = 0;
// 	while (i < 1024)
// 	{
// 		addr = (char*)malloc(1024);
// 		addr = realloc(addr, 64);
// 		if (addr == NULL)
// 		{
// 			ft_putstr("NULL returned!\n");
// 			return 0;
// 		}
// 		addr[0] = 42;
// 		free(addr);
// 		i++;
// 	}
// 	addr = (char*)malloc(1024);
// 	strcpy(addr, "Bonjour\n");
// 	tmp = (char*)malloc(128);
// 	addr = realloc(addr, 64);
// 	free(tmp);
// 	print(addr);
// 	free(addr);
// 	free(NULL);
// 	if (realloc(NULL, 0) == NULL)
// 		print("Bonjour\n");
// 	return 0;
// }

// int	main()
// {
// 	ft_putstr("Malloc...\n");
// 	malloc(0);
// 	ft_putstr("Free...\n");
// 	free(NULL);
// 	ft_putstr("Realloc...\n");
// 	realloc(NULL, 0);
// 	ft_putstr("Show alloc mem...\n");
// 	show_alloc_mem();
// 	printf("Page Size: %d", getpagesize());
// 	return 0;
// }
