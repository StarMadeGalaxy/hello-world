void hex_to_bin(char* hex_array, char* bin_array)
{
	
	int hex_index;		// index of each element in hex_array
	
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
}
