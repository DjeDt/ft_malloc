/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:58:40 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 17:18:58 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "debug.h"
#include "libft.h"
#include "printf.h"
#include <sys/wait.h>

void	small_test(void)
{
	int		len;
	char	*little;
	char	*little2;
	char	*little3;
	char	*little4;
	char	*little5;

	len = 10;
	little = malloc(len);
	memset(little, 'a', len);

	little2 = malloc(20);
	memset(little2, 'b', 60);

	little3 = malloc(30);
	memset(little3, 'c', 70);

	free(little);
	free(little2);
	little4 = malloc(40);
	little5 = malloc(50);
	free(little4);
	little4 = malloc(60);
	little = malloc(25);
	free(little);
}

void	medium_test(void)
{
	char	*medium1;
	char	*medium2;
	char	*medium3;
	char	*medium4;
	char	*medium5;
	char	*medium6;
	char	*medium7;
	char	*medium8;

	ft_putendl("[main1] malloc");
	medium1 = malloc(200);
	ft_putendl("[main2] malloc");
	medium2 = malloc(250);
	ft_putendl("[main3] malloc");
	medium3 = malloc(300);
	ft_putendl("[main4] malloc");
	medium4 = malloc(350);
	ft_putendl("[main5] malloc");
	medium5 = malloc(400);

	ft_putendl("[main6] free");
	free(medium3);
	ft_putendl("[main7] free");
	free(medium4);

	ft_putendl("[main8] malloc");
	medium6 = malloc(450);
	ft_putendl("[main9] malloc");
	medium7 = malloc(500);
	ft_putendl("[main10] malloc");
	medium8 = malloc(550);
	ft_putendl("[main11] malloc");
	medium3 = malloc(225);
	ft_putendl("[main12] malloc");
	medium4 = malloc(325);
	ft_putendl("[main13] malloc");
}

void	large_test(void)
{
	char	*large1;
	char	*large2;
	char	*large3;
	char	*large4;
	char	*large5;

	ft_putendl("[main] malloc 1");
	large1 = malloc(2048);
	large2 = malloc(2048 * 2);
	large3 = malloc(2048 * 3);
	large4 = malloc(2048 * 4);
	large5 = malloc(2048 * 5);

	ft_putendl("[main] free large 2");
	free(large4);
	free(large3);
	ft_putendl("[main] malloc large 3");
	char *large6 = malloc(2048 * 7);
	char *large7 = malloc(2048 * 8);
	large3 = malloc(2048 * 300);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	free(large3);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	free(large3);
	large3 = malloc(2048 * 300);
	large3 = malloc(2048 * 300);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	large3 = malloc(2048 * 300);
	free(large3);
	large3 = malloc(2048 * 300);
	large4 = malloc(2048 * 4);
}

void	mixed_test(void)
{
	large_test();
	medium_test();
	small_test();
}

void	realloc_test(void)
{
	char	*ptr;

	ptr = malloc(10);
	memset(ptr, 'a', 10);
	ptr = realloc(ptr, 50);
	ft_putendl(ptr);

	size_t count;

	count = 0;
	int count2 = 10;
	while (++count < 500)
	{
		printf("[%zu] eme appel\n", count);
		(void)realloc(ptr, count2);
		count2++;
		if (count2 >= 600)
			count2 = 10;
	}
}

void	test(void)
{
	size_t count;
	char	*test;
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;


	count = 0;
	while (count++ < 10)
	{
		printf("[%zu] eme appel\n", count);
		ptr1 = malloc(20);
		ptr2 = malloc(80);
		ptr3 = malloc(130);
		free(ptr3);
	}
	free(ptr1);
	free(ptr2);
	free(ptr3);
	ptr3 = malloc(130);
	free(ptr3);
}

int		function_th(void)
{
	int count = 0;
	while (1)
	{
		count += rand() % 10;
		ft_putnbr(count);
		ft_putchar('\n');
		if (count > 20)
		{
			ft_putendl("depass 20");
			sleep(1);
		}
		return (0);
	}
}

