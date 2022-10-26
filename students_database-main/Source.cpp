// Copyright 2020, Slava Ilyuk, All rights reserved.

/*Text files or .txt files are a bit hard to parse in programs
and easy to read, whereas .dat is usually used to store data
that is not just plain text. Generally .txt files contains letters,
characters and symbols which is readable, .dat is binary text file
in which data is not always printable on screen.*/


#define MAX_LENGTH 224
#define ZERO 0
#define SIZEE 96
#define SUBJECTS_AMOUNT 4
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4244 )
#define BIRTH_YEAR_LIMIT 4
#define MARK_LIMIT 2
#define GROUP_LIMIT 6
#define MENU_LIMIT 1
#define UNLIMITED -1
#define STRUCT_FIELDS_AMOUNT 7 // ID and average_mark are not included, cause they cannot be changed by hand
#define DELAY 1



#include <stdio.h>
#include <iostream>
#include <math.h>
#include <io.h>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <windows.h>


using namespace std;


struct Student {
	int ID;
	char full_name[SIZEE];
	int birth_year;
	int group_number;
	int physics_mark;
	int math_mark;
	int it_mark;
	int science_mark;
	double average_mark;
};


struct Filenames {
	char output_file[MAX_PATH];
	char data_file[MAX_PATH];
	char index_file[MAX_PATH];
};


long long int number_input(int limit);
bool is_empty_file(FILE* stream);
void letter_input(char string[], int size);
void students_output(Student* student, FILE* stream);
void int_in_file(const char* filename, FILE* stream, int value);
int add_array_structure(Student structure, Student array[], int& index);
int get_current_year(void);
void print_date(void);
int set_filename_win(const char* file_format, char filename[MAX_PATH]);
int string_length(const char* string);
bool string_compare(const char* str1, const char* str2);
void hide_cursor();
void move_console_cursor(short x, short y);
void print_loading_field(int delay, int end_offset);


