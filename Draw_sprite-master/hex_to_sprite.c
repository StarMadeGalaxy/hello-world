#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 401

void hex_to_sprite(char* hex_array, char* bin_array, int width);

int main(void)
{
	char hex_sprite[MAX] = "07C0092009201110101010101FF0101010101010101010101010101010101010600C80028002800280028102410422881C70";
	// length of binary_coded_sprite must be four times more than hex
	char bin_array[MAX];
	strcpy(bin_array, "");

	int width = 16;

	hex_to_sprite(hex_sprite, bin_array, width);

	return EXIT_SUCCESS;
}

// Draws a sprite in the console using hex-coded sprite with a specific width
void hex_to_sprite(char* hex_array, char* bin_array, int width)
{
	// hex_array = array of hex-coded sprite 
	// width = width of sprite you want to draw
	// bin_array = an array, where decoded sprite will be contained in binary form
	// length of binary_coded_sprite must be four times more than hex


	int hex_index;		// index of each element in hex_arrayB
	int counter;		// total amount of pixels of the sprite 
	int line_counter;	// variable to control width of the line of the sprite 
	int index;			// index of each element in bin_array


	for (int i = 0, hex_index = 0; i < strlen(hex_array) * 4; i++, hex_index++)
	{
		switch (*(hex_array + hex_index))
		{
		case '0':
			strcat(bin_array, "0000");
			break;

		case '1':
			strcat(bin_array, "0001");
			break;

		case '2':
			strcat(bin_array, "0010");
			break;

		case '3':
			strcat(bin_array, "0011");
			break;

		case '4':
			strcat(bin_array, "0100");
			break;

		case '5':
			strcat(bin_array, "0101");
			break;

		case '6':
			strcat(bin_array, "0110");
			break;

		case '7':
			strcat(bin_array, "0111");
			break;

		case '8':
			strcat(bin_array, "1000");
			break;

		case '9':
			strcat(bin_array, "1001");
			break;

		case 'A':
			strcat(bin_array, "1010");
			break;

		case 'B':
			strcat(bin_array, "1011");
			break;

		case 'C':
			strcat(bin_array, "1100");
			break;

		case 'D':
			strcat(bin_array, "1101");
			break;

		case 'E':
			strcat(bin_array, "1110");
			break;

		case 'F':
			strcat(bin_array, "1111");
			break;

		default:
			;
			break;
		}
	}

	counter = 0;
	line_counter = 0;
	index = 0;

	while (counter < strlen(bin_array))
	{
		if (line_counter < width)
		{
			if (*(bin_array + index) == '0')
			{
				putchar('.');
			}
			else if (*(bin_array + index) == '1')
			{
				putchar('0');
			}
			index++;
			line_counter++;
			counter++;
		}
		else
		{
			putchar('\n');
			line_counter = 0;
		}
	}
}
