#include "stdafx.h"
#include "LCI.h"
#include "iotools.h"


int main()
{
	system("chcp 1251>nul");

	FILE* pDataFile = NULL;
	const char* data_file = "lci_data.dat";

	LCI* indicators = NULL;
	size_t indicators_amount = 0;

	while (1)
	{
		system("CLS");

		lci_menu();

		printf("\nВыберите пункт меню: ");
		char choice[MAX];

		getline(choice);

		if (string_equality(choice, "1") == 1)
		{
			system("CLS");
			indicators = create_lci_array(indicators, &indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "2") == 1)
		{
			system("CLS");
			lci_array_output(indicators, indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "3") == 1)
		{
			system("CLS");
			indicators = lci_append(indicators, &indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "4") == 1)
		{
			system("CLS");
			indicators = lci_delend(indicators, &indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "5") == 1)			
		{
			system("CLS");
			lci_correct(indicators, indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "6") == 1)
		{
			system("CLS");
			lci_find(indicators, indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "7") == 1)
		{
			system("CLS");
			lci_file_write(pDataFile, data_file, indicators, indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "8") == 1)
		{
			system("CLS");
			indicators = lci_file_read(pDataFile, data_file, &indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "9") == 1)
		{
			system("CLS");
			sort_by_field(indicators, indicators_amount);
			wait_to_press();
		}
		else if (string_equality(choice, "10") == 1)
		{
			system("CLS");
			printf("\nПрограмма завершена корректно.\n");
			return EXIT_SUCCESS;
		}
		else 
		{
			if (indicators != NULL)
				free(indicators);
			printf("\nТакого пункта в меню нет!\n");
		}
	}

	return EXIT_SUCCESS;
}

