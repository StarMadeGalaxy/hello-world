#include <stdio.h>
#define IN 1
#define OUT 0
#define AMOUNT 10
#define ZERO 0



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