void	test_thread(void)
{
	int count = 0;
	pthread_t th;
//	pthread_create (&monThreadCompteur, NULL, threadCompteur, (void*)NULL);
	while (count < 5)
	{
		pthread_create(&th, NULL, (void*)&function_th, &th);
		count++;
	}
	pthread_exit(&th);
}

void	corr_test_1(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
}

void	corr_test_2(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
}


void	test_calloc(int count)
{
	int i, n;
	int *a;
	n = count;

	a = (int*)calloc(n, sizeof(int));

	i = 0;
	while (i < n)
	{
		a[i] = i;
		i++;
	}
	for (i = 0 ; i < n ; i++)
	{
		ft_putstr("numbers are : ");
		ft_putnbr(a[i]);
		ft_putchar('\n');
	}
	free(a);
}


#define M (1024 * 1024)
void print(char *s)
{
write(1, s, strlen(s));
}

void	test3()
{
	char *addr1;
	char *addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
}

void	test3_2()
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char*)malloc(16*M);
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
}

void	test4()
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
}

void	test5()
{
	void *test;

	test = malloc(1024);
	test = malloc(1024 * 32);
	test = malloc(1024 * 1024);
	test = malloc(1024 * 1024 * 16);
	test = malloc(1024 * 1024 * 128);
	show_alloc_mem();
}

void	test_corrupt_metadata()
{
	ft_putendl("test_corrupt_metada :");
	void *ptr = malloc(22);
	memset(ptr, 'a', 22);
	ft_putendl(ptr);
	bzero((unsigned char*)ptr - AREA_SIZE, 22);
	ptr = realloc(ptr, 50);
	ft_putendl(ptr);
}

void *thread_malloc()
{
	void *ptr = malloc(4);
	strcpy(ptr, "small 1");
	void *ptr2 = malloc(800);
	strcpy(ptr2, "medium 1");
	ptr = realloc(ptr, 40);
	strcpy(ptr, "realloc small");
	free(ptr2);
	void *ptr3 = malloc(2000);
	strcpy(ptr3, "large malloc");
	void *ptr4 = calloc(80, 10);
	void *ptr5 = malloc(1000);
	strcpy(ptr4, "medium calloc");
	return (ptr);
}

void	test_thread2()
{
	int limit = 5;
	int i;
	pthread_t th[limit];

    for (i = 0; i < limit; i++)
		pthread_create(&th[i], NULL, &thread_malloc, NULL);
}

int		main(int ac, char **av, char **env)
{
/* 	int count = 0; */
/* 	char *str; */

/* 	while (count < 50) */
/* 	{ */
/* 		str = malloc(count + 1); */
/* //		str = malloc(count + 1024); */
/* //		free(str); */
/* 		count++; */
/* 	} */
/* 	large_test(); */
/* 	large_test(); */
/* 	large_test(); */
/* 	large_test(); */
/* 	large_test(); */
/* 	mixed_test(); */
/* 	realloc_test(); */

/* 	show_alloc_mem(); */

	/* ft_putendl("test 3 :"); */
	/* test3(); */
	/* ft_putendl("test3-2 :"); */
	/* test3_2(); */
	/* ft_putendl("test 4 :"); */
	/* test4(); */
	/* ft_putendl("test 5 :"); */
	/* test5(); */
	/*
	small_test();
	malloc(4);
	medium_test();
	test();
	*/

//	char *ptr = malloc(56);
//	ptr = malloc(55);
//	ptr = malloc(65);
//	ptr = malloc(555);
//	ptr = malloc(655);
//	ptr = malloc(5555);
//	ptr = malloc(6555);


//	test_thread();
//	test_calloc(10);
	/*
	corr_test_1();
	corr_test_2();
	*/
//	test_corrupt_metadata();

	//test_thread2();
	int sldf = 0;
	while (sldf++ < 500)
	{
		ft_putnbr(sldf);
		ft_putstr(" . ");
		test_thread2();
	}

//	sleep(1);
//	show_alloc_mem();
	return (0);
}
