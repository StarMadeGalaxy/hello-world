#pragma once

#include "stdafx.h"
#include "LCI.h"

size_t string_compare(char string_first[], char string_second[]);
int string_equality(const char* first, const char* second);
size_t get_file_size(FILE* Stream, const char* file_name);
void swap_strings(char frst[], char snd[]);
size_t is_uppercase(char character);
void swap_lci(LCI* frst, LCI* snd);
void string_output(char* string);
int string_to_int(char string[]);
int if_int_string(char string[]);
void getline(char string[]);
void wait_to_press();