#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define BASE_HEX "0123456789abcdef"

int ft_putstr(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		write(1,str,1);
		count++;
		str++;
	}
	return count;
}

int ft_putnbr(int nbr)
{
	int n;
	int count;
	int divider;
	int cpy_nbr;

	if (nbr == -2147483648)
	{
		write(1,"-2147483648", 11);
		count += 11;
		return count;
	}
	if (nbr < 0)
	{
		write(1,"-",1);
		count++;
		nbr *= -1;
	}

	count = 0;
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
		write (1,&n,1);
		count ++;
		nbr = nbr % divider;
		divider /= 10;
	}

	return count;
}

int ft_putnbr_hex (int nbr, int count)
{
	int n = 0;

	if (nbr == 0)
	{
		return count;
	}


	n = nbr % 16;
	nbr = nbr / 16;
	ft_putnbr_hex(nbr, count);
	write (1,&BASE_HEX[n],1);
	count++;
	
	return count;
	/*
	480 = 30 x 16 + 0
	30 = 1 x 16 + 14
	14 = 0 X 16 + 14
	*/

	/*
	26 = 16 x 1 + 10
	1 = 16 x 0 + 1
	
	*/

	//printf("nbr = %d\n", nbr);
	//count++;

	//return count;

}

int ft_printf(const char *str, ...)
{
	va_list ap, ap2;
	int d;
	char c; 
	char *s;
	int size;

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
					ft_putstr(s);
					break;
				case 'd':                       
					d = va_arg(ap, int);
					printf("int %d\n", d);
					break;
				case 'c':
					c = va_arg(ap, int);
					write (1,&c,1);
					size++;
					break;
				
			}
		}
		else
		{
			write(1,str,1);
		}
		size++;
		str++;
	}
	va_end(ap);
	
	va_end(ap2);
	return size;
}

int main (void)
{
    //ft_printf("Voici les tests : %c %d %s\n", 'c', 42, "hello");

	//ft_putstr("Bonjour voici le test\n");

	int test = 2147483646;

	printf("%d : %x\n", test, test);
	
	ft_putnbr_hex(test, 0);
	printf("\n");


    return 0;
}