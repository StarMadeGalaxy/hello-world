#pragma once

#include "iotools.h"


void wait_to_press()
{
	printf("\n\nНажмите Enter чтобы продолжить...");
	char nothing = _getch();
}


void string_output(char* string)
{
	size_t counter = 0;

	while (string[counter] != '\0')
	{
		printf("%c", string[counter]);
		counter++;
	}
}


size_t is_uppercase(char character)
{
	if (character >= 'A' && character <= 'Z')
		return 1;
	else
		return 0;
}


void swap_strings(char frst[], char snd[])
{
	size_t size_1 = strlen(frst);
	size_t size_2 = strlen(snd);
	size_t limit = (size_1 > size_2 ? size_1 : size_2);

	for (size_t i = 0; i <= limit; i++)
	{
		char temp = frst[i];
		frst[i] = snd[i];
		snd[i] = temp;
	}
}


size_t string_compare(char string_first[], char string_second[])
{
	// Function takes two string, then compare it by ASCII code.
	// If the first letters are the same, then compare next letters.
	// Function return true or false as a allowance to swap elements
	// Some cases:
	// aaa < aaaav
	// aaa > aa
	// vaaaaaa < z
	// Aaa < aaa, but Caaa > baaa. Right: AaBbCc

	size_t size_1 = strlen(string_first);
	size_t size_2 = strlen(string_second);
	size_t limit = (size_1 > size_2 ? size_2 : size_1);
	size_t frst, snd = 0;
	size_t difference = 32;

	// a-A=32
	// If the letter is upper we will add 32 to his ascii, in other words
	// we will treat the uppercase like a lowercase. That's it...

	for (size_t i = 0; i < limit; i++) {
		frst = string_first[i];
		snd = string_second[i];

		if (is_uppercase(string_first[i]))
			frst += difference;
		if (is_uppercase(string_second[i]))
			snd += difference;

		if (frst > snd)
			return 1;
		else if (frst == snd)
			continue;
		else
			return 0;
	}

	if (size_1 > size_2)
		return 1;
	else
		return 0;
}


int string_equality(const char* first, const char* second)
{
	size_t max_length = 0;

	size_t first_length = strlen(first);
	size_t second_length = strlen(second);

	if (first_length != second_length)
		return 0;

	if (first_length > second_length)
		max_length = first_length;
	else
		max_length = second_length;

	for (int i = 0; i < max_length; i++)
	{
		if (first[i] != second[i])
			return 0;
	}
	return 1;
}


size_t get_file_size(FILE* Stream, const char* file_name)
{
	size_t previous_offset = ftell(Stream);
	fseek(Stream, 0, SEEK_END);
	size_t file_size = ftell(Stream);
	fseek(Stream, (long)previous_offset, SEEK_SET);
	return file_size;
}


void getline(char string[])		// without \n
{
	int i, c;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
	{
		string[i] = c;
	}
	string[i] = '\0';
}


int string_to_int(char string[])
{
	if (strlen(string) == 0)
	{
		return 0;
	}

	int number_to_return = 0;

	for (int i = 0; i < strlen(string) && string[i] != '\0'; i++)
	{
		number_to_return *= 10;
		number_to_return += string[i] - 48;
	}

	return number_to_return;
}


int if_int_string(char string[])
{
	for (size_t i = 0; i < strlen(string) && string[i] != '\0'; i++)
	{
		if (string[i] < '0' || string[i] > '9')
			return 0;
	}
	return 1;
}