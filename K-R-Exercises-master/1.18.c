#include <stdio.h>
#include <string.h>		// just for testing

#define SIZE 1000

int get_length(char[], int);
void tail_garbage(char[], int);

int main(void)
{
	char current_string[SIZE];
	int current_length;

	while ((current_length = get_length(current_string, SIZE)) > 0)
	{
		if (current_length > 1)  // empty line consists of \n and \0, therefore length is 1. And we dont output it
		{
			tail_garbage(current_string, current_length);
			if (current_string[0] != '\n')
			{
				printf("Length before cleaning: %d\n", current_length);
				printf("Length after cleaning: %d\n", strlen(current_string));
				printf("%s\n", current_string);
			}
			else if (current_string[0] == '\n')
			{
				printf("EMPTY LINE\n");
			}
		}
		else if (current_length <= 1)
		{
			printf("EMPTY LINE\n");
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


void tail_garbage(char string[], int string_length)
{
	int i;

	i = string_length - 2;  // -2 due to the NULL - terminator and \0

	while ((string[i] == ' ') || (string[i] == '\t'))
	{
		string[i] = '\0';
		--i;
	}
	string[++i] = '\n';	// while loop going back throughout the string it skips \n and we gonna append it to the end of the line before	null-terminator
}

