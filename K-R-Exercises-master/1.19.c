#include <stdio.h>
#define MAXLENGTH 10

void reverse(char[]);
int length(char[]);
int getline(char[], int);

int main(void)
{
	int len;
	char string_to_reverse[MAXLENGTH];

	while ((len = getline(string_to_reverse, MAXLENGTH)) > 0)
	{
		reverse(string_to_reverse);
		printf("%s\n", string_to_reverse);
	}
	return 0;
}


void reverse(char string[])
{
	int start, end;
	char buffer;

	for (start = 0, end = length(string) - 1; start < end; ++start, --end)
	{
		buffer = string[start];
		string[start] = string[end];
		string[end] = buffer;
	}
}


int getline(char string[], int string_length)
{
	int i, c;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
	{
		string[i] = c;
	}
	if (c == '\n')
	{
		string[i] = c;
		++i;
	}
	string[i] = '\0';

	return i;
}

int length(char string[])
{
	int i;

	i = 0;

	while (string[i] != '\0')
	{
		++i;
	}
	return i;
}


