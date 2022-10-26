// 	13. ƒана строка, состо€ща€ из слов, разделенных пробелами. 
// –азбить исходную строку на две подстроки, причем перва€ длиной k символов,
// если на k-ю позицию попадает слово, то его следует отнести ко второй строке.
// «начение k вводитс€ с клавиатуры.  

#include <ilyuk_header.h>
#define MAXLENGTH 1024
#define IN 1
#define OUT 0

// enter a string and stores it to line, then line is the string
// return the size of the string
int enter_line(char line[], int size);
int word_counter(char line[]);


int main()
{
	int size;
	int k;

	char first_line[MAXLENGTH];
	char second_line[MAXLENGTH];
	char temporary_line[MAXLENGTH];

	while (true) {
		// If we enter 'milk' size is 6 because of '\0' and '\n'
		cout << "Enter the string: ";
		if ((size = enter_line(second_line, MAXLENGTH)) < 2) {	// check the size
			cout << "Size must be greater than 1.\n";
		}
		else {
			cout << "Enter k: ";
			if ((k = input_check()) >= 0 && k <= size) {
				break;
			}
			else {
				cout << "k must be positive and either equal to number of character + 1 or less.\n";
			}
		}
	}

	char c = second_line[k];
	if (c == '\n' || c == '\t' || c == '\0' || c == ' ' || k == 0) {
		cout << "First line: " << second_line << endl;
		cout << "Second line does not exists, because k point to space." << endl;
		return 0;
	}
	else {
		// finding the nearest left space in the string and get its index
		while (true) {
			// k == -1, cause if we enter for example one word, second will be without first letter, cause we're trying
			// to remove space. So not to remove the first letter we assume || k == -1
			char c = second_line[k];
			if (c == '\n' || c == '\t' || c == '\0' || c == ' ' || k == -1) {
				break;
			}
			else {
				k--;
			}
		}
	}

	// We create third string, that designed to be contain
	// entered line, without k characters in the beginning
	char third_line[MAXLENGTH];
	int third_line_index = 0;

	// n_character + 1 because counting k stopped before
	// we met space and k point to space. We must not
	// inlucde space in the second line => +1
	for (int i = k + 1; second_line[i] != '\0'; i++) {
		third_line[third_line_index++] = second_line[i];
	}
	third_line[third_line_index] = '\0';

	if (word_counter(second_line) <= 1) {
		strncpy_s(first_line, second_line, k);
		cout << "Second line: " << third_line << endl;
		cout << "First line does not exists, there's one word in the string." << endl;
		cout << "First line " << first_line << endl;
		return 0;
	}
	else {
		strncpy_s(first_line, second_line, k);
		cout << "First  line: " << first_line << endl;
		cout << "Second line: " << third_line << endl;
	}

	return 0;
}


int word_counter(char line[])
{
	int words_amount = 0;
	int index = 0;
	int state = OUT;

	while ((line[index] != '\0') && (line[index] != EOF) && (index != MAXLENGTH - 1)) {
		char c = line[index];
		index++;
		if (c == '\t' || c == ' ' || c == '\n') {
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			words_amount++;
		}
	}

	return words_amount;
}


int enter_line(char line[], int max_string_length)
{
	int i, character;

	// put the NULL-terminator at the end of the string
	// and we press enter to over entering and therefore '\n' before NULL-terminator.
	// Eventually our string will be like:
	// 0 1 2 3 4  5 
	// m i l k \n \0

	// since we met '\n' in out entered in string, when we do not intecrement i
	for (i = 0; i < max_string_length - 1 && (character = getchar()) != EOF && character != '\n'; ++i) {
		line[i] = character;
	}
	// in case of 'milk' i is equal 4 below
	if (character == '\n')
	{
		line[i] = character;
		++i;
	}
	line[i] = '\0';

	return i;
}

