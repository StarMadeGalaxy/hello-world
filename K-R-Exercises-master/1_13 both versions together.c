#include <stdio.h>
#define IN 1
#define OUT 0
#define AMOUNT 10
#define ZERO 0
#define FRST_COL_WIDE 16  // Wide of the first column in table for 1 digit size indexes in array


int main(void)
{
	int c, i, s;					// stream and indexes
	int length, state;			// length of the input word and entering word state
	int	bar_chart[AMOUNT];		// index - amount of letter in word, element - amount of words with letters 
	int many;

	many = max_element(bar_chart);
	state = OUT;
	length = ZERO;

	for (i = ZERO; i < AMOUNT; ++i)
	{
		bar_chart[i] = ZERO;
	}


	while ((c = getchar()) != EOF)
	{
		if (c != ' ' && c != '\t' && c != '\n')
		{
			state = IN;
			++length;
		}
		else if (state == IN)
		{
			state = OUT;
			if (length >= AMOUNT)		// index 0 used for words whose length more than max index of array
			{
				++bar_chart[ZERO];
				length = ZERO;
			}
			else
			{
				++bar_chart[length];
				length = ZERO;
			}
		}
	}

	putchar('\n');
	printf("************************************************************\n");
	printf("                      VERTICAL VERSION                      \n");
	printf("************************************************************\n");
	putchar('\n');


	printf("  ");
	for (i = ZERO; i < 10; ++i)
	{
		printf(" %d", i);
	}
	putchar('\n');

	for (i = ZERO; i < max_element(bar_chart); ++i)
	{
		if (i < 9)
		{
			printf("%d ", i + 1);
		}
		else
		{ 
			printf("%d", i + 1);
		}
			
		for (s = ZERO; s < AMOUNT; ++s)
		{
			if (bar_chart[s] > i)
			{
				printf(" *");
			}
			else if (bar_chart[s] <= i)
			{
				printf("  ");
			}
		}
		putchar('\n');
	}
	
	putchar('\n');
	printf("************************************************************\n");
	printf("                    HORIZONTAL VERSION                      \n");
	printf("************************************************************\n");
	putchar('\n');

	printf("| Letters num |");

	for (i = 0; i < max_element(bar_chart); ++i)
	{
		if (i >= 10)
		{
			printf("%d|", i + 1);
		}
		else
		{
			printf(" %d|", i + 1);
		}
	}
	putchar('\n');

	for (i = ZERO; i < (FRST_COL_WIDE + max_element(bar_chart)); ++i)
	{
		if (i == ZERO)
		{
			putchar('|');
		}
		else if (i < (FRST_COL_WIDE - 2) && i != ZERO && i != (FRST_COL_WIDE - 2))
		{
			putchar('_');
		}
		else if (i == (FRST_COL_WIDE - 2))		// -2 due to specification of the first column
		{
			putchar('|');
		}
		else if (i >(FRST_COL_WIDE - 2) && i < (FRST_COL_WIDE + max_element(bar_chart)) - 1)
		{
			printf("  |");
		}
	}
	putchar('\n');


	for (i = ZERO; i < AMOUNT; ++i)
	{
		printf("|______%d______|", i);
		for (s = ZERO; s < max_element(bar_chart); ++s)
		{
			if (s < bar_chart[i])
			{
				printf(" *|");
			}
			else
			{
				printf("  |");
			}
		}
		putchar('\n');
	}


	return 0;
}


int max_element(int array[AMOUNT])		// find the max array element 
{
	int i, max;

	max = array[0];

	for (i = ZERO; i < AMOUNT; ++i)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
		else
		{
			;
		}
	}
	return max;
} 