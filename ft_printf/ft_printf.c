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

	int mine, real;

	mine = ft_printf ("mine = Test INT_MIN : %d | Test INT_MAX : %d \n",
						2147483647, -2147483648);
	real = printf ("real = Test INT_MIN : %d | Test INT_MAX : %ld \n",
						2147483647, -2147483648);
	printf ("mine = %d & real = %d\n\n", mine, real);

	mine = ft_printf ("real = Test INT : %d | Test INT : %d | test str = %s | test hexadecimale = %x\n",
						900001, -900001, "Hello World !", 2147483647);
	real = printf ("real = Test INT : %d | Test INT : %d | test str = %s | test hexadecimale = %x\n",
						900001, -900001, "Hello World !", 2147483647);
	printf ("mine = %d & real = %d", mine, real);

    return 0;
}