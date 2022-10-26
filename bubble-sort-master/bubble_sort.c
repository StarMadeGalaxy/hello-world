#include <string.h>
#include <stdio.h>

void swap(int*, int*);
void bubble_sort(int*, int);


int main(void)
{
	int array[13] = {1, 7, 6, 4, 3, 6, 13, 67, 3, 87, 33, 23, 1};

	for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) {
		printf("%d ", array[i]);
	}
	putchar('\n');

	bubble_sort(array, 13);

	for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) { 
		printf("%d ", array[i]);
	}
	putchar('\n');

	getchar();
	return 0;
}

void swap(int* frst, int* snd)			// In C we have to swap variables by their references 
{
	int temp = *frst;
	*frst = *snd;
	*snd = temp;
}	

void bubble_sort(int* array, int length)
{
	int left = 0;		// index for the left element 
	int right = 1;		// index for the right elemnt

	if (length > 1)		//if array consists of 1 element hence it is already sorted
	{
		for(int n_swap = 0; n_swap < length - 1; ++left, ++right)		// n_swap checks if swap has happened. 	
		{																// When at least one swap has happened, so
			if (array[left] > array[right])								// array was not sorted.
			{
				swap(&array[left], &array[right]);
				n_swap = 0;
			}
			else {								// If swap has not happened so two adjacent numbers are sorted
				++n_swap;						// therefore we gotta increase n_swap to let program know
			}									// that these numbers are not going to be swapped
			if (right == length - 1)	// When 'right' hit the last element
			{		
				left = 0;				// Reset both variables to the initial state
				right = 1;
			}
		}
	}	
	else {
		printf("Already have sorted or does not exist.\n");
	}
}