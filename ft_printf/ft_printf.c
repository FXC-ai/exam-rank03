#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>


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
	

	if (nbr < 0)
	{
		write(1,"-",1);
		nbr *= -1;
	}

	while (nbr > 10)
	{
		

	}


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
	
	//printf("premier   argument : %c\n", va_arg(ap2, int));
	//printf("deuxieme  argument : %d\n", va_arg(ap2, int));
	//printf("troisieme argument : %s\n", va_arg(ap2, char *));
	
	va_end(ap2);
	return size;
}

int main (void)
{
    ft_printf("Voici les tests : %c %d %s\n", 'c', 42, "hello");

	ft_putstr("Bonjour voici le test\n");

    return 0;
}