int main(void)
{
	system("COLOR 8b");
	hide_cursor();

	struct Student student;
	struct Filenames fname;

	// Index for each sturcture in array and at the same time amount of students stored in array
	int index;
	int menu_choice;

	FILE* DataFile, * OutputFile, * IndexFile, * MainFile;
	int struct_size = sizeof(student);
	int fstruct_size = sizeof(fname);
	int index_size = sizeof(int);

	// filenames
	const char* data_file;
	const char* output_file;
	const char* index_file;

	// This is kind of system file that's intended to store 
	// names of other files, that could be changed later
	const char* main_file = "main.dat";


	if (_access(main_file, 0) == -1) {	// access in io.h check the file for existance. code for that is 0
		cout << "\nMain file doesn't exist. File is to be created.\n";
		if ((MainFile = fopen(main_file, "wb")) == NULL) {
			cout << "An ERROR occured with '" << main_file << "'." << endl;
			return -1;
		} cout << "The file '" << main_file << "' " << "has been created successfully.\n";
		output_file = "output.txt";
		data_file = "data.dat";
		index_file = "index.dat";
		fclose(MainFile);
	}
	else {
		if ((MainFile = fopen(main_file, "rb")) == NULL) {
			cout << "An ERROR occured with '" << main_file << "'." << endl;
			return -1;
		}
		if (is_empty_file(MainFile)) {
			output_file = "output.txt";
			data_file = "data.dat";
			index_file = "index.dat";
		}
		else {
			fseek(MainFile, 0, SEEK_SET);
			if (fread(&fname, fstruct_size, 1, MainFile) == NULL) {
				cout << "An ERROR occured with '" << main_file << "'." << endl;
				return -1;
			}
			output_file = fname.output_file;
			index_file = fname.index_file;
			data_file = fname.data_file;

			cout << "\nOutput file named: '" << fname.output_file << "' loaded successfully.\n";
			cout << "Data file named: '" << fname.data_file << "' loaded successfully.\n";
			cout << "Index file named: '" << fname.index_file << "' loaded successfully.\n";
			cout << "\nPress enter to continue...";
			cin.get();
		}
		fclose(MainFile);
	}


	if ((OutputFile = fopen(output_file, "w")) == NULL) {
		cout << "An ERROR occured with '" << output_file << "'." << endl;
		return -1;
	}

	// Check if the files exist. If they don't, so create them.
	if (_access(data_file, 0) == -1) {	// access in io.h check the file for existance. code for that is 0
		cout << "\nData file doesn't exist. File is to be created.\n";
		if ((DataFile = fopen(data_file, "wb")) == NULL) {
			cout << "An ERROR occured with '" << data_file << "'." << endl;
			return -1;
		} cout << "The file '" << data_file << "' " << "has been created successfully.\n";
		fclose(DataFile);
	}
	// While dealing with index file if it's not existed, we created it, so it completely empty
	// Then index = 0. And if the file exists, it could be empty too, so check for that.
	// If it is empty int index = 0, else read index from a file.
	if (_access(index_file, 0) == -1) {
		cout << "\nIndex file doesn't exist. File is to be created.\n";
		if ((IndexFile = fopen(index_file, "wb")) == NULL) {
			cout << "An ERROR occured with '" << index_file << "'." << endl;
			return -1;
		} cout << "The file '" << index_file << "' " << "has been created successfully.\n";
		fclose(IndexFile);
		// there is no need to store index in file, because if program
		// was closed properly from menu, index was already written in file.
		index = 0;
		cout << "\nPress enter to continue...";
		cin.get();
	}
	else {
		if ((IndexFile = fopen(index_file, "rb")) == NULL) {
			cout << "An ERROR occured with '" << index_file << "'." << endl;
			return -1;
		}
		if (is_empty_file(IndexFile)) {
			index = 0;
		}
		else {
			//fopen(index_file, "rb");
			fseek(IndexFile, 0, SEEK_SET);
			fscanf(IndexFile, "%d", &index);
		}
		fclose(IndexFile);
	}
	system("CLS");
	//+----------------------------------------------------------------------+
	//|                               MAIN LOOP                              |
	//+----------------------------------------------------------------------+
	for (;;) {
		system("CLS");
		print_date();

		cout << "\n1. Create/Refresh files\n2. Add\n3. View\n4. Correct\n5. Delete"
			<< "\n6. Solving an individual task\n7. Rename the files\n8. Check the filenames\n9. Sort by field\n10. View by field\n11. Exit\n"
			<< "\nSelect an option: ";
		menu_choice = number_input(MARK_LIMIT);
		cout << endl;

		switch (menu_choice) {
		case 1:
			system("CLS");
			print_date();

			if ((DataFile = fopen(data_file, "wb")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}
			else if ((IndexFile = fopen(index_file, "wb")) == NULL) {
				cout << "An ERROR occured with '" << index_file << "'." << endl;
				return -1;
			}
			else {
				cout << "\nFile " << data_file << " has been updated successfully.\n";
				cout << "File " << index_file << " has been updated successfully.\n";
				index = 0;	// after refreshing we have no students in file
				cout << "\nPress enter to continue...";
			}
			fclose(IndexFile);
			fclose(DataFile);
			cin.get();
			break;
		case 2: // add
			system("CLS");
			print_date();

			if ((DataFile = fopen(data_file, "ab")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}
			else if ((IndexFile = fopen(index_file, "ab")) == NULL) {
				cout << "An ERROR occured with '" << index_file << "'." << endl;
				return -1;
			}

			student.ID = index;

			cout << "\nEnter a full name of a student: ";
			letter_input(student.full_name, SIZEE);

			cout << "Enter birth year of a student: ";
			while ((student.birth_year = number_input(BIRTH_YEAR_LIMIT)) > get_current_year()) {
				cout << "\nYou cannot be born in future. Try again: ";
			}

			cout << "\nEnter a group number of a student: ";
			student.group_number = number_input(GROUP_LIMIT);

			cout << "\nEnter a math mark of a student: ";
			while ((student.math_mark = number_input(MARK_LIMIT)) > 10) {
				cout << "\nMark cannot be greater than 10. Try again: ";
			}

			cout << "\nEnter a physics mark of a student: ";
			while ((student.physics_mark = number_input(MARK_LIMIT)) > 10) {
				cout << "\nMark cannot be greater than 10. Try again: ";
			}

			cout << "\nEnter an it mark of a student: ";
			while ((student.it_mark = number_input(MARK_LIMIT)) > 10) {
				cout << "\nMark cannot be greater than 10. Try again: ";
			}

			cout << "\nEnter a science mark of a student: ";
			while ((student.science_mark = number_input(MARK_LIMIT)) > 10) {
				cout << "\nMark cannot be greater than 10. Try again: ";
			} cout << endl;

			student.average_mark = (student.physics_mark + student.math_mark + student.it_mark + student.science_mark) / SUBJECTS_AMOUNT;

			fwrite(&student, struct_size, 1, DataFile);
			index++;
			system("CLS");
			print_date();
			print_loading_field(DELAY, 30);
			cout << "\n\nStudent '" << student.full_name << "' added successfully.\n";
			cout << "\nPress enter to continue...";
			cin.get();

			fclose(DataFile);
			break;
		case 3: // view
			system("CLS");
			print_date();

			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured.\n";
				return -1;
			}

			if (is_empty_file(DataFile)) {
				cout << "\nFile is empty. Write something in and try again.\n";
				fclose(DataFile);
			}
			else {
				cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n";
				cout << "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n";
				cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+";

				fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");
				fprintf(OutputFile, "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n");
				fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+");


				for (;;) {
					if (fread(&student, struct_size, 1, DataFile) == NULL) break;
					students_output(&student, OutputFile);
				}
				cout << "\nTotal amount of students: " << index << endl;
			}
			fprintf(OutputFile, "\nTotal amount of students: %d\n", index);
			fclose(DataFile);
			cout << "\nPress enter to continue...";
			cin.get();
			break;
		case 4: // correction
		{
			system("CLS");
			print_date();

			Student* students_array = new Student[index];
			int id_to_correct, field_to_correct;

			cout << "\nEnter ID of a student you would like to change: ";
			while ((id_to_correct = number_input(UNLIMITED)) >= index) {
				cout << "\nEnter ID between 0 till " << index - 1 << "." << endl
					<< "Student's with that ID doesn't exist. Try again: ";
			} cout << endl; system("CLS"); print_date();

			cout << "\n1. Full name" << "\n2. Birth year" << "\n3. Group number"
				<< "\n4. Physics mark" << "\n5. Math mark" << "\n6. It mark" << "\n7. Science mark\n"
				<< "\nEnter number of field you would like to change: ";

			while ((field_to_correct = number_input(MENU_LIMIT)) > STRUCT_FIELDS_AMOUNT || field_to_correct == 0) {
				cout << "\n\nYou can enter between 1 till " << STRUCT_FIELDS_AMOUNT << "." << endl
					<< "Try again: ";
			}

			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}

			for (int i = 0; i < index; i++) {
				if (fread(&students_array[i], struct_size, 1, DataFile) == NULL)
					break;
			}

			if ((DataFile = freopen(data_file, "wb", DataFile)) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}
			else {
				system("CLS");
				print_date();

				switch (field_to_correct) {
				case 1:
					cout << "\nEnter new full name: ";
					letter_input(students_array[id_to_correct].full_name, SIZEE);
					break;
				case 2:
					cout << "Enter new birth year of a student: ";
					while ((students_array[id_to_correct].birth_year = number_input(BIRTH_YEAR_LIMIT)) > get_current_year()) {
						cout << "\nYou cannot be born in future. Try again: ";
					}
					break;
				case 3:
					cout << "\nEnter new group number: ";
					students_array[id_to_correct].group_number = number_input(GROUP_LIMIT);
					break;
				case 4:
					cout << "\nEnter new physics mark: ";
					while ((students_array[id_to_correct].physics_mark = number_input(MARK_LIMIT)) > 10) {
						cout << "\nMark cannot be greater than 10. Try again: ";
					}
					break;
				case 5:
					cout << "\nEnter new math mark: ";
					while ((students_array[id_to_correct].math_mark = number_input(MARK_LIMIT)) > 10) {
						cout << "\nMark cannot be greater than 10. Try again: ";
					}
					break;
				case 6:
					cout << "\nEnter new it mark: ";
					while ((students_array[id_to_correct].it_mark = number_input(MARK_LIMIT)) > 10) {
						cout << "\nMark cannot be greater than 10. Try again: ";
					}
					break;
				case 7:
					cout << "\nEnter new science mark: ";
					while ((students_array[id_to_correct].science_mark = number_input(MARK_LIMIT)) > 10) {
						cout << "\nMark cannot be greater than 10. Try again: ";
					}
					break;
				}
				// Refrest average mark, cause one of them changed
				students_array[id_to_correct].average_mark = (students_array[id_to_correct].physics_mark + students_array[id_to_correct].math_mark + students_array[id_to_correct].it_mark + students_array[id_to_correct].science_mark) / SUBJECTS_AMOUNT;
			}

			for (int i = 0; i < index; i++) { fwrite(&students_array[i], struct_size, 1, DataFile); }
			fclose(DataFile);
			system("CLS");
			print_date();
			print_loading_field(DELAY, 30);
			cout << "\n\nStudent '" << students_array[id_to_correct].full_name << "' changed successfully.\n";
			cout << "\nPress enter to continue...";
			delete[] students_array;
			cin.get();
			break;
		}
		case 5:	// deletion 
		{

			system("CLS");
			print_date();

			if (index == 0) {
				cout << "\nThere is no students in database.\n";
				cout << "\nPress enter to continue...";
				cin.get();
				break;
			}

			int id_to_delete;
			Student* students_array = new Student[index];

			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}

			cout << "\nEnter ID of a student you would like to delete: ";
			while ((id_to_delete = number_input(UNLIMITED)) >= index) {
				cout << "\nEnter ID between 0 till " << index - 1 << "." << endl
					<< "Student's with that ID doesn't exist. Try again: ";
			}

			// 1) Read infromation from a file and store it in array.
			for (int i = 0; i < index; i++) {
				if (fread(&students_array[i], struct_size, 1, DataFile) == NULL)
					break;
			}

			// 2) Then clear data file and write array in the loop, but if we met id_to_delete
			// we skip it.
			if ((DataFile = freopen(data_file, "wb", DataFile)) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}
			else {
				for (int i = 0; i < index; i++) {
					if (i > id_to_delete) { students_array[i].ID = i - 1; }	// correct indexes after deletion
					if (i == id_to_delete) { continue; }	// enter is not pressed;
					else { fwrite(&students_array[i], struct_size, 1, DataFile); }
				} index--;
			}
			fclose(DataFile);
			system("CLS");
			print_date();
			print_loading_field(DELAY, 30);
			cout << "\n\nStudent '" << students_array[id_to_delete].full_name << "' deleted successfully.\n";
			cout << "\nPress enter to continue...";
			delete[] students_array;
			cin.get();
			break;
		}
		case 6:	// personal task
		{
			system("CLS");
			print_date();

			int clever_students_amount = 0;
			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured.\n";
				return -1;
			}

			if (is_empty_file(DataFile)) {
				cout << "\nFile is empty. Write something in and try again.\n";
				fclose(DataFile);
			}
			else {
				cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n";
				cout << "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n";
				cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+";
				fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");
				fprintf(OutputFile, "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n");
				fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");


				for (;;) {
					if (fread(&student, struct_size, 1, DataFile) == NULL) break;
					if (student.physics_mark == 8 && student.math_mark == 9) {
						students_output(&student, OutputFile);
						++clever_students_amount;
					}
				}
				cout << "\nTotal amount of students with that marks: " << clever_students_amount << endl;
			}
			fprintf(OutputFile, "\nTotal amount of students with that marks: %d\n", clever_students_amount);
			fclose(DataFile);
			cout << "\nPress enter to continue...";
			cin.get();
			break;
		}
		case 7: // rename
		{
			system("CLS");
			print_date();
			short file_to_rename;
			bool stop_point = true;

			cout << "\n1. Output file\n2. Data file\n3. Index file\n0. Back\n\nChoose the file you want to rename: ";
			while ((file_to_rename = number_input(MENU_LIMIT)) > 3 && file_to_rename < 0) { cout << "\nThere is no file like that. Try again: "; }
			if (file_to_rename == 0) { break; }

			switch (file_to_rename) {
			case 1:
			{
				char filename[MAX_LENGTH];
				short execution_code;

				// Output file is opened all the time during compilation
				// We cannot renanme opened files, so we have to close it
				// and after all open it again as it was before
				fclose(OutputFile);
				system("CLS");
				print_date();

				cout << "\n\nEnter file name: ";
				while ((execution_code = set_filename_win(".txt", filename)) != 0) {
					switch (execution_code) {
					case -1:
						cout << "\nInvalid file format. Check the source code of the program.";
						break;
					case -2:
						cout << "\nA filename can't contain any of the following characters: \\ / : * ? < > |\n"
							<< "Try again: ";
						break;
					case -3:
						cout << "\n\nDo not use the following reserved names for the name of a file: \nCON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, \nCOM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.\nFor more information, see: https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file?redirectedfrom=MSDN \n\nTry again: ";
						break;
					}
				}

				if (_access(filename, 0) != -1) {
					cout << "\n\nFile '" << filename << "' already exists.\n";
					break;
				}

				if (rename(output_file, filename) == 0) {
					cout << "\nFile name changed from '" << output_file << "' to '" << filename << "' successfully.\n";
					output_file = filename;
				}
				else {
					cout << "\nAn error occured with renaming the '" << output_file << "' file.\n";
					return -1;
				}

				if ((OutputFile = fopen(output_file, "r+")) == NULL) {
					cout << "An ERROR occured with '" << output_file << "'." << endl;
					return -1;
				}
				break;
			}
			case 2:
			{
				char filename[MAX_LENGTH];
				short execution_code;
				system("CLS");
				print_date();

				cout << "\n\nEnter file name: ";
				while ((execution_code = set_filename_win(".dat", filename)) != 0) {
					switch (execution_code) {
					case -1:
						cout << "\nInvalid file format. Check the source code of the program.";
						break;
					case -2:
						cout << "\nA filename can't contain any of the following characters: \\ / : * ? < > |\n"
							<< "Try again: ";
						break;
					case -3:
						cout << "\n\nDo not use the following reserved names for the name of a file: \nCON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, \nCOM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.\nFor more information, see: https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file?redirectedfrom=MSDN \n\nTry again: ";
						break;
					}
				}

				if (_access(filename, 0) != -1) {
					cout << "\n\nFile '" << filename << "' already exists.\n";
					break;
				}

				if (rename(data_file, filename) == 0) {
					cout << "\nFile name changed from '" << data_file << "' to '" << filename << "' successfully.\n";
					data_file = filename;
				}
				else {
					cout << "\nAn error occured with renaming the '" << data_file << "' file.\n";
					return -1;
				}
				break;
			}
			case 3:
			{
				system("CLS");
				print_date();
				char filename[MAX_LENGTH];
				short execution_code;

				cout << "\n\nEnter file name: ";
				while ((execution_code = set_filename_win(".dat", filename)) != 0) {
					switch (execution_code) {
					case -1:
						cout << "\nInvalid file format. Check the source code of the program.";
						break;
					case -2:
						cout << "\nA filename can't contain any of the following characters: \\ / : * ? < > |\n"
							<< "Try again: ";
						break;
					case -3:
						cout << "\n\nDo not use the following reserved names for the name of a file: \nCON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, \nCOM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, and LPT9.\nFor more information, see: https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file?redirectedfrom=MSDN \n\nTry again: ";
						break;
					}
				}

				if (_access(filename, 0) != -1) {
					cout << "\n\nFile '" << filename << "' already exists.\n";
					break;
				}

				if (rename(index_file, filename) == 0) {
					cout << "\nFile name changed from '" << index_file << "' to '" << filename << "' successfully.\n";
					index_file = filename;
				}
				else {
					cout << "\nAn error occured with renaming the '" << index_file << "' file.\n";
					return -1;
				}
				break;
			}
			case 0:
				break;
			}

			cout << "\n\nPress enter to continue...";
			cin.get();
			break;
		}
		case 8:
			system("CLS");
			print_date();
			cout << endl << data_file;
			cout << endl << index_file;
			cout << endl << output_file;
			cout << "\n\nPress enter to continue...";
			cin.get();
			break;
		case 9:	// sort by field
		{
			system("CLS");
			print_date();

			Student* students_array = new Student[index];
			int field_to_sort, int_temp;
			char temp;

			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}

			for (int i = 0; i < index; i++) {
				if (fread(&students_array[i], struct_size, 1, DataFile) == NULL)
					break;
			};

			cout << "\n1. Birth year\n2. Group number"
				<< "\n3. Physics mark\n4. Math mark\n5. It mark\n6. Science mark\n7. ID\n0. Exit\n"
				<< "\nEnter number of field you would like to view by: ";

			while ((field_to_sort = number_input(MENU_LIMIT)) > STRUCT_FIELDS_AMOUNT || field_to_sort < 0) {
				cout << "\n\nYou can enter between 1 till " << STRUCT_FIELDS_AMOUNT << "." << endl
					<< "Try again: ";
			} if (field_to_sort == 0) { break; }

			system("CLS");
			print_date();
			// entering value 
			switch (field_to_sort)
			{
			case 1:	// birth year
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].birth_year > students_array[j + 1].birth_year) {
							temp = students_array[j].birth_year;
							students_array[j].birth_year = students_array[j + 1].birth_year;
							students_array[j + 1].birth_year = temp;
						}
					}
				};
				break;
			case 2:	// group number
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].group_number > students_array[j + 1].group_number) {
							int_temp = students_array[j].group_number;
							students_array[j].group_number = students_array[j + 1].group_number;
							students_array[j + 1].group_number = int_temp;
						}
					}
				};
				break;
			case 3:	// physics
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].physics_mark > students_array[j + 1].physics_mark) {
							int_temp = students_array[j].physics_mark;
							students_array[j].physics_mark = students_array[j + 1].physics_mark;
							students_array[j + 1].physics_mark = int_temp;
						}
					}
				};
				break;
			case 4: // math mark
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].math_mark > students_array[j + 1].math_mark) {
							int_temp = students_array[j].math_mark;
							students_array[j].math_mark = students_array[j + 1].math_mark;
							students_array[j + 1].math_mark = int_temp;
						}
					}
				};
				break;
			case 5: // it mark
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].it_mark > students_array[j + 1].it_mark) {
							int_temp = students_array[j].it_mark;
							students_array[j].it_mark = students_array[j + 1].it_mark;
							students_array[j + 1].it_mark = int_temp;
						}
					}
				};
				break;
			case 6: // science mark
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].science_mark > students_array[j + 1].science_mark) {
							int_temp = students_array[j].science_mark;
							students_array[j].science_mark = students_array[j + 1].science_mark;
							students_array[j + 1].science_mark = int_temp;
						}
					}
				};
				break;
			case 7:	// ID
				for (int i = 0; i < index - 1; i++) {
					for (int j = 0; j < index - i - 1; j++) {
						if (students_array[j].ID > students_array[j + 1].ID) {
							int_temp = students_array[j].ID;
							students_array[j].ID = students_array[j + 1].ID;
							students_array[j + 1].ID = int_temp;
						}
					}
				};
				break;
			}

			system("CLS");
			print_date();

			cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n";
			cout << "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n";
			cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+";
			fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");
			fprintf(OutputFile, "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n");
			fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");



			if ((DataFile = freopen(data_file, "wb", DataFile)) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}

			for (int i = 0; i < index; i++) {
				fwrite(&students_array[i], struct_size, 1, DataFile);
				students_output(&students_array[i], OutputFile);
			}
			cout << "\nPress enter to continue...";
			fclose(DataFile);
			delete[] students_array;
			cin.get();
			break;
		}
		case 10:	// view by field
		{
			system("CLS");
			print_date();

			if ((DataFile = fopen(data_file, "rb")) == NULL) {
				cout << "An ERROR occured with '" << data_file << "'." << endl;
				return -1;
			}

			Student* students_array = new Student[index];
			int field_to_view, field_value, specific_students_amount = 0;

			cout << "\n1. Birth year" << "\n2. Group number"
				<< "\n3. Physics mark" << "\n4. Math mark" << "\n5. It mark" << "\n6. Science mark\n0. Exit\n"
				<< "\nEnter number of field you would like to view by: ";

			while ((field_to_view = number_input(MENU_LIMIT)) > STRUCT_FIELDS_AMOUNT - 1 || field_to_view < 0) {
				cout << "\n\nYou can enter between 1 till " << STRUCT_FIELDS_AMOUNT - 1 << "." << endl
					<< "Try again: ";
			} if (field_to_view == 0) { break; }

			system("CLS");
			print_date();
			// entering value 
			switch (field_to_view)
			{
			case 1:
				cout << "\nEnter birth you would like to view by: ";
				while ((field_value = number_input(BIRTH_YEAR_LIMIT)) > get_current_year()) { cout << "\n Student cannot be born in future. Try again: "; };
				break;
			case 2:
				cout << "\nEnter group number you would like to view by: ";
				field_value = number_input(GROUP_LIMIT);
				break;
			case 3:
				cout << "\nEnter physics mark you would like to view by: ";
				while ((field_value = number_input(MARK_LIMIT)) > 10) { cout << "\nMark cannot be greater than 10. Try again: "; }
				break;
			case 4:
				cout << "\nEnter math mark you would like to view by: ";
				while ((field_value = number_input(MARK_LIMIT)) > 10) { cout << "\nMark cannot be greater than 10. Try again: "; }
				break;
			case 5:
				cout << "\nEnter it mark you would like to view by: ";
				while ((field_value = number_input(MARK_LIMIT)) > 10) { cout << "\nMark cannot be greater than 10. Try again: "; }
				break;
			case 6:
				cout << "\nEnter science you would like to view by: ";
				while ((field_value = number_input(MARK_LIMIT)) > 10) { cout << "\nMark cannot be greater than 10. Try again: "; }
				break;
			}


			for (int i = 0; i < index; i++) {
				if (fread(&students_array[i], struct_size, 1, DataFile) == NULL)
					break;
			} fclose(DataFile);

			system("CLS");
			print_date();

			cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n";
			cout << "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n";
			cout << "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+";
			fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");
			fprintf(OutputFile, "|               Students               |   ID   | Birth year | Group number | Math mark | Physics mark | It mark | Science mark | Average mark |\n");
			fprintf(OutputFile, "+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+\n");

			switch (field_to_view) {
			case 1:	// birth year
				for (int i = 0; i < index; i++) {
					if (students_array[i].birth_year == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that birth year: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that birth year: %d\n", specific_students_amount);
				break;
			case 2: // group number
				for (int i = 0; i < index; i++) {
					if (students_array[i].group_number == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that group number: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that group number: %d\n", specific_students_amount);
				break;
			case 3:	// physics mark 
				for (int i = 0; i < index; i++) {
					if (students_array[i].physics_mark == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that physics mark: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that physics mark: %d\n", specific_students_amount);
				break;
			case 4: // math_mark
				for (int i = 0; i < index; i++) {
					if (students_array[i].math_mark == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that math mark: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that math mark: %d\n", specific_students_amount);
				break;
			case 5:	// it_mark
				for (int i = 0; i < index; i++) {
					if (students_array[i].it_mark == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that it mark: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that it mark: %d\n", specific_students_amount);
				break;
			case 6: // science mark
				for (int i = 0; i < index; i++) {
					if (students_array[i].science_mark == field_value) {
						students_output(&students_array[i], OutputFile);
						++specific_students_amount;
					}
				}
				cout << "\nTotal amount of students with that science mark: " << specific_students_amount << endl;
				fprintf(OutputFile, "\nTotal amount of students with that science mark: %d\n", specific_students_amount);
				break;
			}

			cout << "\nPress enter to continue...";
			delete[] students_array;
			cin.get();
			break;
		}
		case 11:	// exit
			system("CLS");
			print_date();

			if ((IndexFile = fopen(index_file, "wb")) == NULL) {
				cout << "An ERROR occured with '" << index_file << "'." << endl;
				return -1;
			}
			if ((MainFile = fopen(main_file, "wb")) == NULL) {
				cout << "An ERROR occured with '" << main_file << "'." << endl;
				return -1;
			}
			int_in_file(index_file, IndexFile, index);

			strcpy_s(fname.data_file, data_file);
			strcpy_s(fname.output_file, output_file);
			strcpy_s(fname.index_file, index_file);

			fseek(MainFile, 0, SEEK_SET);
			fwrite(&fname, fstruct_size, 1, MainFile);

			fclose(IndexFile);
			fclose(OutputFile);
			fclose(MainFile);

			cout << "\n\nGoodbye! See you next time!\n\n";
			return 1;	// 1 - exit code
		default:
			system("CLS");
			print_date();

			cout << "\nThere is no option like that." << endl;
			cout << "\nPress enter to continue...";
			cin.get();
			break;
		}
	}
	return 0;
}


long int get_file_size(FILE* Stream, const char* file_name)
{
	long int previous_offset = ftell(Stream);
	fseek(Stream, 0, SEEK_END);
	long int file_size = ftell(Stream);
	fseek(Stream, previous_offset, SEEK_SET);
	return file_size;
}


void students_output(Student* student, FILE* stream)
{
	if (student->average_mark == 10) {
		printf("\n| %36.36s | %6d | %10d | %12d |        %2d |           %2d |      %2d |           %2d |         %.1f |", student->full_name, student->ID, student->birth_year, student->group_number, student->math_mark, student->physics_mark, student->it_mark, student->science_mark, student->average_mark);
		printf("\n+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+");
		fprintf(stream, "\n| %36.36s | %6d | %10d | %12d |        %2d |           %2d |      %2d |           %2d |         %.1f |", student->full_name, student->ID, student->birth_year, student->group_number, student->math_mark, student->physics_mark, student->it_mark, student->science_mark, student->average_mark);
	}
	else {
		printf("\n| %36.36s | %6d | %10d | %12d |        %2d |           %2d |      %2d |           %2d |          %.1f |", student->full_name, student->ID, student->birth_year, student->group_number, student->math_mark, student->physics_mark, student->it_mark, student->science_mark, student->average_mark);
		printf("\n+--------------------------------------+--------+------------+--------------+-----------+--------------+---------+--------------+--------------+");
		fprintf(stream, "\n| %36.36s | %6d | %10d | %12d |        %2d |           %2d |      %2d |           %2d |          %.1f |", student->full_name, student->ID, student->birth_year, student->group_number, student->math_mark, student->physics_mark, student->it_mark, student->science_mark, student->average_mark);
	}
}


int add_array_structure(Student student, Student array[], int& index)
{
	if (index >= SIZEE) {
		cout << "\nArray is full. Free some space to continue." << endl;
		return -1;
	}
	else {
		array[index++] = student;
		return 0;
	}
}


bool is_empty_file(FILE* Stream)
{
	// open the file first
	long int previous_offset = ftell(Stream);
	fseek(Stream, 0, SEEK_END);

	if (ftell(Stream) == 0) {
		return true;
	}
	else {
		fseek(Stream, previous_offset, SEEK_SET);
		return false;
	}
}


void letter_input(char string[], int size)
{
	char c;
	int length = 0;

	for (;;)
	{
		c = _getch();
		if (c == 13 && length) break;
		if (c == '\b' && length) {
			cout << "\b \b";
			length--;
			continue;
		}
		if (c == ' ' && string[length - 1] == ' ') { continue; }
		if (c != ' ' && (c > 'z' || c < 'A')) { continue; }
		if (length < size) {
			string[length] = c;
			cout << string[length];
			length++;
		}
	}
	// form string
	string[length] = '\0';
	cout << endl;
}


long long int number_input(int limit)
{
	// Functions takes restrict to enter anything, but digits.
	// We can get only positive numbers. The 'limit' is referred to as digit capacity.
	// If the limit is equal to -1, the limit is the size of an array.
	char c;
	char string[SIZEE]{};
	long int result = 0;
	int length = 0;


	for (;;) {
		c = _getch();
		if (c == 13 && length != 0) { break; }
		if (c == '\b' && length != 0) {
			cout << "\b \b";
			length--;
			continue;
		} if (c < 48 || c > 57) { continue; }
		if (limit == -1) {
			if (length < SIZEE) {
				cout << (int)c - 48;
				string[length] = c;
				length++;
			}
			else { continue; }
		}
		else if (length < limit) {
			cout << (int)c - 48;
			string[length] = c;
			length++;
		}
	} for (int j = 0; j < length; j++) {
		result *= 10;
		result += (int)string[j] - 48;
	}

	return result;
}


void int_in_file(const char* filename, FILE* stream, int value)
{
	// Copyright 2020, Slava Ilyuk, All rights reserved.

	// Function intended to rewrite the int value in the file
	// which in turn is intended to store one int value too.
	// First: we save the previous offset not to destroy the logic in the end.
	// Second: move cursor at the beginning of the file and write value in
	// Third: move cursor back in the first place
	// NOTE: To get value from a file we need to move cursor back 
	// at the beginning as shown below: 

	// fseek(stream, 0, SEEK_SET);
	// fscanf(stream, "%d", &variable_to_store_value);

	long int previous_offset = ftell(stream);

	fseek(stream, 0, SEEK_SET);
	fprintf(stream, "%d", value);

	fseek(stream, previous_offset, SEEK_SET);
}


int get_current_year()
{
	// Copyright 2020, Slava Ilyuk, All rights reserved.

	int year_start = 20;
	int year_end = 23;
	char year[4];
	int int_year = 0;

	time_t current_date = time(0);

	// Convert current_date to string form
	char* date = ctime(&current_date);

	for (int i = year_start, j = 0; i <= year_end; i++, j++) {
		year[j] = date[i];
	}

	for (int j = 0; j < 4; j++) {
		int_year *= 10;
		int_year += (int)year[j] - 48;
	}

	return int_year;
}


void print_date(void)
{
	time_t current_date = time(0);
	char* date = ctime(&current_date);
	cout << date << endl;
}


int set_filename_win(const char* file_format, char filename[MAX_PATH])
{
	// Copyright 2020, Slava Ilyuk, All rights reserved.

	// Function asks you to enter a file name and store it filename
	// then you have to convert it to const char*

	// File format should be with the dot at the beginning
	// Function ask you to input a filenime up to '224 - length of the format - 1,
	// because of the null-terminator' characters
	// Some characters restricted by OS ? | \ / : * <> "
	// Filename could be only for example: '.dat', '.123' etc.
	// Some filenames are restricted such as:
	// CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, COM9, COM0
	// LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9, LPT0
	// Error codes: -1 - invalid format error; -2 - restricted characters error; -3 - reserved name error;
	// successfully executed - 0;

	int str_length = string_length(file_format);
	// file_format should be at least two characters length: .c
	if (file_format[0] != '.' || str_length < 2 || str_length > MAX_PATH) { return -1; }

	char c;
	int length = 0;

	while (length < MAX_PATH - str_length)
	{
		c = _getch();
		if (c == 13) break;
		if (c == '?' || c == '|' || c == '\\' || c == '/' || c == ':' || c == '*' || c == '<' || c == '>' || c == '"') { return -2; }
		if (c == '\b' && length) {
			cout << "\b \b";
			length--;
			continue;
		}
		if (c != '\b') {
			filename[length] = c;
			cout << filename[length];
			length++;
		}
	}
	// For comparsion below
	filename[length] = '\0';	// In the loop below it will be overwrited

	if (string_compare(filename, "CON") || string_compare(filename, "PRN") || string_compare(filename, "AUX") || string_compare(filename, "NUL") || string_compare(filename, "COM1") || string_compare(filename, "COM2") || string_compare(filename, "COM3") || string_compare(filename, "COM4") || string_compare(filename, "COM5") || string_compare(filename, "COM6") || string_compare(filename, "COM7") || string_compare(filename, "COM8") || string_compare(filename, "COM9") || string_compare(filename, "COM0") || string_compare(filename, "LPT1") || string_compare(filename, "LPT2") || string_compare(filename, "LPT3") || string_compare(filename, "LPT4") || string_compare(filename, "LPT5") || string_compare(filename, "LPT6") || string_compare(filename, "LPT7") || string_compare(filename, "LPT8") || string_compare(filename, "LPT9") || string_compare(filename, "LPT0"))
	{
		return -3;
	}

	// add ff to the string
	for (int i = 0; i < str_length; i++, length++) { filename[length] = file_format[i]; }

	// form string

	filename[length] = '\0';


	return 0;
}


int string_length(const char* string) { int i; for (i = 0; string[i] != '\0'; i++) { ; } return i; }


bool string_compare(const char* str1, const char* str2)
{
	int i = 0;

	while (str1[i] != '\0' || str2[i] != '\0') {
		if (str1[i] != str2[i]) { return false; }
		i++;
	}
	return true;
}


void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


void move_console_cursor(short x, short y)
{
	COORD position = { x, y };
	HANDLE output_window = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output_window, position);
}


void print_loading_field(int delay, int end_offset)
{
	int offset = 1;
	std::cout << "[---------------------]";
	move_console_cursor(0, 1);
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0) {
			move_console_cursor(offset, 2);
			Sleep(delay);
			std::cout << "#";
			offset++;
		}
		Sleep(delay);
		move_console_cursor(end_offset, 2);
		std::cout << i << '%';
	}
}
