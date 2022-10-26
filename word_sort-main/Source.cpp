#define SIZE 100
#define OUT 0
#define IN 1

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


void swap(char frst[], char snd[], int size);
bool is_uppercase(char character);
int word_number(char* string, int length);
bool string_compare(char string_first[], char string_second[]);
void string_cut(char string_to_cut[], char string_array[SIZE][SIZE]);


int main()
{
	char string_to_sort[SIZE] = "My house is so beautiful. I can look at it all day round.";
	char words[SIZE][SIZE];
	int c, n, d;
	n = word_number(string_to_sort, SIZE);

	string_cut(string_to_sort, words);
	
	cout << "Not sorted: " << string_to_sort << endl;
	// bubble_sort
	for (c = 0; c < n - 1; c++)
	{
		for (d = 0; d < n - c - 1; d++)
		{
			if (string_compare(words[d], words[d + 1]) == true) /* For decreasing order use '<' instead of '>' */
			{
				swap(words[d], words[d + 1]);
			}
		}
	}
	cout << "Sorted: ";
	for (int i = 0; i < n; i++)
	{
		cout << words[i] << " ";
	}
	cout << endl;

	return 0;
}
// milk\0
// strawberry\0

void swap(char frst[], char snd[])
{
	int size_1 = strlen(frst);
	int size_2 = strlen(snd);
	int limit = (size_1 > size_2 ? size_1 : size_2);
	char temp;

	for (int i = 0; i <= limit; i++)
	{
		temp = frst[i];
		frst[i] = snd[i];
		snd[i] = temp;
	}
}


void string_cut(char string_to_cut[], char string_array[SIZE][SIZE])
{	
	// indicates number of word in string_array and at the same time shows us amount of words in string_array
	int word_index = 0;	
	// indicates number of letter in the specific word that will be placed in the array of the string_array
	int letter_index = 0;
	int state = OUT;

	// I love milk.
	for (int i = 0; string_to_cut[i] != '\0'; i++) {
		char c = string_to_cut[i];
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;

			int j = i;
			while (string_to_cut[j] != ' ' && string_to_cut[j] != '\n' && string_to_cut[j] != '\t' && string_to_cut[j] != '\0')
			{
				string_array[word_index][letter_index] = string_to_cut[j];
				letter_index++; j++;
			}
			string_array[word_index][letter_index] = '\0';
			word_index++;
			letter_index = 0;
		}
	}
}

// aaaa a ab
//const char* find_min_word(char string[])
//{
//	;
//}


bool string_compare(char string_first[], char string_second[])
{
	// Function takes two string, then compare it by ASCII code.
	// If the first letters are the same, then compare next letters.
	// Function return true or false as a allowance to swap elements
	// Some cases:
	// aaa < aaaav
	// aaa > aa
	// vaaaaaa < z
	// Aaa < aaa, but Caaa > baaa. Right: AaBbCc

	int size_1 = strlen(string_first);
	int size_2 = strlen(string_second);
	int limit = (size_1 > size_2 ? size_2 : size_1);
	int frst, snd;
	int difference = 32;
	// a-A=32
	// If the letter is upper we will add 32 to his ascii, in other words
	// we will treat the uppercase like a lowercase. That's it...
	for (int i = 0; i < limit; i++) {
		frst = string_first[i];
		snd = string_second[i];
		if (is_uppercase(string_first[i])) {
			frst += difference;
		} else if (is_uppercase(string_second[i])) {
			snd += difference;
		}

		if (frst > snd) { return true; }
		else if (frst == snd) { continue; }
		else { return false; }
	}
	
	if (size_1 > size_2) { return true; }
	else { return false; }
}

int word_number(char* string, int length)
{
	int word_counter = 0;
	int state = OUT;

	// 0 1 2 3 4  5  6 => length = 6 (+\n)
	// h e l l o \n \0

	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == ' ' || string[i] == '\n' || string[i] == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			word_counter++;
		}
	}
	return word_counter;
}


bool is_uppercase(char character) 
{
	if (character >= 'A' && character <= 'Z') { return true; }
	else { return false; }
}