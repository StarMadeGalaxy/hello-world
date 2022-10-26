#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <iomanip>

#define RANGE 1000000
#define TRUE 1

using namespace std;

double sum_s_x(double, double);

int main(void)
{
	double y_x;
	double low_limit, high_limit;
	double step, number;	// number of exercise
	int choice, fun_choice;

	cout << scientific;

	while (TRUE) {

		cout << "Enter '0' or ELSE to use data from database or enter '1' to input your own data: ";
		cin >> choice;

		if (cin.fail()) {
			cout << "Incorrect input! Try again." << endl;
			cin.clear();
			cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
		}
		else {
			cout << endl;
			cin.ignore(RANGE, '\n');
			break;
		}
	}

	switch (choice)
	{
	case 0: default:
		low_limit = 0.1;
		high_limit = 1.0;
		step = 0.1;
		number = 16;
		break;
	case 1:
		while (TRUE) {

			cout << "Please enter 'a': ";
			cin >> low_limit;

			if (cin.fail()) {
				cout << "Incorrect input! Try again." << endl;
				cin.clear();
				cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
			}
			else {
				cin.ignore(RANGE, '\n');
				break;
			}
		}

		while (TRUE) {

			cout << "Please enter 'b': ";
			cin >> high_limit;

			if (cin.fail()) {
				cout << "Incorrect input! Try again." << endl;
				cin.clear();
				cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
			}
			else {
				cin.ignore(RANGE, '\n');
				break;
			}
		}

		while (TRUE) {

			cout << "Please enter 'h': ";
			cin >> step;

			if (cin.fail()) {
				cout << "Incorrect input! Try again." << endl;
				cin.clear();
				cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
			}
			else {
				cin.ignore(RANGE, '\n');
				break;
			}
		}

		while (TRUE) {

			cout << "Please enter 'n': ";
			cin >> number;

			if (cin.fail()) {
				cout << "Incorrect input! Try again." << endl;
				cin.clear();
				cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
			}
			else {
				cin.ignore(RANGE, '\n');
				break;
			}
		}

		break;
	}

	cout << "1, ELSE. S(x)" << endl;
	cout << "2. Y(x)" << endl;
	cout << "3. |S(x) - Y(x)|" << endl << endl;


	while (TRUE) {
		cout << "Please choose the function above: ";
		cin >> fun_choice;

		if (cin.fail()) {
			cout << "Incorrect input! Try again." << endl;
			cin.clear();
			cin.ignore(RANGE, '\n');	// ignore first RANGE symbols from keyboard if it is incorrect
		} else {
			cin.ignore(RANGE, '\n');
			break;
		}
	}
	
	while (low_limit <= high_limit) {
		switch (fun_choice)
		{
		case 1: default:
			printf("+------------------+----------------------+\n");
			printf("| x: %13e |  S(x): %13e |\n", low_limit, sum_s_x(low_limit, number));
			break;
		case 2:
			y_x = cos(low_limit * sin(M_PI_4)) * exp(low_limit * cos(M_PI_4));
			printf("+------------------+---------------------+\n");
			printf("| x: %13e | Y(x): %13e |\n", low_limit, y_x);
			break;
		case 3:
			y_x = cos(low_limit * sin(M_PI_4)) * exp(low_limit * cos(M_PI_4));
			printf("+------------------+------------------------------+\n");
			printf("| x: %13e | |Y(x) - S(x)|: %13e |\n", low_limit, fabs(sum_s_x(low_limit, number) - y_x));
			break;
		}
		low_limit += step;
	}

	if (fun_choice == 1)
	{
		printf("+------------------+----------------------+\n");
	} else if (fun_choice == 2) {
		printf("+------------------+---------------------+\n");
	} else if (fun_choice == 3) {
		printf("+------------------+------------------------------+\n");
	} else {
		printf("+------------------+----------------------+\n");
	}

	return 0;
}


double sum_s_x(double x, double iter_quantity)		// return sum sigma with n = iter_quantity
{
	double sum = 1;		// k = 0 => sum = 1
	double result = 1;

	for (int k = 1; k <= iter_quantity; k++) {
		result *= x / k;
		sum += result * cos(k * M_PI_4);
	}

	return sum;
}

