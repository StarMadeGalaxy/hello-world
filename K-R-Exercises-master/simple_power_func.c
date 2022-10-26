#include <stdio.h>

int main(void)
{
	int i, number, begree;

	number = 2;
	begree = 1;

	for (i = 0; i < 30; ++i)
	{
		printf("%d ^ %d = %d\n", number, begree, power(number, begree));
		++begree;
	}

	return 0;
}



int power(int number, int degree)
{
	int i, base;
	base = number;

	for (i = 1; i < degree; ++i)
	{
		base *= number;
	}
	return base;
}