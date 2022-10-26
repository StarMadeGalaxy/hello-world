#pragma once

#include "stdafx.h"


#define RESERVOIR 1
#define TEMPERATURE 2
#define LIFESPAN 3
#define INDICATOR 4


typedef struct Liquid_crystal_indicator
{
	char indicator[MAX];
	double reservoir;
	double temperature;
	double lifespan;

} LCI;


void lci_file_write(FILE* fptr, const char* filename, LCI* indicators, size_t lci_num);
void lci_selection_sort(LCI* indicators, const size_t size, size_t mode);
LCI* lci_file_read(FILE* fptr, const char* filename, size_t* amount);
void lci_array_output(LCI* indicators, const size_t size);
void lci_bubble_sort(LCI* indicators, const size_t size);
LCI* create_lci_array(LCI* indicators, size_t* amount);
void sort_by_field(LCI* indicators, const size_t size);
void lci_correct(LCI* indicators, const size_t size);
void lci_find(LCI* indicators, const size_t amount);
LCI* lci_append(LCI* indicators, size_t* amount);
LCI* lci_delend(LCI* indicators, size_t* amount);
void swap_lci(LCI* frst, LCI* snd);
void lci_info(LCI* indicator);
void lci_menu(void);