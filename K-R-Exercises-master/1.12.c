#include <stdio.h>


int main(void)
{
	int c;
	int space_counter;

	space_counter = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\n' || c == '\t')
		{
			if (space_counter < 1)
			{
				putchar('\n');
				++space_counter;
			}
			else if (space_counter >= 1)
			{
				;
			}
		}
		else
		{
			space_counter = 0;
			putchar(c);
		}
	}
	return 0;
}