#include <stdio.h>

#define TABULATION 9
#define BACKSPACE 8
#define BACKSLASH 92

int main(void)
{
	int input;

	while ((input = getchar()) != EOF)
	{
		if (input == TABULATION)
		{
			printf("\\t");
		}
		if (input == BACKSPACE)
		{
			printf("\\b");
		}
		if (input == BACKSLASH)
		{
			printf("\\");
		}
		putchar(input);
	}
	return 0;
}