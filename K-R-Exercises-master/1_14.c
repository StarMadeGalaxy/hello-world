#include <stdio.h>
#define MAX_ASCII 255

int main(void)
{
	int c, i, s;
	int ascii[MAX_ASCII];

	for (i = 0; i < MAX_ASCII; ++i)
	{
		ascii[i] = 0;
	}

	while ((c = getchar()) != EOF)
	{
		++ascii[c];
	}

	for (i = 0; i < MAX_ASCII; ++i)
	{
		putchar(i);
		printf("   :   ");
		for (s = 0; s < ascii[i]; ++s)
		{
			putchar('*'); 
		}
		putchar('\n');
	}

	return 0;
}