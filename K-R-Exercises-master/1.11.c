#include <stdio.h>

#define IN 1	// inside the word
#define OUT 0	// outside the word

int main(void)
{
	int c;		// main stream
	int nl;		// numbers of lines
	int nw;		// numbers of words
	int nc;		// numbers of characters 
	int state;	// word entry state
	
	nl = 0;
	nw = 0;
	nc = 0;

	state = OUT;

	while ((c = getchar()) != EOF)
	{
		++nc;
		if (c == '\n')
		{
			++nl;
		}
		if (c == '\t' || c == '\n' || c == ' ')	 // if c not equal to letter 
		{										 // we aint enter the word
			state = OUT;
		}
		else if (state == OUT)
		{
			state = IN;
			++nw;
		}
	}

	printf("Word count: %d. Line count: %d. Characters: %d.\n", nw, nl, nc);

	return 0;
}