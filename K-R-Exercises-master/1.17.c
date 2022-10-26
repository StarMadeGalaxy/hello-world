#include <stdio.h>
#define SIZE 1000

int get_length(char[], int);

int main(void)
{
	char current_string[SIZE];
	int current_length;

	while ((current_length = get_length(current_string, SIZE)) > 0)
	{
		printf("Length: %d\n", current_length);
		if (current_length > 80)
		{
			printf("\n%s", current_string);
		}
	}
	return 0;
}


int get_length(char s[], int limit)
{
	int c, i;

	for (i = 0; (c = getchar()) != EOF && c != '\n' && i < limit - 1; ++i)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';  
	return i;
}