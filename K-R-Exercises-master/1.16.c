#include <stdio.h>
#define MAXLINE 10

int get_length(char[], int);
void copy(char[], char[]);


int main(void)
{
	int current_len;
	int max_len;

	char current_string[MAXLINE];
	char longest_string[MAXLINE];
	char c;

	max_len = 0;

	while ((current_len = get_length(current_string, MAXLINE)) > 0)		// While string exists and legnth more than 0
	{
		// Check the last element if its a newline then we got a full line
		// else we store to the current_string part of the line as far as size allows
		// and remaining characters wont store to the current_string, but they are going to
		// next loop that just increase current_len while not meet EOF or newline.
		// In *|if (current_string[current_len - 1] != '\n')|* last character with index (current_len - 1) because
		// get_length return length without null-terminator. For example: {'1','2','\0'} will be 2.
		if (current_string[current_len - 1] != '\n')		
		{
			while ((c = getchar()) != EOF && c != '\n')
			{
				++current_len;
			}
		}

		if (current_len > max_len)
		{
			max_len = current_len;
			copy(longest_string, current_string);
		}

	}
	if (max_len > 0)
	{
		printf("%d, %s", max_len, longest_string);
	}


	return 0;
}


int get_length(char string[], int limit)
{
	int c, len;

	len = 0;

	for (len = 0; (c = getchar()) != EOF && len < limit - 1 && c != '\n'; ++len)
	{
		string[len] = c;
	}
	if (c == '\n')
	{
		string[len] = c;
		++len;
	}
	
	string[len] = '\0';
	return len;
}

void copy(char to[], char from[])
{
	int i;

	i = 0;

	while ((to[i] = from[i]) != '\0')
	{
		++i;
	}
}

