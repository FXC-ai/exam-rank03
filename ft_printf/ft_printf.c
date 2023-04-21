#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define BASE_HEX "0123456789abcdef"

void count_putchar(char c, int *count)
{
	write (1,&c,1);
	(*count)++;
}

void ft_putstr(char *str, int *count)
{
	while (*str)
	{
		count_putchar(*str, count);
		str++;
	}
}

void ft_putnbr_dep(int nbr, int *count)
{
	int n;
	int divider;
	int cpy_nbr;

	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}

	if (nbr < 0)
	{
		count_putchar('-', count);
		nbr *= -1;
	}

	divider = 1;
	cpy_nbr = nbr;
	while (cpy_nbr > 10)
	{
		cpy_nbr = cpy_nbr / 10;
		divider = divider * 10;
	}

	while (nbr > 0)
	{
		n = (nbr / divider) + 48;
		count_putchar(n, count);
		nbr = nbr % divider;
		divider /= 10;
	}
}

void ft_putnbr(int nbr, int *count)
{
	int n = 0;

	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", count);
	}
	else if (nbr < 0)
	{
		count_putchar('-', count);
		ft_putnbr(-nbr, count);
	}
	else if (nbr > 0)
	{
		n = nbr % 10;
		nbr = nbr / 10;
		ft_putnbr(nbr, count);
		count_putchar(n + 48, count);
	}

}

void ft_putnbr_hex (int nbr, int *count)
{
	int n = 0;

	if (nbr > 0)
	{	
		n = nbr % 16;
		nbr = nbr / 16;
		ft_putnbr_hex(nbr, count);
		count_putchar(BASE_HEX[n], count);
	}
}


int ft_printf(const char *str, ...)
{
	va_list ap, ap2;
	int d;
	int tmp;
	char *s;
	int count;

	count = 0;
	va_start(ap, str);
	va_copy(ap2, ap);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			switch(*str) 
			{
				case 's':                       
					s = va_arg(ap, char *);
					ft_putstr(s, &count);
					break;
				case 'd':                       
					d = va_arg(ap, int);
					ft_putnbr(d, &count);
					break;
				case 'x':
					d = va_arg(ap, int);
					ft_putnbr_hex(d, &count);
					break;
			}
		}
		else
			count_putchar(*str, &count);
		str++;
	}
	va_end(ap);	
	va_end(ap2);

	return count;
}

int main (void)
{
    //ft_printf("Voici les tests : %c %d %s\n", 'c', 42, "hello");

	//ft_putstr("Bonjour voici le test\n");

	int test = 2147483647;
	int test2 = -2147483648;
	int real, mine;

	//char *str_test;

	real =    printf("%s\n", "Pourquoi");
	mine = ft_printf("%s\n", "Pourquoi");
	printf("real = %d | mine = %d\n", real, mine);

	real =    printf("%d\n", test2);
	mine = ft_printf("%d\n", test2);
	printf("real = %d | mine = %d\n", real, mine);


	real =    printf("%d\n", test);
	mine = ft_printf("%d\n", test);
	printf("real = %d | mine = %d\n", real, mine);


	real =    printf("%x\n", 9016);
	mine = ft_printf("%x\n", 9016);
	printf("real = %d | mine = %d\n", real, mine);

	int count;
	count = 0;
	ft_putnbr(-2147483648, &count);


	//printf("\n");


    return 0;
}