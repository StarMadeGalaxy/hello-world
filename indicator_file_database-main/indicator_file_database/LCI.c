#pragma once

#include "LCI.h"
#include "iotools.h"


void lci_menu(void)
{
	puts("-----------------------Меню-----------------------\n");
	puts("1. Создание справочника в памяти");
	puts("2. Вывод справочника на экран");
	puts("3. Добавление данных в конец справочника");
	puts("4. Удаление данных из конца справочника");
	puts("5. Корректировка данных с указанным номером");
	puts("6. Поиск данных по определенному числовому полю");
	puts("7. Сохранение изменений/справочника в файл");
	puts("8. Открытие справочника из файла");
	puts("9. Сортировка методом пузырька по текстовому полю,");
	puts("   сортировка методом выбора по числовому полю");
	puts("10. Выход из программы");
	puts("-----------------------Меню-----------------------");
}


void lci_find(LCI* indicators, const size_t amount)
{
	if (amount <= 0)
	{
		puts("\nСправочник пуст.");
		return;
	}
	if (indicators == NULL)
	{
		puts("\nСправочник равен NULL");
		return;
	}

	char input[MAX];

	puts("\nВыберите поле по поиска которому производить поиск\n");
	puts("1. Объем резервуара");
	puts("2. Температура");
	puts("3. Продолжительность жизни");
	puts("4. Название");
	printf("\nВведите значение: ");

	getline(input);
	size_t menu_choice = (size_t)string_to_int(input);

	if (menu_choice < 1 || menu_choice > 4)
	{
		puts("\nНекоррекнтое значение. Попробуйте заново.");
		return;
	}

	char new_value[MAX];
	printf("\nВведите значение для поиска: ");
	getline(new_value);

	short is_found = 0;

	switch (string_to_int(input))
	{
	case RESERVOIR:
		if (if_int_string(new_value) == 1)
		{
			double reservoir = (double)string_to_int(new_value);

			for (size_t i = 0; i < amount; i++)
			{
				if (indicators[i].reservoir == reservoir)
				{
					printf("\n#%zu с объемом: %lf", i, reservoir);
					lci_info(&indicators[i]);
					is_found = 1;
				}
			}
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case TEMPERATURE:
		if (if_int_string(new_value) == 1)
		{
			double temperature = (double)string_to_int(new_value);

			for (size_t i = 0; i < amount; i++)
			{
				if (indicators[i].temperature == temperature)
				{
					printf("\n#%zu с температурой: %lf", i, temperature);
					lci_info(&indicators[i]);
					is_found = 1;
				}
			}
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case LIFESPAN:
		if (if_int_string(new_value) == 1)
		{
			double lifespan = (double)string_to_int(new_value);

			for (size_t i = 0; i < amount; i++)
			{
				if (indicators[i].lifespan == lifespan)
				{
					printf("\n#%zu с продолжительностью жизни: %lf", i, lifespan);
					lci_info(&indicators[i]);
					is_found = 1;
				}
			}
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case INDICATOR:
		for (size_t i = 0; i < amount; i++)
		{
			if (string_equality(indicators[i].indicator, new_value) == 1)
			{
				printf("\n#%zu с названием: %s", i, new_value);
				lci_info(&indicators[i]);
				is_found = 1;
			}
		}

		break;
	default:
		puts("\nТакого пункта в меню нет!");
		break;
	}
	if (is_found == 0)
		puts("\nНичего не найдено.");
	else
		puts("\nПоиск завершен успешно!");
}
	

void lci_correct(LCI* indicators, const size_t amount)
{
	if (amount <= 0)
	{
		puts("\nСписок пуст!");
		return;
	}
	if (indicators == NULL)
	{
		puts("\nСправочник равен NULL");
		return;
	}

	char input[MAX];

	printf("\nВведите номер индикатора, который хотите изменить: ");
	getline(input);
	if (if_int_string(input) == 0)
	{
		puts("\nВведено некорретное значение. Попробуйте заново.");
		return;
	}

	size_t num_to_correct = (size_t)string_to_int(input);

	if (num_to_correct >= amount)
	{
		puts("\nНомер превышает количество элементов.");
		return;
	}
	
	puts("\nВыберите поле для изменения\n");
	puts("1. Объем резервуара");
	puts("2. Температура");
	puts("3. Продолжительность жизни");
	puts("4. Название");
	printf("\nВведите значение: ");

	getline(input);
	size_t menu_choice = (size_t)string_to_int(input);
	
	if (menu_choice < 1 || menu_choice > 4)
	{
		puts("\nНекоррекнтое значение. Попробуйте заново.");
		return;
	}

	char new_value[MAX];
	printf("\nВведите новое значение: ");
	getline(new_value);

	switch (string_to_int(input))
	{
	case RESERVOIR:
		if (if_int_string(new_value) == 1)
		{
			indicators[num_to_correct].reservoir = (double)string_to_int(new_value);
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case TEMPERATURE:
		if (if_int_string(new_value) == 1)
		{
			indicators[num_to_correct].reservoir = (double)string_to_int(new_value);
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case LIFESPAN:
		if (if_int_string(new_value) == 1)
		{
			indicators[num_to_correct].reservoir = (double)string_to_int(new_value);
		}
		else {
			puts("Некорректное значение. Попробуйте заново.");
			return;
		}
		break;
	case INDICATOR:
		memcpy(indicators[num_to_correct].indicator, new_value, MAX);
		break;
	default:
		puts("\nТакого пункта в меню нет!");
		break;
	}
	puts("\nИзменение прошло успешно!");
}


void swap_lci(LCI* frst, LCI* snd)
{
	double temp = 0;

	swap_strings(frst->indicator, snd->indicator);

	temp = frst->lifespan;
	frst->lifespan = snd->lifespan;
	snd->lifespan = temp;

	temp = frst->reservoir;
	frst->reservoir = snd->reservoir;
	snd->reservoir = temp;

	temp = frst->temperature;
	frst->temperature = snd->temperature;
	snd->temperature = temp;
}


LCI* lci_file_read(FILE* fptr, const char* filename, size_t* amount)
{
	errno_t error_code;
	error_code = fopen_s(&fptr, filename, "rb");

	if (error_code != 0) {
		printf("Ошибка открытия файла '%s'.\nФайл должен существовать перед чтением.\n\n", filename);
		return 0;
	}
	else
	{
		printf("Файл '%s' открыт успешно для чтения.\n\n", filename);
	}

	size_t lci_file_amount = get_file_size(fptr, filename) / sizeof(LCI);
	LCI* indicators = (LCI*)malloc(lci_file_amount * sizeof(LCI));

	if (lci_file_amount > MAX)
	{
		puts("\nКоличество индикаторов превышает допустимый размер справочника.");
		puts("С файла будет прочтено ограниченное количество индикаторов.\n");
		lci_file_amount = MAX;
	} 
	else if (lci_file_amount <= 0)
	{
		puts("\nСписок пуст!");
		return 0;
	}

	if (indicators != NULL)
	{
		for (size_t i = 0; i < lci_file_amount; i++)
		{
			if (fread(&indicators[i], sizeof(LCI), 1, fptr) == 0)
			{
				printf("\nВо время чтения произошла ошибка.\nВероятно выход за пределы справочника\n");
				break;
			} else {
				printf("Индикатор '%s' прочитан успешно из файла '%s'.\n", indicators[i].indicator, filename);
			}
		}
	}

	fclose(fptr);
	*amount = lci_file_amount;

	return indicators;
}


void lci_file_write(FILE* fptr, const char* filename, LCI* indicators, size_t lci_num)
{
	if (lci_num <= 0)
	{
		puts("\nСписок пуст!");
		return;
	}

	errno_t error_code;

	error_code = fopen_s(&fptr, filename, "wb");

	if (error_code != 0) {
		printf("Ошибка открытия файла '%s'.\n\n", filename);
		return;
	}
	else
	{
		printf("Файл '%s' открыт успешно для записи.\n\n", filename);
	}

	for (size_t i = 0; i < lci_num; i++) 
	{
		printf("Индикатор '%s' записан успешно в файл '%s'.\n", indicators[i].indicator, filename);
		fwrite(&indicators[i], sizeof(LCI), 1, fptr);
	}
	fclose(fptr);
}


LCI* lci_delend(LCI* indicators, size_t* amount)
{
	if (amount <= 0)
	{
		puts("\nСписок пуст!");
		return indicators;
	}
	if (indicators == NULL)
	{
		puts("\nСправочник равен NULL");
		return indicators;
	}

	char input[MAX];

	printf("\nВведите количество индикаторов которое хотите удалить: ");
	getline(input);

	if (if_int_string(input) == 0)
	{
		puts("\nВведено некорретное значение. Попробуйте заново.");
		return indicators;
	}

	size_t how_much = (size_t)string_to_int(input);

	if (((signed)*amount - (signed)how_much) < 0)
	{
		puts("\nЗначение слишком велико. Попробуйте заново.");
		return indicators;
	}
	else if ((*amount - how_much) == 0)
	{
		free(indicators);
		puts("\nСправочник очищен.");
		return NULL;
	}

	LCI* temp_lci = (LCI*)realloc(indicators, sizeof(LCI) * (*amount - how_much));
	if (temp_lci != NULL)
	{
		indicators = temp_lci;
	}
	else
	{
		puts("\nОшибка реалокации при удалении.");
		return NULL;
	}
	*amount -= how_much;
	puts("\nУдаление прошло успешно!");
	return indicators;
}


LCI* lci_append(LCI* indicators, size_t* amount)
{
	char input[MAX];

	printf("\nВведите количество индикаторов которое хотите добавить: ");
	getline(input);

	if (if_int_string(input) == 0)
	{
		puts("\nВведено некорретное значение. Попробуйте заново.");
		return indicators;
	}

	size_t how_much = (size_t)string_to_int(input);

	if ((*amount + how_much) >= MAX)
	{
		puts("\nЗначение слишком велико. Попробуйте заново.");
		return indicators;
	}

	LCI* temp_lci = (LCI*)realloc(indicators, sizeof(LCI) * (*amount + how_much));
	if (temp_lci != NULL)
	{
		indicators = temp_lci;
	}
	else 
	{
		puts("\nОшибка реалокации при удалении.");
		return NULL;
	}

	for (size_t i = *amount; i < *amount + how_much; i++)
	{
		system("CLS");

		LCI indicator;

		printf("\nВведите имя название индикатора: ");
		getline(input);
		memcpy(indicator.indicator, input, MAX);

		printf("\nВведите объем резервуара: ");
		getline(input);
		indicator.reservoir = (double)string_to_int(input);

		printf("\nВведите температуру: ");
		getline(input);
		indicator.temperature = (double)string_to_int(input);

		printf("\nВведите продолжительность жизни: ");
		getline(input);
		indicator.lifespan = (double)string_to_int(input);

		indicators[i] = indicator;		// TODO: buffer overflow warning
	}
	*amount += how_much;
	puts("\nДобавление прошло успешно!");
	return indicators;
}


void lci_bubble_sort(LCI* indicators, const size_t size)
{
	for (size_t i = 0; i < size - 1; i++) {
		for (size_t j = 0; j < size - i - 1; j++) {
			if (string_compare(indicators[j].indicator, indicators[j + 1].indicator)) {
				swap_lci(&indicators[j], &indicators[j + 1]);
			}
		}
	};
}


void lci_selection_sort(LCI* indicators, const size_t size, size_t mode)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		size_t min_index = i;

		for (size_t j = i + 1; j < size; j++)
		{
			switch (mode)
			{
			case RESERVOIR:
				if (indicators[j].reservoir < indicators[min_index].reservoir)
					min_index = j;
				break;
			case TEMPERATURE:
				if (indicators[j].temperature < indicators[min_index].temperature)
					min_index = j;
				break;
			case LIFESPAN:
				if (indicators[j].lifespan < indicators[min_index].lifespan)
					min_index = j;
				break;
			default:
				break;
			}
		}
		swap_lci(&indicators[min_index], &indicators[i]);
	}
}


void sort_by_field(LCI* indicators, const size_t size)
{
	if (size <= 0 )
	{
		puts("\nСписок пуст!");
		return;
	} 
	if (indicators == NULL)
	{
		puts("\nСправочник равен NULL");
		return;
	}

	puts("Выберите поле для сортировки: \n");
	puts("1. Название");
	puts("2. Объем резервуара");
	puts("3. Температура");
	puts("4. Продолжительность жизни");
	printf("\nВведите значение: ");

	char input[MAX];
	getline(input);

	switch (string_to_int(input))
	{
	case 1:
		lci_bubble_sort(indicators, size);
		break;
	case 2:
		lci_selection_sort(indicators, size, RESERVOIR);
		break;
	case 3:
		lci_selection_sort(indicators, size, TEMPERATURE);
		break;
	case 4:
		lci_selection_sort(indicators, size, LIFESPAN);
		break;
	default:
		puts("\nТакого пункта в меню нет!");
		break;
	}
	puts("\nСортировка прошла успешно!");
}


void lci_info(LCI* indicator)
{
	printf("\nИндикатор: %s", indicator->indicator);
	printf("\nРезервуар: %lf", indicator->reservoir);
	printf("\nТемпература: %lf", indicator->temperature);
	printf("\nСрок службы: %lf\n", indicator->lifespan);
}


void lci_array_output(LCI* indicators, const size_t size)
{
	if (size <= 0) 
	{
		puts("\nСправочник пуст.");
		return;
	}
	if (indicators == NULL)
	{
		puts("\nСправочник равен NULL");
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		printf("\n#%zu", i);
		lci_info(&indicators[i]);
	}
}


LCI* create_lci_array(LCI* indicators, size_t* amount)
{
	if (indicators != NULL)
	{
		puts("\nСправочник уже был создан. Для добавления используйте добавление в конец.\n");
		return indicators;
	}
	char input[MAX];

	printf("\nВведите количество индикаторов которое хотите добавить: ");
	getline(input);
	if (if_int_string(input) == 0)
	{
		puts("\nВведено некорретное значение. Попробуйте заново.");
		return NULL;
	}
	size_t size = (size_t)string_to_int(input);
	*amount += size;
	indicators = (LCI*)malloc(*amount * sizeof(LCI));

	if (indicators)		// если хватило памяти
	{
		for (size_t i = 0; i < size; i++)
		{
			system("CLS");

			LCI indicator;

			printf("\nВведите имя название индикатора: ");
			getline(input);
			memcpy(indicator.indicator, input, MAX);

			printf("\nВведите объем резервуара: ");
			getline(input);
			indicator.reservoir = (double)string_to_int(input);

			printf("\nВведите температуру: ");
			getline(input);
			indicator.temperature = (double)string_to_int(input);

			printf("\nВведите продолжительность жизни: ");
			getline(input);
			indicator.lifespan = (double)string_to_int(input);

			indicators[i] = indicator;		// TODO: buffer overflow warning
		}
		else {
			perror("\nОшибка выделения памяти: ");
			*amount = 0;
			return NULL;
		}
	}

	puts("\nСоздание завершено!");
	return indicators;
}


