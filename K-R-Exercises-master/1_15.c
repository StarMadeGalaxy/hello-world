#include <stdio.h>

int main(void)
{
	int step, lower, upper;

	lower = 0;
	upper = 300;
	step = 20;

	while (lower <= upper)
	{
		printf("Fharenheit: %d | Celsiuc: %d\n", lower, fahr_to_cels(lower));
		lower += step;
	}

	return 0;
}


int fahr_to_cels(int fahr)
{
	return 5 * (fahr - 32) / 9;
}