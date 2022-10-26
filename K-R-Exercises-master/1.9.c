#include <stdio.h>


int main(void)
{
	int input;
	int counter;

	counter = 0;


	while ((input = getchar()) != EOF)
	{
		if (input == ' ')
		{
			if (counter < 1)
			{
				++counter;
				putchar(input);
			}
			if (counter >= 1)
			{
				;
			}
		}
		if (input != ' ')
		{
			counter = 0;
			putchar(input);
		}
	}
	return 0;
}